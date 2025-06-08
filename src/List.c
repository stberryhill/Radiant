/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "RadiantList.h"
#include "Internal_List.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define expand_uint32(listName, index) *((uint32_t*)(listName->data + index))
#define size_used(listName) expand_uint32(listName, ARRAY_LIST_SIZE_USED)
#define size_allocated(listName) expand_uint32(listName, ARRAY_LIST_SIZE_ALLOCATED)
#define bytes_per_element(listName) expand_uint32(listName, ARRAY_LIST_BYTES_PER_ELEMENT)
#define grow_increment(listName) expand_uint32(listName, ARRAY_LIST_GROW_INCREMENT)

#define set_uint32(listName, index, value) *((uint32_t*)(listName->data + index)) = value
#define set_size_used(listName, value) set_uint32(listName, ARRAY_LIST_SIZE_USED, value)
#define set_size_allocated(listName, value) set_uint32(listName, ARRAY_LIST_SIZE_ALLOCATED, value)
#define set_bytes_per_element(listName, value) set_uint32(listName, ARRAY_LIST_BYTES_PER_ELEMENT, value)
#define set_grow_increment(listName, value) set_uint32(listName, ARRAY_LIST_GROW_INCREMENT, value)

List *List_Create(int bytesPerElement, int growIncrement) {
  List *list = malloc(sizeof *list);
  list->data = malloc(ARRAY_LIST_EMPTY_SIZE_BYTES);
  list->data += ARRAY_LIST_EMPTY_SIZE_BYTES;

  set_size_used(list, 0);
  set_size_allocated(list, 0);
  set_bytes_per_element(list, bytesPerElement);
  set_grow_increment(list, growIncrement);

  return list;
}

void List_AddItem(List *list, const void *itemPointer) {
  if (size_used(list) ==  size_allocated(list)) {
    const uint32_t newSize = size_allocated(list) + grow_increment(list);
    const uint32_t newSizeBytes = ARRAY_LIST_EMPTY_SIZE_BYTES + (bytes_per_element(list) * newSize);

    list->data -= ARRAY_LIST_EMPTY_SIZE_BYTES;
    if (!(list->data = realloc(list->data, newSizeBytes))) {
      printf("(%s:%d) [Fatal] could not realloc to add item.\n", __FILE__, __LINE__);
      exit(-1);
    }

    list->data += ARRAY_LIST_EMPTY_SIZE_BYTES;
    set_size_allocated(list, newSize);
  }

  memcpy(list->data + (size_used(list) * bytes_per_element(list)), itemPointer, bytes_per_element(list));
  set_size_used(list, size_used(list) + 1);
}

void List_RemoveItem(List *list, int index);

void *List_GetItem(List *list, int index) {
  return (void*) list->data + (index * bytes_per_element(list));
}

int List_GetSize(List *list) {
  return (int) size_used(list);
}

void List_Destroy(List *list, ListFreeFunction freeElementFunc) {
  uint8_t *element;
  const uint32_t numBytes = size_used(list) * bytes_per_element(list);

  for (element = list->data; element < list->data + numBytes; element += bytes_per_element(list)) {
    freeElementFunc((void*) element);
  }

  /* NOTE: could cause issues since data block is partially frieed in freeElementFunc. Might need to make the freeElementFunc only free nested poitners? Or look for a free func that lets you specify number of bytes to free */
  free(list->data - ARRAY_LIST_EMPTY_SIZE_BYTES);
}