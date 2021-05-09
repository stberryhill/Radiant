#include "RadiantMath.h"
#include <math.h>
#include <stdio.h>

#define MAT4_MAX_STRING_LENGTH 256

/* Matrix creation */
void Matrix4f_Identity(float *output) {
  output[0] = 1.0;
  output[1] = 0.0;
  output[2] = 0.0;
  output[3] = 0.0;

  output[4] = 0.0;
  output[5] = 1.0;
  output[6] = 0.0;
  output[7] = 0.0;

  output[8]  = 0.0;
  output[9]  = 0.0;
  output[10] = 1.0;
  output[11] = 0.0;

  output[12] = 0.0;
  output[13] = 0.0;
  output[14] = 0.0;
  output[15] = 1.0;
}

void Matrix4f_PerspectiveProjection(const float fov, const float aspectRatio, const float near, const float far, float *output) {
  const float top = near * tan((fov / 2.0) * (PI_OVER_180));
  const float right = top * aspectRatio;

  output[0] = near / right;
  output[1] = 0.0;
  output[2] = 0.0;
  output[3] = 0.0;

  output[4] = 0.0;
  output[5] = near / top;
  output[6] = 0.0;
  output[7] = 0.0;

  output[8]  = 0.0;
  output[9]  = 0.0;
  output[10] = -(far + near) / (far - near);
  output[11] = -(2.0 * far * near) / (far - near);

  output[12] = 0.0;
  output[13] = 0.0;
  output[14] = -1.0;
  output[15] = 0.0;
}

void Matrix4f_OrthographicProjection(const float left, const float right, const float top, const float bottom, const float near, const float far, float *output) {
  output[0] = 2.0f/(right-left);
  output[1] =  0.0;
  output[2] = 0.0;
  output[3] = -(right+left)/(right-left);
  output[4] = 0.0;
  output[5] = 2.0f/(top-bottom);
  output[6] = 0.0;
  output[7] = -(top+bottom)/(top-bottom);
  output[8] = 0.0;
  output[9] = 0.0;
  output[10] = -2.0f/(far-near);
  output[11] = -(far+near)/(far-near);
  output[12] = 0.0;
  output[13] = 0.0;
  output[14] = 0.0;
  output[15] = 1.0;
}

void Matrix4f_Translation(const float *translation3f, float *output) {
  output[0] = 1.0;
  output[1] = 0.0;
  output[2] = 0.0;
  output[3] = translation3f[0];

  output[4] = 0.0;
  output[5] = 1.0;
  output[6] = 0.0;
  output[7] = translation3f[1];

  output[8]  = 0.0;
  output[9]  = 0.0;
  output[10] = 1.0;
  output[11] = translation3f[2];

  output[12] = 0.0;
  output[13] = 0.0;
  output[14] = 0.0;
  output[15] = 1.0;
}

void Matrix4f_Rotation(const float *rotation3f, float *output) {
  const float sinTheta = sin(rotation3f[0]);
  const float cosTheta = cos(rotation3f[0]);
  const float sinPhi   = sin(rotation3f[1]);
  const float cosPhi   = cos(rotation3f[1]);
  const float sinOmega = sin(rotation3f[2]);
  const float cosOmega = cos(rotation3f[2]);

  output[0] = cosPhi * cosOmega;
  output[1] = (sinPhi * cosOmega * sinTheta) - (sinOmega * cosTheta);
  output[2] = (-sinPhi * cosOmega * cosTheta) - (sinOmega * sinTheta);
  output[3] = 0.0;

  output[4] = cosPhi * sinOmega;
  output[5] = (cosOmega * cosTheta) + (sinPhi * sinOmega * sinTheta);
  output[6] = (cosOmega * sinTheta) - (sinPhi * sinOmega * cosTheta);
  output[7] = 0.0;

  output[8]  = sinPhi;
  output[9]  = -cosPhi * sinTheta;
  output[10] = cosPhi * cosTheta;
  output[11] = 0.0;

  output[12] = 0.0;
  output[13] = 0.0;
  output[14] = 0.0;
  output[15] = 1.0;
}

void Matrix4f_Scale(const float *scale3f, float *output) {
  output[0] = scale3f[0];
  output[1] = 0.0;
  output[2] = 0.0;
  output[3] = 0.0;

  output[4] = 0.0;
  output[5] = scale3f[1];
  output[6] = 0.0;
  output[7] = 0.0;

  output[8]  = 0.0;
  output[9]  = 0.0;
  output[10] = scale3f[2];
  output[11] = 0.0;

  output[12] = 0.0;
  output[13] = 0.0;
  output[14] = 0.0;
  output[15] = 1.0;
}

/* Matrix operations */
void Matrix4f_Add(const float *a, const float *b, float *output) {
  output[0] = a[0] + b[0];
  output[1] = a[1] + b[1];
  output[2] = a[2] + b[2];
  output[3] = a[3] + b[3];

  output[4] = a[4] + b[4];
  output[5] = a[5] + b[5];
  output[6] = a[6] + b[6];
  output[7] = a[7] + b[7];

  output[8]  = a[8] + b[8];
  output[9]  = a[9] + b[9];
  output[10] = a[10] + b[10];
  output[11] = a[11] + b[11];

  output[12] = a[12] + b[12];
  output[13] = a[13] + b[13];
  output[14] = a[14] + b[14];
  output[15] = a[15] + b[15];
}

void Matrix4f_Subtract(const float *a, const float *b, float *output) {
  output[0] = a[0] - b[0];
  output[1] = a[1] - b[1];
  output[2] = a[2] - b[2];
  output[3] = a[3] - b[3];

  output[4] = a[4] - b[4];
  output[5] = a[5] - b[5];
  output[6] = a[6] - b[6];
  output[7] = a[7] - b[7];

  output[8]  = a[8] - b[8];
  output[9]  = a[9] - b[9];
  output[10] = a[10] - b[10];
  output[11] = a[11] - b[11];

  output[12] = a[12] - b[12];
  output[13] = a[13] - b[13];
  output[14] = a[14] - b[14];
  output[15] = a[15] - b[15];
}

void Matrix4f_Multiply(const float *a, const float *b, float *output) {
  output[0] = (a[0] * b[0]) + (a[1] * b[4]) + (a[2] * b[8]) + (a[3] * b[12]);
  output[1] = (a[0] * b[1]) + (a[1] * b[5]) + (a[2] * b[9]) + (a[3] * b[13]);
  output[2] = (a[0] * b[2]) + (a[1] * b[6]) + (a[2] * b[10]) + (a[3] * b[14]);
  output[3] = (a[0] * b[3]) + (a[1] * b[7]) + (a[2] * b[11]) + (a[3] * b[15]);

  output[4] = (a[4] * b[0]) + (a[5] * b[4]) + (a[6] * b[8]) + (a[7] * b[12]);
  output[5] = (a[4] * b[1]) + (a[5] * b[5]) + (a[6] * b[9]) + (a[7] * b[13]);
  output[6] = (a[4] * b[2]) + (a[5] * b[6]) + (a[6] * b[10]) + (a[7] * b[14]);
  output[7] = (a[4] * b[3]) + (a[5] * b[7]) + (a[6] * b[11]) + (a[7] * b[15]);

  output[8]  = (a[8] * b[0]) + (a[9] * b[4]) + (a[10] * b[8]) + (a[11] * b[12]);
  output[9]  = (a[8] * b[1]) + (a[9] * b[5]) + (a[10] * b[9]) + (a[11] * b[13]);
  output[10] = (a[8] * b[2]) + (a[9] * b[6]) + (a[10] * b[10]) + (a[11] * b[14]);
  output[11] = (a[8] * b[3]) + (a[9] * b[7]) + (a[10] * b[11]) + (a[11] * b[15]);

  output[12] = (a[12] * b[0]) + (a[13] * b[4]) + (a[14] * b[8]) + (a[15] * b[12]);
  output[13] = (a[12] * b[1]) + (a[13] * b[5]) + (a[14] * b[9]) + (a[15] * b[13]);
  output[14] = (a[12] * b[2]) + (a[13] * b[6]) + (a[14] * b[10]) + (a[15] * b[14]);
  output[15] = (a[12] * b[3]) + (a[13] * b[7]) + (a[14] * b[11]) + (a[15] * b[15]);
}

const char *Matrix4f_ToString(const float *input) {
  static char str[MAT4_MAX_STRING_LENGTH];
  int pos = 0;

  short i, j;
  for (j = 0; j < 4; j++) {
    str[pos++] = ' ';

    for (i = 0; i < 4; i++) {
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
