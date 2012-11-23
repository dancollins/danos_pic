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
    CHECK_ACK,
    RESTART, // Enable master receive
    READ_START, // Start a read sequence
    READ, // Read a byte
    WRITE, // Send a byte
    STOP, // Send a stop condition
    BUSERROR // Reset the bus logic
} I2CState_t;

/**
 * A higher level state
 * Is the I2C module currently reading or writing data?
 */
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
    uint8_t * tx_buf; // The data to send
    uint8_t tx_buf_index; // Location of the cursor
    uint8_t tx_buf_size; // Number of bytes in the buffer

    uint8_t * rx_buf; // Where data will be entered
    uint8_t rx_buf_index; // Location of the cursor
    uint8_t bytesToRead; // Number of bytes to read back

    void (*callback)(void); // The function to call when the frame is completed
    void (*error)(void); // The function to call if the frame terminates early

    Bool success; // True when the frame has been processed
} I2CFrame_t;

/**
 * Used to hold information about a single I2C module
 */
typedef struct {
    uint8_t moduleName;

    I2CState_t state;

    I2CFrame_t * frame; // A single transaction
    Bool frameToSend; // True when there is data to send

    I2CDirection_t dataDirection;
} I2CModule_t;

I2CModule_t I2C_2;

/**
 * Prepare the i2c module/s for use
 */
void i2c_init(void);

/**
 * Load an I2C transaction for the given module
 * @param p The port to use
 * @param frame The frame to load
 * @return True on success
 */
Bool i2c_prepareFrame(uint8_t p, I2CFrame_t * frame);

/**
 * Used to begin transactions if available
 */
void i2c_update(void);

/**
 * Run by the I2C interrupt to process transactions
 */
void i2c_isr(uint8_t p);


#endif
