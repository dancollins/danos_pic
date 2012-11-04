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
#include <string.h>

#include "types.h"
#include "board.h"

// TODO: Support more than one UART

#define TX_BUFFER_SIZE 512 // The bytes in RAM that each buffer will ocupy (there is a Tx and an Rx buffer)
#define RX_BUFFER_SIZE 256 // The bytes in RAM that each buffer will ocupy (there is a Tx and an Rx buffer)

/**
 * Prepares the serial ports for use
 */
void serial_init(void);

/**
 *
 * @param mod The port that fired the interrupt
 */
void serial_receive(uint8_t port);

/**
 * Handle the transmission of the output buffer
 * This should be run in the main loop.
 */
void serial_transmit(void);

/**
 * Put a single character into the transmit buffer
 * @param c The character to transmit
 * @return True if the byte was added
 */
Bool serial_putChar(uint8_t c);

/**
 * Put a string into the transmit buffer
 * @param s The string to transmit
 * @return True if the string was added
 */
Bool serial_putString(uint8_t *s);

/**
 * Put a fixed number of bytes into the output buffer
 * @param buf The buffer to add from
 * @param len The number of bytes in the buffer
 * @return True if the bytes were added
 */
Bool serial_putData(uint8_t *buf, uint32_t len);

/**
 * Get a pointer to the receive buffer
 * @param port The port to get the buffer of
 * @return Pointer to the buffer
 */
uint8_t * serial_getBuffer(uint8_t port);

/**
 * Clear the receive buffer of the given port
 * @param port The port to clear
 */
void serial_clearBuffer(uint8_t port);

#endif
