#include "board.h"

/**
 * Configuration.
 * 80MHz Clock
 */
#pragma config POSCMOD = EC // Using an external clock IC
#pragma config FNOSC = PRIPLL // Use the PLL as the clock source
#pragma config FPLLIDIV = DIV_2 // Divide 8MHz / 2 = 4MHz
#pragma config FPLLMUL = MUL_20 // Multiply 4MHz * 20 = 80MHz
#pragma config FPLLODIV = DIV_1 // Don't divide the output = 80MHz
#pragma config FPBDIV = DIV_2 // PB Clock will be 40MHz

#ifdef __DEBUG
#pragma config ICESEL = ICS_PGx1
#endif

button_t board_b1, board_b2, board_b3;

void InitialiseBoard(void) {
    // System
    SYSTEMConfig(GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    while(!(OSCCON && 0x20)); // Wait for PLL to start up
    DDPCONbits.JTAGEN = 0; // Disable JTAG

    // LEDs
    init_led1();
    init_led2();
    init_led3();
    init_led4();
    init_led5();
    init_led6();
    init_led7();
    init_led8();
    init_led9();
    init_led10();
    init_led11();
    init_led12();

    led1 = 0;
    led2 = 0;
    led3 = 0;
    led4 = 0;
    led5 = 0;
    led6 = 0;
    led7 = 0;
    led8 = 0;
    led9 = 0;
    led10 = 0;
    led11 = 0;
    led12 = 0;

    // Buttons
    init_but1();
    board_b1.pressed = False;
    board_b1.time = 0;
    board_b1.read = False;

    init_but2();
    board_b2.pressed = False;
    board_b2.time = 0;
    board_b2.read = False;

    init_but3();
    board_b3.pressed = False;
    board_b3.time = 0;
    board_b3.read = False;

    // Interrupts
    INTConfigureSystem(INT_SYSTEM_CONFIG_MULT_VECTOR);
    INTEnableInterrupts();
}

/**
 * Button Debouncing
 */
void board_update(void) {
    // Button 1
    if (but1) {
        board_b1.pressed = True;

        if(board_b1.time < BUTTON_COUNT)
            board_b1.time++;
    } else {
        if (board_b1.time)
            board_b1.time --;

        if (board_b1.time < BUTTON_COUNT) {
            board_b1.pressed = False;
            board_b1.read = False;
        }
    }

    // Button 2
    if (but2) {
        board_b2.pressed = True;

        if(board_b2.time < BUTTON_COUNT)
            board_b2.time++;
    } else {
        if (board_b2.time)
            board_b2.time --;

        if (board_b2.time < BUTTON_COUNT) {
            board_b2.pressed = False;
            board_b2.read = False;
        }
    }

    // Button 3
    if (but3) {
        board_b3.pressed = True;

        if(board_b3.time < BUTTON_COUNT)
            board_b3.time++;
    } else {
        if (board_b3.time)
            board_b3.time --;

        if (board_b3.time < BUTTON_COUNT) {
            board_b3.pressed = False;
            board_b3.read = False;
        }
    }

    // UART
    serial_transmit();

    // I2C
    i2c_update();

    // EEPROM
    eeprom_update();
}

void board_idle(void) {
    PowerSaveIdle(); // TODO: Move this to board so it's more portable
}

Bool board_getButtonState(uint8_t button) {
    switch (button) {
        case 1:
            if ((board_b1.pressed == True) && (board_b1.time >= BUTTON_COUNT) && (board_b1.read == False)) {
                board_b1.read = True;
                return True;
            }
            return False;
            break;
        case 2:
            if ((board_b2.pressed == True) && (board_b2.time >= BUTTON_COUNT) && (board_b2.read == False)) {
                board_b2.read = True;
                return True;
            }
            return False;
            break;
        case 3:
            if ((board_b3.pressed == True) && (board_b3.time >= BUTTON_COUNT) && (board_b3.read == False)) {
                board_b3.read = True;
                return True;
            }
            return False;
            break;
    }
}

/**
 * Interrupt vectors
 */
void __ISR(_TIMER_1_VECTOR, ipl5) isr_timer1(void) {
    mT1ClearIntFlag(); // Clear interrupt flag TODO: This macro is legacy
    
    timer_update();
}

void __ISR(_UART_1_VECTOR, ipl4) isr_uart1(void) {
    if ((IEC0bits.U1RXIE == True) &&(IFS0bits.U1RXIF == True)) {
        serial_receive(UART1);
        
        IFS0bits.U1RXIF = 0; // Clear the flag
    }
}

void __ISR(_I2C_2_VECTOR, ipl4) isr_i2c2(void) {
    /* Master interrupt */
    if ((IEC1bits.I2C2MIE == True) && (IFS1bits.I2C2MIF == True)) {
        i2c_isr(I2C2);

        IFS1bits.I2C2MIF = 0; // Clear the flag
    }

    /* Bus error interrupt */
    if ((IEC1bits.I2C2ABIE == True) && (IFS1bits.I2C2BIF == True)) {

        IFS1bits.I2C2BIF = 0; // Clear the flag
    }
}
