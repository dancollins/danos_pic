#include "i2cEeprom.h"
#include "iic.h"

list_t eepromFrames;

void eeprom_init(void) {
    list_init(&eepromFrames); // Prepare the list
}

void eeprom_update(void) {
    // Check there are frames to send
    if (list_hasData(&eepromFrames) == False)
        return;

    // Check the I2C module is free
    // TODO: Support multiple I2C modules
    if (I2C_2.state != IDLE)
        return;

    I2CFrame_t * frame;
    list_pop(&eepromFrames, &frame); // Retrieve a frame from the list

    i2c_prepareFrame(EEPROM_MODULE, frame); // Send it to the I2C module
}

Bool eeprom_putData(uint8_t * src, uint16_t addr, uint16_t len, void (*callback)(void), void (*error)(void)) {
    // Chop the data into frames, and add to the list

    
}

Bool eeprom_getData(uint8_t * dest, uint16_t addr, uint16_t len, void (*callback)(void), void (*error)(void)) {
    uint8_t * readData = calloc(2, sizeof(uint8_t));
    readData[0] = (uint8_t)((addr >> 8) & 0xFF); // Split the address word into bytes
    readData[1] = (uint8_t)(addr & 0xFF);

    I2CFrame_t * frame = malloc(sizeof(I2CFrame_t)); // Create an empty frame

    // Fill the frame details
    frame->address = EEPROM_ADDR;
    frame->bytesToRead = len;
    frame->rx_buf = dest;
    frame->tx_buf = readData;
    frame->callback = callback;
    frame->error = error;

    list_add(&eepromFrames, frame); // Add the frame to the list
}

