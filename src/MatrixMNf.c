/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "RadiantMath.h"
#include <stdio.h>

#define MATN_MAX_STRING_LENGTH 4096

void MatrixMNf_Zeros(const int m, const int n, float *output) {
  const int numElements = m * n;
  int i;

  for (i = 0; i < numElements; i++) {
    output[i] = 0.0;
  }
}

void MatrixMNf_Ones(const int m, const int n, float *output) {
  const int numElements = m * n;
  int i;

  for (i = 0; i < numElements; i++) {
    output[i] = 1.0;
  }
}

void MatrixMNf_Add(const int m, const int n, const float *a, const float *b, float *output) {
  int i;
  const int numElements = m * n;

  for (i = 0; i < numElements; i++) {
    output[i] = a[i] + b[i];
  }
}

void MatrixMNf_Subtract(const int m, const int n, const float *a, const float *b, float *output) {
  int i;
  const int numElements = m * n;

  for (i = 0; i < numElements; i++) {
    output[i] = a[i] - b[i];
  }
}

void MatrixMNf_AddScalar(const int m, const int n, const float scalar, const float *inputMatrix, float *output) {
  int i;
  const int numElements = m * n;

  for (i = 0; i < numElements; i++) {
    output[i] = inputMatrix[i] + scalar;
  }
}
void MatrixMNf_SubtractScalar(const int m, const int n, const float scalar, const float *inputMatrix, float *output) {
  int i;
  const int numElements = m * n;

  for (i = 0; i < numElements; i++) {
    output[i] = inputMatrix[i] - scalar;
  }
}

void MatrixMNf_MultiplyScalar(const int m, const int n, const float scalar, const float *inputMatrix, float *output) {
  int i;
  const int numElements = m * n;

  for (i = 0; i < numElements; i++) {
    output[i] = inputMatrix[i] * scalar;
  }
}

void matxn_multiplyPiecewise(const int m, const int n, const float *a, const float *b, float *output) {
  int i;
  const int numElements = m * n;

  for (i = 0; i < numElements; i++) {
    output[i] = a[i] * b[i];
  }
}

void MatrixMNf_Cut(const int m, const int n, const float *input, const int width, const int stride, const int offset, float *output) {
    const int numElements = m * n;
    const int jump = stride - width;
    int i = offset;
    int j = 0;
    int x;

    while (i < numElements) {
        for (x = 0; x < width; x++) {
            output[j] = input[i];
            i++;
            j++;
        }

        i += jump;
    }
}

const char *MatrixMNf_ToString(const int m, const int n, const float *input) {
  static char str[MATN_MAX_STRING_LENGTH];
  int pos = 0;

  short i, j;
  for (j = 0; j < m; j++) {
    str[pos++] = ' ';

    for (i = 0; i < n; i++) {
      str[pos++] = ' ';
      char maxStr[64];
      sprintf(maxStr, "%.3f", input[(j << 2) + i]);

      char *ptr = maxStr;
      while (*ptr != '\0') {
        str[pos++] = *ptr;
        ptr++;
      }

      str[pos++] = ' ';
    }

    str[pos++] = '\n';
  }

  return str;
}
