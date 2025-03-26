#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>

#include <core/math/vector.h>

namespace Core
{
    namespace Math
    {
        enum _3D_Cartesian_Coord
        {
            X,
            Y,
            Z
        };

        struct Matrix4x4
        {
        public:
            float element[4][4];
            
            Matrix4x4() noexcept;
            Matrix4x4(const Matrix4x4& mat) noexcept;
            Matrix4x4(const float matValue[4][4]) noexcept;
            ~Matrix4x4() noexcept;

            // Operator Overloading
            Matrix4x4 operator+ (const Matrix4x4& mat) const noexcept;                 // Matrix-Matrix Add
            Matrix4x4 operator- (const Matrix4x4& mat) const noexcept;                 // Matrix-Matrix Substract
            Matrix4x4 operator* (const Matrix4x4& mat) const noexcept;                 // Matrix-Matrix Multiply
            Vector4 operator* (const Vector4& vec) const noexcept;                     // Matrix-Vector Multiply
            Matrix4x4 operator* (const float k) const noexcept;                        // Matrix-Constant Multiply
            Matrix4x4& operator= (const Matrix4x4& other) noexcept;

            // Get Row/Column Vector
            Vector4 GetRowVector(int i) const noexcept;
            Vector4 GetColVector(int j) const noexcept;

            // Matrix Basic
            Matrix4x4 GetTranspose() const noexcept;
            static Matrix4x4 GetIdentity() noexcept;

            // Affine Transformation
            static Matrix4x4 Translation(const Vector3& vec) noexcept;           
            static Matrix4x4 Scale(const Vector3& vec) noexcept;
            static Matrix4x4 Rotation(float angle, _3D_Cartesian_Coord axis) noexcept;

            // Debug Tool
            void PrintMat() const noexcept;
        };
    }
}

#endif // MATRIX_H