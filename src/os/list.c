#include "list.h"

void list_init(list_t * list) {
    list->head = Null;
}

Bool list_add(list_t * list, void * element) {
    list_el_t * link;
    size_t linkSize = sizeof(list_el_t);

    link = malloc(linkSize);
    if (link == Null)
        return False;
    
    link->next = list->head; // Save the old head as the new element
    list->head = link; // Store the new link as the new head

    link->element = element;

    return True; // Link creation was successfull
}

Bool list_pop(list_t * list, void * element) {
    list_el_t * link, * prev = Null;

    if (list_length(list) == 0)
        return False; // The list is empty

    link = list->head;

    while (link->next != Null) {
        prev = link;
        link = link->next;
    }

    element = link->element;
    free(link);

    if (prev != Null) {
        prev->next = Null;
    } else {
        list->head = Null; // We just popped the last element in the list
    }

    return True;
}

Bool list_remove(list_t * list, void * element) {
    list_el_t * prev = Null; // The previous link in the chain
    list_el_t * link = list->head; // Point to the first element

    if (list_hasData(list) == False)
        return False; // Can't remove from an empty list

    while(link != Null) {
        if (link->element == element) { // If they point at the same thing, then remove it
            if (prev == Null) {
                list->head = link->next;
            } else {
                prev->next = link->next; // Edit the chain to skip this link
            }

            free(link->element); // Remove the element from the link
            free(link); // Remove the link from the list

            return True; // Link was removed
        }

        prev = link; // Keep reference to the previous link
        link = link->next; // Move to the next link
    }

    return False; // Link was not found
}

uint32_t list_length(list_t * list) {
    uint32_t len = 0; // Will store the length of the list.  Maximum length is 2^32
    list_el_t * link = list->head; // Point to the start of the list

    if (list_hasData(list) == False)
        return 0; // List has no elements

    while (link != Null) {
        link = link->next; // Point to the next link
        len++; // Increment the count
    }

    return len; // Return the length of the list
}

Bool list_hasData(list_t * list) {
    if (list->head == Null)
        return False; // List has no data

    return True; // List has data
}
