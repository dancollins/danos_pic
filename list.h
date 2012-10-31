/**
 * @author: Dan
 * @since October 30, 2012, 5:43 PM
 * @version 1.0
 *
 * Create a list datatype, and provide functions to manage that list
 */

#ifndef LIST_H
#define LIST_H

#include <xc.h>
#include <stdlib.h>
#include "types.h"

struct list_el_s {
    void *element;
    struct list_el_s *next; // The next element in the list
};

struct list_s {
    struct list_el_s *head; // The top of the list
};

typedef struct list_el_s list_el_t; // Element in a list
typedef struct list_s list_t; // A list

/**
 * Prepare a list for use
 * @param l The list to initiate
 */
void list_init(list_t * l);

/**
 * Add an element to a list
 * @param list The list to add to
 * @param element The element to add
 * @return True for success
 */
Bool list_add(list_t * list, void * element);

/**
 * Remove the given element from the list
 * @param list The list to modify
 * @param element The element to remove
 * @return True on success
 */
Bool list_remove(list_t * list, void * element);

/**
 * Return the length of the given list
 * @param list The list to measure
 * @return The length of the list
 */
uint32_t list_length(list_t * list);

/**
 * Check a list to see if it holds any data
 * @param list The list to test
 * @return True when the list has data
 */
Bool list_hasData(list_t * list);

#endif
