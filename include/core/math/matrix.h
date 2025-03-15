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
            double element[4][4];
            
            Matrix4x4();
            Matrix4x4(const Matrix4x4& mat);
            Matrix4x4(const double matValue[4][4]);
            ~Matrix4x4();

            // Operator Overloading
            Matrix4x4 operator+ (const Matrix4x4& mat) const;                 // Matrix-Matrix Add
            Matrix4x4 operator- (const Matrix4x4& mat) const;                 // Matrix-Matrix Substract
            Matrix4x4 operator* (const Matrix4x4& mat) const;                 // Matrix-Matrix Multiply
            Vector4 operator* (const Vector4& vec) const;                     // Matrix-Vector Multiply
            Matrix4x4 operator* (const double k) const;                       // Matrix-Constant Multiply
            Matrix4x4& operator= (const Matrix4x4& other);

            // Get Row/Column Vector
            Vector4 GetRowVector(int i) const;
            Vector4 GetColVector(int j) const;

            // Matrix Basic
            Matrix4x4 GetTranspose() const;
            static Matrix4x4 GetIdentity();

            // Affine Transformation
            static Matrix4x4 Translation(const Vector3& vec);           
            static Matrix4x4 Scale(const Vector3& vec);
            static Matrix4x4 Rotation(double angle, _3D_Cartesian_Coord axis);

            // Debug Tool
            void PrintMat() const;
        };
    }
}

#endif // MATRIX_H