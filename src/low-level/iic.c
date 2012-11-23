#include "iic.h"

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

Bool i2c_prepareFrame(uint8_t p, I2CFrame_t * frame) {
    switch (p) {
        case I2C2:
            // Check we aren't already sending data
            if (I2C_2.state != IDLE)
                return False;

            // Check the module isn't being used by something else
            if (I2C_2.frameToSend == True)
                return False;

            frame->rx_buf_index = 0;
            frame->tx_buf_index = 0;
            
            I2C_2.frame = frame; // Store the frame as the next job to do
            I2C_2.frameToSend = True;
            
            return True;
    }

    return False;
}

void i2c_update(void) {
    // TODO: Multiple ports
    if (I2C_2.state == IDLE) {
        // If there is data to send
        if (I2C_2.frameToSend == True) {
            I2C_2.state = START;

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
            I2C_2.dataDirection = WRITING;
            break;

        case ADDRESS:
            switch (mod->dataDirection) {
                case READING:
                    I2CSendByte(mod->moduleName, mod->frame->address + 1);
                    mod->state = CHECK_ACK;
                    break;

                case WRITING:
                    I2CSendByte(mod->moduleName, mod->frame->address);
                    mod->state = CHECK_ACK;
                    break;
            }

            break;

        case CHECK_ACK:
            if (I2CByteWasAcknowledged(mod->moduleName) == True) {
                switch (mod->dataDirection) {
                    case READING:
                        mod->state = READ;
                        break;

                    case WRITING:
                        mod->state = WRITE;
                        break;
                }
            } else {
                mod->frame->success = False;
                mod->state = STOP;
            }

            i2c_isr(mod->moduleName);
            
            break;

        case RESTART:
            I2CRepeatStart(mod->moduleName);
            mod->dataDirection = READING;
            mod->state = ADDRESS;
            break;

        case READ_START:
            I2CReceiverEnable(mod->moduleName, TRUE);
            mod->state = READ;
            break;

        case READ:
            mod->frame->rx_buf[mod->frame->rx_buf_index++] = I2CGetByte(mod->moduleName);
                
            // If we need to read more bytes send an ACK
            if (mod->frame->rx_buf_index <= mod->frame->bytesToRead) {
                I2CAcknowledgeByte(mod->moduleName, True); // Send an ACK
                mod->state = READ_START; // Prepare for the next byte
            } else {
                I2CAcknowledgeByte(mod->moduleName, False); // Send a NACK
                mod->frame->success = True;
                mod->state = STOP; // Prepare for a stop condition
            }

            break;

        case WRITE:
            // If there are still bytes to send
            if (mod->frame->tx_buf_index < mod->frame->tx_buf_size) {
                I2CSendByte(mod->moduleName, mod->frame->tx_buf[mod->frame->tx_buf_index++]);
            } else {
                // If we need to read some bytes
                if (mod->frame->bytesToRead > 0) {
                    mod->state = RESTART; // Send a restart condition
                } else {
                    mod->frame->success = True;
                    mod->state = STOP; // Send a stop condition
                }

                i2c_isr(mod->moduleName); // Re-run this function to call stop/restart
                // TODO: Perhaps there is a better way to do this..!
            }
            break;

        case STOP:
            I2CStop(mod->moduleName);
            mod->frameToSend = False;
            mod->state = IDLE;

            // Tell the owner of the frame that it has complete or failed
            if (mod->frame->success == True) {
                mod->frame->callback();
            } else {
                mod->frame->error();
            }

            break;

        case BUSERROR:
            led12 = 1;
            // TODO: Something..!
            while(1); // Don't know what to do here yet..!
            break;
    }
}

