#include "serial.h"

uint8_t uart_tx_buf[TX_BUFFER_SIZE];
uint8_t uart_rx_buf[RX_BUFFER_SIZE];

uint32_t uart_tx_buf_writing; // The end of the tx buffer
uint32_t uart_tx_buf_written; // The position of the transmit 'cursor' in the buffer
uint32_t uart_tx_buf_size; // The number of bytes in the transmit buffer

uint32_t uart_rx_buf_index;
uint32_t uart_rx_buf_size;

void serial_init(void) {
    // UART1
    U1MODEbits.ON = 1; // Enable the UART
    U1STAbits.UTXEN = 1; // Enable the TX
    U1STAbits.URXEN = 1; // Enable the RX
    U1STAbits.URXISEL = 0; // Interrupt when the RX buffer has any data
    U1BRG = 64; // 38.4kbps

    // Interrupt
    IEC0bits.U1RXIE = 1; // Enable receive interrupt
    IPC6bits.U1IP = 4; // ipl = 4
    IPC6bits.U1IS = 3;

    serial_clearBuffer(UART1);

    uart_tx_buf_writing = 0;
    uart_tx_buf_written = 0;
    uart_tx_buf_size = 0;
}

void serial_receive(uint8_t port) {
    uint8_t rx; // Received character
    
    switch (port)  {
        case UART1:
            if (uart_rx_buf_index >= RX_BUFFER_SIZE) // Can't add to a full buffer
                break;

            rx = U1RXREG;
            uart_rx_buf[uart_rx_buf_index] = rx; // Save the received byte into the buffer
            
            if (rx != '\0')
                uart_rx_buf_index++; // Only increment when the character is not null
            
            break;

        default:
            break;
    }
}

void serial_transmit(void) {
    if (uart_tx_buf_written < uart_tx_buf_writing) {
        if (UARTTransmitterIsReady(UART1)) { // If the transmitter can handle another byte
            UARTSendDataByte(UART1, uart_tx_buf[uart_tx_buf_written++]); // Send a single byte from the output buffer
            uart_tx_buf_size--; // One less byte in the buffer
        }
    } else {
        // No data in the buffer, so reset the index
        uart_tx_buf_written = 0;
        uart_tx_buf_writing = 0;
    }
}

Bool serial_putChar(uint8_t c) {
    if (uart_tx_buf_size >= TX_BUFFER_SIZE)
        return False;

    uart_tx_buf[uart_tx_buf_writing++] = c; // Add the character to the buffer
    uart_tx_buf_size++; // One more character in the buffer
    return True;
}

Bool serial_putString(uint8_t *s) {
    if (strlen(s) >= (TX_BUFFER_SIZE - uart_tx_buf_size))
        return False; // String is too big
    
    while(*s)
        serial_putChar(*s++);

    return True;
}

Bool serial_putData(uint8_t *buf, uint32_t len) {
    uint32_t i;
    
    if (len >= TX_BUFFER_SIZE)
        return False; // String is too big

    for (i = 0; i < len; i++)
        serial_putChar(*buf++); // Add all of the bytes to the buffer

    return True;
}

uint8_t * serial_getBuffer(uint8_t port) {
    uint8_t * buf;
    switch (port) {
        case UART1:
            buf = uart_rx_buf;
            break;
        default:
            buf = Null;
            break;
    }

    return buf;
}

void serial_clearBuffer(uint8_t port) {
    uint32_t i, j;

    switch (port) {
        case UART1:
            uart_rx_buf_index = 0;

            for (j = 0; j < 2; j++)
                for (i = 0; i < RX_BUFFER_SIZE; i++)
                    uart_rx_buf[i] = Null;
            
            break;
        default:
            break;
    }
}
