/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _RADIANT_LIST_H
#define _RADIANT_LIST_H

#include "RadiantAPIMacro.h"

typedef struct List List; /* Array-based list focused on cache locality - best for most cases */
typedef struct LinkedList LinkedList;
typedef struct LinkedNode LinkedNode;
typedef void (*ListFreeFunction)(void *); /* List free function - to free nested pointers only. */

/* List functions */
RADIANT_API List *List_Create(int bytesPerElement, int growIncrement);
RADIANT_API void List_AddItem(List *list, const void *itemPointer);
RADIANT_API void List_RemoveItem(List *list, int index);
RADIANT_API void *List_GetItem(List *list, int index);
RADIANT_API int List_GetSize(List *list);
RADIANT_API void List_Destroy(List *list, ListFreeFunction freeElementFunc);

/* Linked list functions */
RADIANT_API LinkedList *LinkedList_create();
RADIANT_API void LinkedList_destroy(LinkedList *list, void (*freeNodeDataFunc)(void *));
RADIANT_API LinkedNode *LinkedList_getHead(LinkedList *list);
RADIANT_API int LinkedList_getSize(LinkedList *list);
RADIANT_API void LinkedList_addNode(LinkedList *list, void *data);
RADIANT_API void LinkedList_removeNode(LinkedList *list, LinkedNode *node);
RADIANT_API void LinkedList_removeNodeByIndex(LinkedList *list, int indexOfNode);
RADIANT_API int LinkedList_getIndexOfNode(LinkedList *list, LinkedNode *node);
RADIANT_API LinkedNode *LinkedList_getNodeAtIndex(LinkedList *list, int index);
RADIANT_API void *LinkedList_getData(LinkedList *list, int index);

/* Linked node functions */
RADIANT_API LinkedNode *LinkedNode_getNext(LinkedNode *node);
RADIANT_API LinkedNode *LinkedNode_getPrevious(LinkedNode *node);
RADIANT_API void *LinkedNode_getData(LinkedNode *node);

#endif