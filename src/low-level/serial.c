#include "serial.h"

uint8_t uart_tx_buf[TX_BUFFER_SIZE];
uint8_t uart_rx_buf[RX_BUFFER_SIZE];

uint8_t *uart_tx_buf_end; // The end of the tx buffer
uint8_t *uart_tx_buf_pos; // The position of the transmit 'cursor' in the buffer

void serial_init(void) {
    UARTEnable(UART1, UART_ENABLE_FLAGS(UART_RX | UART_TX));
}

void serial_receive(void) {

}

void serial_transmit(void) {

}

void serial_putChar(uint8_t c) {
    *uart_tx_buf_end++ = c; // Add the character to the buffer
}

void serial_putString(uint8_t *s) {
    while(*s)
        serial_putChar(*s++);
}
