/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "RadiantMath.h"
#include <math.h>

void Vector3f_Add(const float a[], const float b[], float *output) {
  output[0] = a[0] + b[0];
  output[1] = a[1] + b[1];
  output[2] = a[2] + b[2];
}

void Vector3f_Subtract(const float a[], const float b[], float *output) {
  output[0] = a[0] - b[0];
  output[1] = a[1] - b[1];
  output[2] = a[2] - b[2];
}

void Vector3f_PiecewiseMultiply(const float a[], const float b[], float *output) {
  output[0] = a[0] * b[0];
  output[1] = a[1] * b[1];
  output[2] = a[2] * b[2];
}

float Vector3f_DotProduct(const float a[], const float b[]) {
  return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

float Vector3f_Magnitude(const float input[]) {
  return FastSquareRoot((input[0] * input[0]) + (input[1] * input[1]) + (input[2] * input[2]));
}

void Vector3f_Normalize(const float input[], float *output) {
  const float selfDot = (input[0] * input[0]) + (input[1] * input[1]) + (input[2] * input[2]);
  const float magnitudeReciprocal = FastInverseSquareRoot(selfDot);

  output[0] = input[0] * magnitudeReciprocal;
  output[1] = input[1] * magnitudeReciprocal;
  output[2] = input[2] * magnitudeReciprocal;
}

void Vector3f_Scale(const float input[], const float scalar, float *output) {
  output[0] = input[0] * scalar;
  output[1] = input[1] * scalar;
  output[2] = input[2] * scalar;
}

void Vector3f_CrossProduct(const float a[], const float b[], float *output) {
  output[0] = (a[1] * b[2]) - (a[2] * b[1]);
  output[1] = (a[2] * b[0]) - (a[0] * b[2]);
  output[2] = (a[0] * b[1]) - (a[1] * b[0]);
}

float Vector3f_AngleBetweenVectors(const float a[], const float b[]) {
  const float dot = (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
  const float selfDotA = (a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]);
  const float selfDotB = (b[0] * b[0]) + (b[1] * b[1]) + (b[2] * b[2]);
  const float magA = FastSquareRoot(selfDotA);
  const float magB = FastSquareRoot(selfDotB);

  return acos(dot * magA * magB);
}
