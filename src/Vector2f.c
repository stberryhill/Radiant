#include "RadiantMath.h"
#include <math.h>

void Vector2f_Add(const float a[], const float b[], float *output) {
  output[0] = a[0] + b[0];
  output[1] = a[1] + b[1];
}

void Vector2f_Subtract(const float a[], const float b[], float *output) {
  output[0] = a[0] - b[0];
  output[1] = a[1] - b[1];
}

void Vector2f_PiecewiseMultiply(const float a[], const float b[], float *output) {
  output[0] = a[0] * b[0];
  output[1] = a[1] * b[1];
}

float Vector2f_DotProduct(const float a[], const float b[]) {
  return (a[0] * b[0]) + (a[1] * b[1]);
}

float Vector2f_Magnitude(const float input[]) {
  return FastSquareRoot((input[0] * input[0]) + (input[1] * input[1]));
}

void Vector2f_Normalize(const float input[], float *output) {
  const float selfDot = (input[0] * input[0]) + (input[1] * input[1]);
  const float magnitudeReciprocal = FastInverseSquareRoot(selfDot);

  output[0] = input[0] * magnitudeReciprocal;
  output[1] = input[1] * magnitudeReciprocal;
}

void Vector2f_Scale(const float input[], const float scalar, float *output) {
  output[0] = input[0] * scalar;
  output[1] = input[1] * scalar;
}

float Vector2f_AngleBetweenVectors(const float a[], const float b[]) {
  const float dot = (a[0] * b[0]) + (a[1] * b[1]);
  const float selfDotA = (a[0] * a[0]) + (a[1] * a[1]);
  const float selfDotB = (b[0] * b[0]) + (b[1] * b[1]);
  const float magA = FastSquareRoot(selfDotA);
  const float magB = FastSquareRoot(selfDotB);

  return acos(dot * magA * magB);
}

void Vector2f_AbsoluteValue(const float input[], float *output) {
  output[0] = fabsf(input[0]);
  output[1] = fabsf(input[1]);
}
