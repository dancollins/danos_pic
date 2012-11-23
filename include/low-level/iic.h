/**
 * @author: Dan
 * @since November 22, 2012, 7:40 PM
 * @version 1.0
 *
 * A driver for the I2C ports (Inter-Integrated Circuit - IIC)
 */

#ifndef I2C_H
#define I2C_H

#include <xc.h>
#include <plib.h>
#include <string.h>

#include "types.h"
#include "board.h"

#define I2C_TX_BUFFER_SIZE 32
#define I2C_RX_BUFFER_SIZE 32

/**
 * The current state of the I2C module
 */
typedef enum {
    IDLE, // Bus is idle
    START, // Send a start condition
    ADDRESS, // Send address
    RESTART, // Enable master receive
    READSTART, // Start a read sequence
    READ, // Read a byte
    WRITE, // Send a byte
    STOP, // Send a stop condition
    BUSERROR // Reset the bus logic
} I2CState_t;

typedef enum {
    READING,
    WRITING
} I2CDirection_t;

/**
 * Used to hold information about an I2C frame
 */
typedef struct {
    uint8_t address; // The 8bit write address (ADDR<<1) + W

    // TODO: Replace with a FIFO buffer
    uint8_t tx_buf[I2C_TX_BUFFER_SIZE]; // The data to send
    uint8_t tx_buf_index; // Location of the cursor
    uint8_t tx_buf_size; // Number of bytes in the buffer

    uint8_t bytesToRead; // Number of bytes to read back
} I2CFrame_t;

/**
 * Used to hold information about a single I2C module
 */
typedef struct {
    uint8_t moduleName;

    I2CState_t state;

    // TODO: Replace with a FIFO buffer
    uint8_t rx_buf[I2C_RX_BUFFER_SIZE]; // Bytes will be read from the I2C into here
    uint8_t rx_buf_index; // Location of the cursor

    I2CFrame_t frame; // A single transaction
    Bool dataToSend; // True when there is data to send

    I2CDirection_t dataDirection;
} I2CModule_t;

/**
 * Prepare the i2c module/s for use
 */
void i2c_init(void);

/**
 * Read a number of bytes from the given i2c port buffer
 * @param p The port to read from
 * @param n The number of bytes to read
 * @param b The array to read into
 */
Bool i2c_readBytesFromBuffer(uint8_t p, uint8_t n, uint8_t * b);

/**
 * Load an I2C transaction for the given module
 * @param p The port to use
 * @param frame The frame to load
 * @return True on success
 */
Bool i2c_prepareFrame(uint8_t p, I2CFrame_t frame);

/**
 * Used to begin transactions if available
 */
void i2c_update(void);

/**
 * Run by the I2C interrupt to process transactions
 */
void i2c_isr(uint8_t p);


#endif
