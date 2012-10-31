/**
 * @author: Dan
 * @since October 29, 2012, 11:34 PM
 * @version 1.0
 *
 * DESC
 */

#ifndef TYPES_H
#define TYPES_H

#include <xc.h>

#define Null 0

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;

typedef enum {False = 0, True} Bool; // Boolean datatype

typedef struct {
    uint8_t pressed; // True when the button is pressed
    uint8_t read; // True when the button has been read
    uint8_t time; // The length of the press
} button_t;

#endif
