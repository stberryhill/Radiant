/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "RadiantList.h"
#include "Internal_List.h"

#include <stdlib.h>
#include <stdio.h>

LinkedList *LinkedList_create() {
    LinkedList *list = malloc(sizeof *list);
    list->head = 0;
    list->size = 0;
    return list;
}

void LinkedList_destroy(LinkedList *list, void (*freeNodeDataFunc)(void *)) {
    LinkedNode *n = list->head;
    int i;
    for (i = 0; i < list->size; i++) {
        LinkedNode *next = n->next;
        freeNodeDataFunc(n->data);
        free(n);
        n = next;
    }

    free(list);
}

LinkedNode *LinkedList_getHead(LinkedList *list) {
    return list->head;
}

int LinkedList_getSize(LinkedList *list) {
    return list->size;
}

void LinkedList_addNode(LinkedList *list, void *data) {
    LinkedNode *node = malloc(sizeof *node);
    node->data = data;

    if (!list->head) {
        list->head = node;
        list->head->index = 0;
    } else {
        LinkedNode *n = list->head;
        int i = 0;

        while(n->next) { n = n->next; i++; } /*Go to first non-initialized node */

        n->next = node;
        n->next->prev = n;
        n->next->index = i;
    }

    list->size++;
}

void LinkedList_removeNode(LinkedList *list, LinkedNode *node) {
    LinkedNode *n = list->head;
    while(n) {
        if (n == node) {
            if (n == list->head) {
                list->head = n->next;
            } else {
                if (n->next) {
                    n->prev->next = n->next;
                } else {
                    n->prev->next = 0;
                }
            }

            list->size--;
            return;
        }
    }

    printf("LinkedList error - trying to remove node that doesn't exist...\n");
    exit(-1);
}
void LinkedList_removeNodeByIndex(LinkedList *list, int indexOfNode);
int LinkedList_getIndexOfNode(LinkedList *list, LinkedNode *node);
LinkedNode *LinkedList_getNodeAtIndex(LinkedList *list, int index);

void *LinkedList_getData(LinkedList *list, int index) {
    if (index > list->size) {
        printf("LinkedList error - index is greather than size\n");
        exit(-1);
    }

    LinkedNode *node = list->head;
    int i;
    for (i = 0; i < index; i++) {
        node = node->next;
    }

    return node->data;
}