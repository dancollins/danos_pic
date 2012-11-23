#include "iic.h"

I2CModule_t I2C_2;

void i2c_init(void) {
    I2C_2.moduleName = I2C2;

    I2C_2.state = IDLE;

    I2CConfigure(I2C2, I2C_ENABLE_HIGH_SPEED);
    I2CSetFrequency(I2C2, GetPeripheralClock(), 400000); // 400KHz
    I2CEnable(I2C2, TRUE);

    // Interrupts
    IEC1bits.I2C2MIE = 1; // Enable I2C2 master interrupts
    IEC1bits.I2C2BIE = 1; // Enable I2C2 bues error interrupts
    IPC8bits.I2C2IP = 4; // Priority level 4
    IPC8bits.I2C2IS = 2; // Subpriority level 2
}

Bool i2c_readBytesFromBuffer(uint8_t p, uint8_t n, uint8_t * b) {
    switch (p) {
        case I2C2:
            // Check the buffer is big enough to read n bytes from
            if (n >= I2C_RX_BUFFER_SIZE)
                break;

            // Check we have that much data to send back
            if (n > I2C_2.rx_buf_index)
                break;

            // Read n bytes out of the buffer
            uint8_t i = 0;
            for (i = 0; i < n; i++) {
                b[i] = I2C_2.rx_buf[i];
            }

            return True;
    }

    return False;
}

Bool i2c_prepareFrame(uint8_t p, I2CFrame_t frame) {
    switch (p) {
        case I2C2:
            // Check we aren't already sending data
            if (I2C_2.dataToSend == True)
                return False;
            
            // Check we have enough room to receive
            if (frame.bytesToRead >= I2C_RX_BUFFER_SIZE)
                return False;
            
            memcpy(&I2C_2.frame, &frame, sizeof(I2CFrame_t)); // Copy the transaction details
            I2C_2.dataToSend = True;

            return True;
    }

    return False;
}

void i2c_update(void) {
    // TODO: Multiple ports
    if (I2C_2.state == IDLE) {
        // If there is data to send
        if (I2C_2.dataToSend == True) {
            led10 = 1;
            I2C_2.state = START;
            I2C_2.dataDirection = WRITING;

            i2c_isr(I2C2);
        }
    }
}

void i2c_isr(uint8_t p) {
    I2CModule_t * mod;

    // Get a reference to the module structure
    switch (p) {
        case I2C2:
            mod = &I2C_2;
            break;
            
        default:
            return;
    }

    switch (mod->state) {
        case IDLE:
            break;

        case START:
            I2CStart(mod->moduleName);
            mod->state = ADDRESS;
            break;

        case ADDRESS:
            switch (mod->dataDirection) {
                case READING:
                    I2CSendByte(mod->moduleName, mod->frame.address + 1);
                    mod->state = READ;
                    break;

                case WRITING:
                    I2CSendByte(mod->moduleName, mod->frame.address);
                    mod->state = WRITE;
                    break;
            }

            break;

        case RESTART:
            I2CRepeatStart(mod->moduleName);
            mod->dataDirection = READING;
            mod->state = ADDRESS;
            break;

        case READSTART:
            I2CReceiverEnable(I2C2, TRUE);
            mod->state = READ;
            break;

        case READ:
            mod->rx_buf[mod->rx_buf_index++] = I2CGetByte(mod->moduleName);
                
            // If we need to read more bytes send an ACK
            if (mod->rx_buf_index <= mod->frame.bytesToRead) {
                I2CAcknowledgeByte(I2C2, True); // Send an ACK
                mod->state = READSTART; // Prepare for the next byte
            } else {
                I2CAcknowledgeByte(I2C2, False); // Send a NACK
                mod->state = STOP; // Prepare for a stop condition
            }

            break;

        case WRITE:
            // If there are still bytes to send
            if (mod->frame.tx_buf_index < mod->frame.tx_buf_size) {
                I2CSendByte(mod->moduleName, mod->frame.tx_buf[mod->frame.tx_buf_index++]);
            } else {
                // If we need to read some bytes
                if (mod->frame.bytesToRead > 0) {
                    mod->state = RESTART; // Send a restart condition
                } else {
                    mod->state = STOP; // Send a stop condition
                }

                i2c_isr(mod->moduleName); // Re-run this function to call stop/restart
                // TODO: Perhaps there is a better way to do this..!
            }
            break;

        case STOP:
            I2CStop(mod->moduleName);
            I2C_2.dataToSend = False;
            mod->state = IDLE;
            led10 = 0;
            break;

        case BUSERROR:
            led12 = 1;
            // TODO: Something..!
            while(1); // Don't know what to do here yet..!
            break;
    }
}

