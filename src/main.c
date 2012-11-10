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

#include "jobs.h"

#include "board.h"
#include "timer.h"
#include "serial.h"

Bool checkButtons(void);
Bool checkUart(void);
Bool blinkyLed(void);

Bool turnOffLed2(void);
Bool turnOffLed3(void);
Bool turnOffLed4(void);

/**
 * Prepare the various peripherals for use
 */
void init(void) {
    InitialiseBoard(); // Prepare the board (this is basic IO stuff, and also CPU init stuff)
    timer_init(); // Prepare the systick timer
    serial_init(); // Prepare the serial port
    jobs_init(); // Prepare the job controller
}

int main(void) {
    init();

    serial_putString("Starting up...\r\n");

    /*
     * Create a job description for a blinking LED
     */
    job_t blinkyLedJob = {
        .activationTime = timer_currentTime(),
        .jobFunction = blinkyLed
    };

    /*
     * Create a job description that will check the state of the buttons
     */
    job_t checkButtonsJob = {
        .activationTime = timer_currentTime(),
        .jobFunction = checkButtons
    };

    job_t checkSerialJob = {
        .activationTime = timer_currentTime(),
        .jobFunction = checkUart
    };

    // Add the jobs into the jobs controller
    jobs_add(&blinkyLedJob);
    jobs_add(&checkButtonsJob);
    jobs_add(&checkSerialJob);

    while (1) {
        board_update(); // Run the low level operations (buttons, uart...)
        jobs_update(); // Run the jobs
        
        // Go into sleep mode
        board_idle();
    }

    return 0;
}

Bool checkButtons(void) {
    // This will temporarily hold a job description for the LEDs if one needs to be created
    job_t ledJob = {
        .activationTime = timer_currentTime() + 500 // LEDs need to be turned off in 500mS
    };

    /*
     * These jobs will turn the LED on, and create a job to turn them off in 500mS
     */
    if (board_getButtonState(1)) {
        led2 = 1;
        ledJob.jobFunction = turnOffLed2;
        jobs_add(&ledJob);
        serial_putString("Button 1 pressed.\r\n");
    }

    if (board_getButtonState(2)) {
        led3 = 1;
        ledJob.jobFunction = turnOffLed3;
        jobs_add(&ledJob);
        serial_putString("Button 2 pressed.\r\n");
    }

    if (board_getButtonState(3)) {
        led4 = 1;
        ledJob.jobFunction = turnOffLed4;
        jobs_add(&ledJob);
        serial_putString("Button 3 pressed.\r\n");
    }

    return False; // This job never finishes
}

Bool checkUart(void) {
    uint8_t * uart_buf = serial_getBuffer(UART1);

    if (strstr(uart_buf, "on") != Null) {
        led6 = 1;
        serial_putString("Turning LED on\r\n");
        serial_putChar('{');
        serial_putString(uart_buf);
        serial_putString("}\r\n");
        serial_clearBuffer(UART1);
    }

    if (strstr(uart_buf, "off") != Null) {
        led6 = 0;
        serial_putString("Turning LED off\r\n");
        serial_putChar('{');
        serial_putString(uart_buf);
        serial_putString("}\r\n");
        serial_clearBuffer(UART1);
    }

    return False; // This job never ends
}

Bool blinkyLed(void) {
    static uint32_t delayTime = 0; // The time to delay before executing this thread again
    uint32_t currentTime = timer_currentTime();

    uint8_t * rxBuf; // TODO: Remove this.  This is for debugging the UART getting more characters than it should

    /*
     * TODO: This thread actually only needs to run at 2Hz, so job descriptions should allow for this by adding a field called update period
     */
    if (delayTime <= currentTime) { // If it is time to run this job...
        led1 ^= 1;

        delayTime = currentTime + 500; // Execute this job every 500mS
    }

    return False; // This job never stops
}

/**
 * Turn LED off
 * @return True when the job has completed
 */
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

