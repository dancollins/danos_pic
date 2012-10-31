/**
 * @author: Dan
 * @since October 29, 2012, 6:32 PM
 * @version 1.0
 *
 * Manages the system tick timer used for scheduling
 */

#ifndef TIMER_H
#define TIMER_H

#include <xc.h>
#include <plib.h>

#include "types.h"
#include "board.h"

/**
 * Tick timer
 */
#define TICK_FREQUENCY 1000 // 1mS ticks
#define TICK_PRESCALE 8
#define TICK_VALUE GetPeripheralClock() / (TICK_PRESCALE*TICK_FREQUENCY) // Value to load the timer with

/**
 * Prepare the timer for use
 */
void timer_init(void);

/**
 * Called by the ISR upon timer interrupt
 */
void timer_update(void);

#endif
