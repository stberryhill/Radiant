#include "RadiantMath.h"

#include <math.h>

const double PI = 3.14159265358979323846;
const double PI_OVER_180 = PI / 180.0;

float DegreesToRadians(float input) {
  return input * PI_OVER_180;
}

float RadiansToDegrees(float input) {
  return input / PI_OVER_180;
}

float MinFloat(float a, float b) {
    return a < b ? a : b;
}
float MaxFloat(float a, float b) {
    return a > b ? a : b;
}
