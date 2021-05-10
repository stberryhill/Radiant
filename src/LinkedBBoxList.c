/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "RadiantPhysics.h"
#include "Internal_Physics.h"

#include <stdlib.h>
#include <string.h>

BBox2DList *BBoxList_create() {
    BBox2DList *list = malloc(sizeof *list);
    list->head = 0;
    list->size = 0;

    return list;
}

void BBoxList_destroy(BBox2DList *list) {
    if (list) {
        BBox2DListNode *n = list->head;
        int i;
        for (i = 0; i < list->size; i++) {
            BBox2DListNode *next = n->next;
            free(n->data);
            free(n);
            n = next;
        }
    }
}
BBox2DListNode * BBoxList_getHead(BBox2DList *list) {
    return list->head;
}

int BBoxList_getSize(BBox2DList *list) {
    return list->size;
}

BBox2D *BBoxList_addBBox(BBox2DList *list, const BBox2D box) {

    BBox2DListNode *newNode = malloc(sizeof *newNode);
    newNode->data = malloc(sizeof *newNode->data);
    memcpy(newNode->data, &box, sizeof(*newNode->data));
    newNode->next = 0;

    if (list->size == 0) {
        newNode->prev = 0;
        list->head = newNode;
        
    } else {
        BBox2DListNode *node = list->head;
        while (node->next) {
            node = node->next;
        }

        newNode->prev = node;
        node->next = newNode;
    }

    list->size++;

    return newNode->data;
}

void BBoxList_removeNode(BBox2DList *list, BBox2DListNode *node);
void BBoxList_removeNodeByIndex(BBox2DList *list, int indexOfNode);