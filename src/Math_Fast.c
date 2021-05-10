/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "RadiantMath.h"

float FastInverseSquareRoot(float input) {
  long i;
  float x, y;

  x = input * 0.5;
  y = input;
  i = *(long *) &y;
  i = 0x5f3759df - (i >> 1);
  y = *(float *) &i;
  y = y * ( 1.5 - (x * y * y) );

  return y;
}

float FastSquareRoot(float input) {
  long i;
  float x, y;

  x = input * 0.5;
  y = input;
  i = *(long *) &y;
  i = 0x5f3759df - (i >> 1);
  y = *(float *) &i;
  y = y * ( 1.5 - (x * y * y) );
  return 1.0 / y;
}
