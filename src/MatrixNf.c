/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */


#include "RadiantMath.h"
#include <stdio.h>

#define MATN_MAX_STRING_LENGTH 4096

void MatrixNf_Identity(const int matrixSize, float *output) {
  const int numElements = matrixSize * matrixSize;
  int i;

  /* TODO: optimize this */
  for (i = 0; i < numElements; i++) {
    output[i] = 0.0;
  }

  for (i = 0; i < matrixSize; i++) {
    output[(i * matrixSize) + i] = 1.0;
  }
}

void MatrixNf_Zeros(const int matrixSize, float *output) {
  const int numElements = matrixSize * matrixSize;
  int i;

  for (i = 0; i < numElements; i++) {
    output[i] = 0.0;
  }
}

void MatrixNf_Ones(const int matrixSize, float *output) {
  const int numElements = matrixSize * matrixSize;
  int i;

  for (i = 0; i < numElements; i++) {
    output[i] = 1.0;
  }
}

void MatrixNf_Add(const int matrixSize, const float *a, const float *b, float *output) {
  int i;
  const int numElements = matrixSize * matrixSize;

  for (i = 0; i < numElements; i++) {
    output[i] = a[i] + b[i];
  }
}

void MatrixNf_Subtract(const int matrixSize, const float *a, const float *b, float *output) {
  int i;
  const int numElements = matrixSize * matrixSize;

  for (i = 0; i < numElements; i++) {
    output[i] = a[i] - b[i];
  }
}

void MatrixNf_Multiply(const int matrixSize, const float *a, const float *b, float *output) {
  int eRow, eCol;
  int vectorOffset = 0;
  float dotProduct = 0.0;

  /* These two for loops are for the index of the element we are populating */
  for (eRow = 0; eRow < matrixSize; eRow++) {
    for (eCol = 0; eCol < matrixSize; eCol++) {

      /* This is the loop to step through the rows and columns of a & b accumulating the dot product */
      for (vectorOffset = 0; vectorOffset < matrixSize; vectorOffset++) {
        const float elementFromRowOfA = a[(eRow * matrixSize) + vectorOffset];
        const float elementFromColumnOfB = b[(vectorOffset * matrixSize) + eCol];
        dotProduct += elementFromRowOfA * elementFromColumnOfB;
      }

      output[(eRow * matrixSize) + eCol] = dotProduct;
    }
  }
}

void MatrixNf_AddScalar(const int matrixSize, const float scalar, const float *inputMatrix, float *output) {
  int i;
  const int numElements = matrixSize * matrixSize;

  for (i = 0; i < numElements; i++) {
    output[i] = inputMatrix[i] + scalar;
  }
}
void MatrixNf_SubtractScalar(const int matrixSize, const float scalar, const float *inputMatrix, float *output) {
  int i;
  const int numElements = matrixSize * matrixSize;

  for (i = 0; i < numElements; i++) {
    output[i] = inputMatrix[i] - scalar;
  }
}

void MatrixNf_MultiplyScalar(const int matrixSize, const float scalar, const float *inputMatrix, float *output) {
  int i;
  const int numElements = matrixSize * matrixSize;

  for (i = 0; i < numElements; i++) {
    output[i] = inputMatrix[i] * scalar;
  }
}

void MatrixNf_MultiplyPiecewise(const int matrixSize, const float *a, const float *b, float *output) {
  int i;
  const int numElements = matrixSize * matrixSize;

  for (i = 0; i < numElements; i++) {
    output[i] = a[i] * b[i];
  }
}

const char *MatrixNf_ToString(const int matrixSize, const float *input) {
  static char str[MATN_MAX_STRING_LENGTH];
  int pos = 0;

  short i, j;
  for (j = 0; j < matrixSize; j++) {
    str[pos++] = ' ';

    for (i = 0; i < matrixSize; i++) {
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
