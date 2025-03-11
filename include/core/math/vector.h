#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <cmath>

namespace Core
{
    namespace Math
    {
        struct Vector2
        {
        public:
            double x;
            double y;

            Vector2();
            Vector2(double x, double y);
            Vector2(const Vector2& vec);
            ~Vector2();

            // Operator Overloading
            Vector2 operator+ (const Vector2& vec) const;
            Vector2 operator- (const Vector2& vec) const;
            Vector2 operator* (double k) const;

            // Vector Operation
            double Dot(const Vector2& vec) const;
            Vector2 Normalize() const;
            double Magnitude() const;

            static double Dot(const Vector2& vec1, const Vector2& vec2);

            // Debug Tools
            void PrintVec() const;
            

        private:

        };

        struct Vector3
        {
        public:
            double x;
            double y;
            double z;

            Vector3();
            Vector3(double x, double y, double z);
            Vector3(const Vector3& vec);
            ~Vector3();

            // Operator Overloading
            Vector3 operator+ (const Vector3& vec) const;
            Vector3 operator- (const Vector3& vec) const;
            Vector3 operator* (double k) const;

            // Vector Operation
            double Dot(const Vector3& vec) const;
            Vector3 Cross(const Vector3& vec) const;
            Vector3 Normalize() const;
            double Magnitude() const;

            static double Dot(const Vector3& vec1, const Vector3& vec2);
            static Vector3 Cross(const Vector3& vec1, const Vector3& vec2);

            // Debug Tools
            void PrintVec() const;

        private:

        };

        // For Color(RGBA) and homogeneous coordinate(XYZW)
        struct Vector4
        {
        public:
            double x;
            double y;
            double z;
            double w;

            Vector4();
            Vector4(double x, double y, double z, double w);
            Vector4(const Vector4& vec);
            ~Vector4();

            // Operator Overloading
            Vector4 operator+ (const Vector4& vec) const;
            Vector4 operator- (const Vector4& vec) const;
            Vector4 operator* (double k) const;

            // Vector Operation
            double Dot(const Vector4& vec) const;
            Vector4 Normalize() const;
            double Magnitude() const;

            static double Dot(const Vector4& vec1, const Vector4& vec2);

            // Debug Tool
            void PrintVec() const;
        };
    }
}

#endif  // VECTOR_H