/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _RADIANT_MATH_H
#define _RADIANT_MATH_H

#include "RadiantAPIMacro.h"
#include <math.h>

extern const double PI_OVER_180;

/* Fast approximations */
RADIANT_API float FastInverseSquareRoot(float input);
RADIANT_API float FastSquareRoot(float input);

/* Angle conversions */
RADIANT_API float DegreesToRadians(float input);
RADIANT_API float RadiansToDegrees(float input);

/* min/max float */
RADIANT_API float MinFloat(float a, float b);
RADIANT_API float MaxFloat(float a, float b);

/* Vector operations */
RADIANT_API void  Vector3f_Add(const float a[], const float b[], float *output);
RADIANT_API void  Vector3f_Subtract(const float a[], const float b[], float *output);
RADIANT_API void  Vector3f_PiecewiseMultiply(const float a[], const float b[], float *output);
RADIANT_API float Vector3f_DotProduct(const float a[], const float b[]);
RADIANT_API float Vector3f_Magnitude(const float input[]);
RADIANT_API void  Vector3f_Normalize(const float input[], float *output);
RADIANT_API void  Vector3f_Scale(const float input[], const float scalar, float *output);
RADIANT_API void  Vector3f_CrossProduct(const float a[], const float b[], float *output);
RADIANT_API float Vector3f_AngleBetweenVectors(const float a[], const float b[]);

RADIANT_API void  Vector2f_Add(const float a[], const float b[], float *output);
RADIANT_API void  Vector2f_Subtract(const float a[], const float b[], float *output);
RADIANT_API void  Vector2f_PiecewiseMultiply(const float a[], const float b[], float *output);
RADIANT_API float Vector2f_DotProduct(const float a[], const float b[]);
RADIANT_API float Vector2f_Magnitude(const float input[]);
RADIANT_API void  Vector2f_Normalize(const float input[], float *output);
RADIANT_API void  Vector2f_Scale(const float input[], const float scalar, float *output);
RADIANT_API float Vector2f_AngleBetweenVectors(const float a[], const float b[]);
RADIANT_API void Vector2f_AbsoluteValue(const float input[], float *output);

/* Matrix creation */
RADIANT_API void Matrix4f_Identity(float *output);
RADIANT_API void Matrix4f_PerspectiveProjection(const float fov, const float aspectRatio, const float near, const float far, float *output);
RADIANT_API void Matrix4f_OrthographicProjection(const float left, const float right, const float top, const float bottom, const float near, const float far, float *output);
RADIANT_API void Matrix4f_Translation(const float *translation3f, float *output);
RADIANT_API void Matrix4f_Rotation(const float *rotation3f, float *output);
RADIANT_API void Matrix4f_Scale(const float *scale3f, float *output);
RADIANT_API const char *Matrix4f_ToString(const float *input);

/* Matrix operations */
RADIANT_API void Matrix4f_Add(const float *a, const float *b, float *output);
RADIANT_API void Matrix4f_Subtract(const float *a, const float *b, float *output);
RADIANT_API void Matrix4f_Multiply(const float *a, const float *b, float *output);

/* Arbitrary, n x n matrix operations */
RADIANT_API void MatrixNf_Identity(const int matrixSize, float *output);
RADIANT_API void MatrixNf_Zeros(const int matrixSize, float *output);
RADIANT_API void MatrixNf_Ones(const int matrixSize, float *output);
RADIANT_API void MatrixNf_Add(const int matrixSize, const float *a, const float *b, float *output);
RADIANT_API void MatrixNf_Subtract(const int matrixSize, const float *a, const float *b, float *output);
RADIANT_API void MatrixNf_Multiply(const int matrixSize, const float *a, const float *b, float *output);
RADIANT_API void MatrixNf_AddScalar(const int matrixSize, const float scalar, const float *inputMatrix, float *output);
RADIANT_API void MatrixNf_SubtractScalar(const int matrixSize, const float scalar, const float *inputMatrix, float *output);
RADIANT_API void MatrixNf_MultiplyScalar(const int matrixSize, const float scalar, const float *inputMatrix, float *output);
RADIANT_API void MatrixNf_MultiplyPiecewise(const int matrixSize, const float *a, const float *b, float *output);
RADIANT_API const char *MatrixNf_ToString(const int matrixSize, const float *input);

RADIANT_API void MatrixMNf_Zeros(const int m, const int n, float *output);
RADIANT_API void MatrixMNf_Ones(const int m, const int n, float *output);
RADIANT_API void MatrixMNf_Add(const int m, const int n, const float *a, const float *b, float *output);
RADIANT_API void MatrixMNf_Subtract(const int m, const int n, const float *a, const float *b, float *output);
RADIANT_API void MatrixMNf_AddScalar(const int m, const int n, const float scalar, const float *inputMatrix, float *output);
RADIANT_API void MatrixMNf_SubtractScalar(const int m, const int n, const float scalar, const float *inputMatrix, float *output);
RADIANT_API void MatrixMNf_MultiplyScalar(const int m, const int n, const float scalar, const float *inputMatrix, float *output);
RADIANT_API void MatrixMNf_MultiplyPiecewise(const int m, const int n, const float *a, const float *b, float *output);
RADIANT_API void MatrixMNf_Cut(const int m, const int n, const float *input, const int width, const int stride, const int offset, float *output);
RADIANT_API const char *MatrixMNf_ToString(const int m, const int n, const float *input);

#endif
