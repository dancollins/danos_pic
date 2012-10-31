#include "timer.h"

uint32_t sysTick;

void timer_init(void) {
    sysTick = 0;

    OpenTimer1(T1_ON | T1_PS_1_8, TICK_VALUE); // Start timer1 and load it for 1mS operation
    ConfigIntTimer1(T1_INT_ON | T1_INT_PRIOR_5); // Use interrupts on timer1 at priority 5
}

void timer_update(void) {
    sysTick++;
}

uint32_t timer_currentTime(void) {
    return sysTick;
}
