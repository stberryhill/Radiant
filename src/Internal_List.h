/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _RADIANT_INTERNAL_LIST_H
#define _RADIANT_INTERNAL_LIST_H

#include "RadiantList.h"
#include <stdint.h>

#define ARRAY_LIST_SIZE_USED -16
#define ARRAY_LIST_SIZE_ALLOCATED -12
#define ARRAY_LIST_BYTES_PER_ELEMENT -8
#define ARRAY_LIST_GROW_INCREMENT -4

#define ARRAY_LIST_EMPTY_SIZE_BYTES 16

struct List {
    uint8_t *data;
};

struct LinkedList {
    LinkedNode *head;
    int size;
};

struct LinkedNode {
    int index;
    LinkedNode *prev;
    LinkedNode *next;
    void *data;
};

#endif