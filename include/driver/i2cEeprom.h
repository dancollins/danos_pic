/**
 * @author: Dan
 * @since November 24, 2012, 1:12 AM
 * @version 1.0
 *
 * DESC
 */

#ifndef I2CEEPROM_H
#define I2CEEPROM_H

#include <xc.h>

#include "list.h"

#define EEPROM_MODULE I2C2 // The I2C module the eeprom is connected to
#define EEPROM_ADDR 0xA0 // The I2C address of the module

/**
 * Prepares the eeprom driver
 */
void eeprom_init(void);

/**
 * This will manage operations to the EEPROM.
 */
void eeprom_update(void);

/**
 * Used to send data to the EEPROM.
 * The buffer will be split into 64 byte frames which will be stored in a list of operations.
 * @param src The data to be sent
 * @param addr The eeprom address to start sending the data to
 * @param len The number of bytes to send
 * @param callback The function to call when the frame was sent
 * @param error The function to call if the frame fails
 * @return True if the frame/s was/were created
 */
Bool eeprom_putData(uint8_t * src, uint16_t addr, uint16_t len, void (*callback)(void), void (*error)(void));

/**
 * Used to read data from the EEPROM.
 * @param dest Where to save the data (this needs to be large enough to hold the data)
 * @param addr The address to start reading from
 * @param len The number of bytes to read
 * @param callback The function to call when the frame was sent
 * @param error The function to call if the frame fails
 * @return True if the frame was created
 */
Bool eeprom_getData(uint8_t * dest, uint16_t addr, uint16_t len, void (*callback)(void), void (*error)(void));

#endif
