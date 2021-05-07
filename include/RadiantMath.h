#ifndef _RADIANT_MATH_H
#define _RADIANT_MATH_H

#include <math.h>

extern const double PI_OVER_180;

/* Fast approximations */
float FastInverseSquareRoot(float input);
float FastSquareRoot(float input);

/* Angle conversions */
float DegreesToRadians(float input);
float RadiansToDegrees(float input);

/* min/max float */
float MinFloat(float a, float b);
float MaxFloat(float a, float b);

/* Vector operations */
void  Vector3f_Add(const float a[], const float b[], float *output);
void  Vector3f_Subtract(const float a[], const float b[], float *output);
void  Vector3f_PiecewiseMultiply(const float a[], const float b[], float *output);
float Vector3f_DotProduct(const float a[], const float b[]);
float Vector3f_Magnitude(const float input[]);
void  Vector3f_Normalize(const float input[], float *output);
void  Vector3f_Scale(const float input[], const float scalar, float *output);
void  Vector3f_CrossProduct(const float a[], const float b[], float *output);
float Vector3f_AngleBetweenVectors(const float a[], const float b[]);

void  Vector2f_Add(const float a[], const float b[], float *output);
void  Vector2f_Subtract(const float a[], const float b[], float *output);
void  Vector2f_PiecewiseMultiply(const float a[], const float b[], float *output);
float Vector2f_DotProduct(const float a[], const float b[]);
float Vector2f_Magnitude(const float input[]);
void  Vector2f_Normalize(const float input[], float *output);
void  Vector2f_Scale(const float input[], const float scalar, float *output);
float Vector2f_AngleBetweenVectors(const float a[], const float b[]);
void Vector2f_AbsoluteValue(const float input[], float *output);

/* Matrix creation */
void Matrix4f_Identity(float *output);
void Matrix4f_PerspectiveProjection(const float fov, const float aspectRatio, const float near, const float far, float *output);
void Matrix4f_OrthographicProjection(const float left, const float right, const float top, const float bottom, const float near, const float far, float *output);
void Matrix4f_Translation(const float *translation3f, float *output);
void Matrix4f_Rotation(const float *rotation3f, float *output);
void Matrix4f_Scale(const float *scale3f, float *output);
const char *Matrix4f_ToString(const float *input);

/* Matrix operations */
void Matrix4f_Add(const float *a, const float *b, float *output);
void Matrix4f_Subtract(const float *a, const float *b, float *output);
void Matrix4f_Multiply(const float *a, const float *b, float *output);

/* Arbitrary, n x n matrix operations */
void MatrixNf_Identity(const int matrixSize, float *output);
void MatrixNf_Zeros(const int matrixSize, float *output);
void MatrixNf_Ones(const int matrixSize, float *output);
void MatrixNf_Add(const int matrixSize, const float *a, const float *b, float *output);
void MatrixNf_Subtract(const int matrixSize, const float *a, const float *b, float *output);
void MatrixNf_Multiply(const int matrixSize, const float *a, const float *b, float *output);
void MatrixNf_AddScalar(const int matrixSize, const float scalar, const float *inputMatrix, float *output);
void MatrixNf_SubtractScalar(const int matrixSize, const float scalar, const float *inputMatrix, float *output);
void MatrixNf_MultiplyScalar(const int matrixSize, const float scalar, const float *inputMatrix, float *output);
void MatrixNf_MultiplyPiecewise(const int matrixSize, const float *a, const float *b, float *output);
const char *MatrixNf_ToString(const int matrixSize, const float *input);

void MatrixMNf_Zeros(const int m, const int n, float *output);
void MatrixMNf_Ones(const int m, const int n, float *output);
void MatrixMNf_Add(const int m, const int n, const float *a, const float *b, float *output);
void MatrixMNf_Subtract(const int m, const int n, const float *a, const float *b, float *output);
void MatrixMNf_AddScalar(const int m, const int n, const float scalar, const float *inputMatrix, float *output);
void MatrixMNf_SubtractScalar(const int m, const int n, const float scalar, const float *inputMatrix, float *output);
void MatrixMNf_MultiplyScalar(const int m, const int n, const float scalar, const float *inputMatrix, float *output);
void MatrixMNf_MultiplyPiecewise(const int m, const int n, const float *a, const float *b, float *output);
void MatrixMNf_Cut(const int m, const int n, const float *input, const int width, const int stride, const int offset, float *output);
const char *MatrixMNf_ToString(const int m, const int n, const float *input);

#endif
