/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "RadiantList.h"
#include "Internal_List.h"

LinkedNode *LinkedNode_getNext(LinkedNode *node) {
    return node->next;
}

LinkedNode *LinkedNode_getPrevious(LinkedNode *node) {
    return node->prev;
}

void *LinkedNode_getData(LinkedNode *node) {
    return node->data;
}