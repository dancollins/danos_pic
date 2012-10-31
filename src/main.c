/**
 * @author: Dan
 * @since October 29, 2012, 5:01 PM
 * @version 1.0
 *
 * This is my attempt at creating a simple scheduling system as described by Michael J. Pont (http://www.tte-systems.com/)
 * It will implement a simple multi-state (timed / input) system.
 */

#include <xc.h>

#include "types.h"
#include "board.h"
#include "timer.h"
#include "jobs.h"

// TODO: Make this better..!
Bool checkButtons(void);
Bool blinkyLed(void);

Bool turnOffLed2(void);
Bool turnOffLed3(void);
Bool turnOffLed4(void);

/**
 * Prepare the various peripherals for use
 */
void init(void) {
    InitialiseBoard();
    timer_init();
    jobs_init();
}

int main(void) {
    init();

    job_t blinkyLedJob = {
        .activationTime = timer_currentTime(),
        .jobFunction = blinkyLed
    };

    job_t checkButtonsJob = {
        .activationTime = timer_currentTime(),
        .jobFunction = checkButtons
    };

    jobs_add(&blinkyLedJob);
    jobs_add(&checkButtonsJob);

    while (1) {
        board_update(); // Check the buttons
        jobs_update(); // Run the jobs
        
        // Go into sleep mode
        board_idle();
    }

    return 0;
}

Bool checkButtons(void) {
    job_t ledJob = {
        .activationTime = timer_currentTime() + 500
    };

    if (board_getButtonState(1)) {
        led2 = 1;
        ledJob.jobFunction = turnOffLed2;
        jobs_add(&ledJob);
    }

    if (board_getButtonState(2)) {
        led3 = 1;
        ledJob.jobFunction = turnOffLed3;
        jobs_add(&ledJob);
    }

    if (board_getButtonState(3)) {
        led4 = 1;
        ledJob.jobFunction = turnOffLed4;
        jobs_add(&ledJob);
    }

    return False; // This job never finishes
}

Bool blinkyLed(void) {
    static uint32_t delayTime = 0; // The time to delay before executing this thread again
    uint32_t currentTime = timer_currentTime();

    if (delayTime <= currentTime) { // If it is time to run this job...
        led1 ^= 1;

        delayTime = currentTime + 500; // Execute this job every 500mS
    }

    return False; // This job never stops
}

Bool turnOffLed2(void) {
    led2 = 0;
    return True;
}

Bool turnOffLed3(void) {
    led3 = 0;
    return True;
}

Bool turnOffLed4(void) {
    led4 = 0;
    return True;
}

