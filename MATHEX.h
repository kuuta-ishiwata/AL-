#pragma once
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>

Vector3 Add(const Vector3 v1, const Vector3 v2);
Vector3 Subtract(const Vector3& v1, const Vector3& v2);

Matrix4x4 Multiply(const Matrix4x4 m1, const Matrix4x4 m2);

Matrix4x4 MakeScaleMatrix(const Vector3 scale);
Matrix4x4 MakeRotateXMatrix(float radian);

Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 MakeRotateXYZMatrix(float radianX, float radianY, float radianZ);

Matrix4x4 MakeRotateMatrix(const Vector3& radian);

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);

Vector3 TransformNormal(const Vector3& v, const Matrix4x4& m);

Vector3 Normalize(const Vector3& v);

Vector3 Multiply2(const Vector3& v1, const Vector3& v2);

Matrix4x4 Inverse(const Matrix4x4& m);

Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float mindepth, float maxDepth);

Vector3 Transform(const Vector3 vecter, const Matrix4x4 matrix);

Vector3 Multiply3(const float& v1, const Vector3& v2);

Vector3 Multiply4(const float& v1, const Vector3& v2);