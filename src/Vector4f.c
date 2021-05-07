#include "RadiantMath.h"
#include <math.h>

void Vector4f_Add(const float a[], const float b[], float *output) {
  output[0] = a[0] + b[0];
  output[1] = a[1] + b[1];
  output[2] = a[2] + b[2];
  output[3] = a[3] + b[3];
}

void Vector4f_Subtract(const float a[], const float b[], float *output) {
  output[0] = a[0] - b[0];
  output[1] = a[1] - b[1];
  output[2] = a[2] - b[2];
  output[3] = a[3] - b[3];
}

void Vector4f_PiecewiseMultiply(const float a[], const float b[], float *output) {
  output[0] = a[0] * b[0];
  output[1] = a[1] * b[1];
  output[2] = a[2] * b[2];
  output[3] = a[3] * b[3];
}

float Vector4f_DotProduct(const float a[], const float b[]) {
  return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]) + (a[3] * b[3]);
}

float Vector4f_Magnitude(const float input[]) {
  return FastSquareRoot((input[0] * input[0]) + (input[1] * input[1]) + (input[2] * input[2]) + (input[3] * input[3]));
}

void Vector4f_Normalize(const float input[], float *output) {
  const float selfDot = (input[0] * input[0]) + (input[1] * input[1]) + (input[2] * input[2]) + (input[3] * input[3]);
  const float magnitudeReciprocal = FastInverseSquareRoot(selfDot);

  output[0] = input[0] * magnitudeReciprocal;
  output[1] = input[1] * magnitudeReciprocal;
  output[2] = input[2] * magnitudeReciprocal;
  output[3] = input[3] * magnitudeReciprocal;
}

void Vector4f_Scale(const float input[], const float scalar, float *output) {
  output[0] = input[0] * scalar;
  output[1] = input[1] * scalar;
  output[2] = input[2] * scalar;
  output[2] = input[3] * scalar;
}


float Vector4f_AngleBetweenVectors(const float a[], const float b[]) {
  const float dot = (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]) + (a[3] * b[3]);
  const float selfDotA = (a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]) + (a[3] * a[3]);
  const float selfDotB = (b[0] * b[0]) + (b[1] * b[1]) + (b[2] * b[2]) + (b[3] * b[3]);
  const float magA = FastSquareRoot(selfDotA);
  const float magB = FastSquareRoot(selfDotB);

  return acos(dot * magA * magB);
}
