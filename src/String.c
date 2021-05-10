/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

bool String_Equal(const char *a, const char *b) {
  return (strcmp(a, b) == 0);
}

void String_Copy(const char *src, char *dest) {
  uint32_t i = 0;

  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
}

/* TODO: implement */
void String_CopyN(const char *src, char *dest, uint32_t n);

/* TODO: implement */
int String_Compare(const char *a, const char *b);


int String_ToInt(char *string) {
  int x = 0;
  char *c;
  for (c = string; *c != '\0'; c++) {
    if (*c < '0' || *c > '9') {
      printf("Error - cannot convert string to int, invalid character '%c'\n", *c);
      exit(-1);
    }
    x = (x + (*c - '0')) * 10;
  }

  return x;
}
