/**
 * @author: Dan
 * @since October 29, 2012, 6:34 PM
 * @version 1.0
 *
 * Controls various functions on the board to abstract them.
 */

#ifndef BOARD_H
#define BOARD_H

#include <xc.h>
#include <plib.h>

#include "timer.h"

/**
 * System
 */
#define PBDIV 1 // Peripheral clock divider

#define GetSystemClock() 80000000ul
#define GetPeripheralClock() GetSystemClock() / PBDIV
#define GetInstructionClock() GetSystemClock()

/**
 * LEDs
 */
// Call this to prepare the LED
#define init_led1() TRISGbits.TRISG12 = 0
#define init_led2() TRISGbits.TRISG13 = 0
#define init_led3() TRISGbits.TRISG14 = 0
#define init_led4() TRISGbits.TRISG15 = 0
// Call this to turn the LED on/off
#define led1 LATGbits.LATG12
#define led2 LATGbits.LATG13
#define led3 LATGbits.LATG14
#define led4 LATGbits.LATG15
// Call this to sleep the LED (Put it into a low power mode)
#define sleep_led1() set_led1(0); TRISGbits.TRISG12 = 1
#define sleep_led2() set_led2(0); TRISGbits.TRISG13 = 1
#define sleep_led3() set_led3(0); TRISGbits.TRISG14 = 1
#define sleep_led4() set_led4(0); TRISGbits.TRISG15 = 1

/**
 * Buttons
 */
// Call this to prepare the button
#define init_but1() TRISGbits.TRISG6 = 1
#define init_but2() TRISGbits.TRISG7 = 1
#define init_but3() TRISAbits.TRISA0 = 1
// Call this to read the state of the button
#define but1 PORTGbits.RG6
#define but2 PORTGbits.RG7
#define but3 PORTAbits.RA0
// This is the number of ticks a button needs to be held down
#define BUTTON_COUNT 30

/**
 * Set up the peripherals on the board
 */
void InitialiseBoard(void);

/**
 * This needs to be run at the tick rate to update the buttons
 */
void board_update(void);

/**
 * Send the CPU into idle mode
 */
void board_idle(void);

/**
 * Get the state of the given button
 * @param button The button to check (1, 2, 3)
 * @return The state of the button
 */
Bool board_getButtonState(uint8_t button);

#endif
