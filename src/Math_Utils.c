#include "RadiantMath.h"

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
