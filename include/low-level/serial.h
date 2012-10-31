/**
 * @author: Dan
 * @since October 31, 2012, 10:52 AM
 * @version 1.0
 *
 * This is the lowest level UART driver.
 * Reads and writes are done though a buffer
 */

#ifndef UART_H
#define UART_H

#include <xc.h>
#include <plib.h>

#include "types.h"
#include "board.h"

// TODO: Support more than one UART

#define TX_BUFFER_SIZE 128 // The bytes in RAM that each buffer will ocupy (there is a Tx and an Rx buffer)
#define RX_BUFFER_SIZE 512 // The bytes in RAM that each buffer will ocupy (there is a Tx and an Rx buffer)

/**
 * Prepares the serial ports for use
 */
void serial_init(void);

/**
 * Handle the receive buffers.  This should be interrupt driven
 */
void serial_receive(void);

/**
 * Handle the transmission of the output buffer
 * This should be run in the main loop.
 */
void serial_transmit(void);

/**
 * Put a single character into the transmit buffer
 * @param c The character to transmit
 */
void serial_putChar(uint8_t c);

/**
 * Put a string into the transmit buffer
 * @param s The string to transmit
 */
void serial_putString(uint8_t *s);

#endif
