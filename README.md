DanOS
=====

My play into the world of my own RTOS.  This is designed to run on a PIC32 platform, but should be portable enough that it can be modified for other platforms.  Low-Level stuff will be platform specific, however you would only ned to change 'board.h' if you are using a PIC32.

Please note, this project was developed using MPLABX (v1.41) and XC32 (v1.11).

As of 31/10/2012, this OS has the capability of sheduling tasks to be run where a task has a start time and a function to call.

On the horizon is a UART driver, and perhaps a UDP stack.
