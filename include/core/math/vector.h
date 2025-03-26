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
            float x;
            float y;

            Vector2() noexcept;
            Vector2(float x, float y) noexcept;
            Vector2(const Vector2& vec) noexcept;
            ~Vector2() noexcept;

            // Operator Overloading
            Vector2 operator+ (const Vector2& vec) const noexcept;
            Vector2 operator- (const Vector2& vec) const noexcept;
            Vector2 operator* (float k) const noexcept;
            Vector2& operator= (const Vector2& other) noexcept;

            // Vector Operation
            float Dot(const Vector2& vec) const noexcept;
            float Cross(const Vector2& vec) const noexcept; 
            Vector2 Normalize() const;
            void NormalizeSelf();

            float Magnitude() const noexcept;

            static float Dot(const Vector2& vec1, const Vector2& vec2) noexcept;
            static float Cross(const Vector2& vec1, const Vector2& vec2) noexcept;

            // Debug Tools
            void PrintVec() const noexcept;
            

        private:

        };

        struct Vector3
        {
        public:
            float x;
            float y;
            float z;

            Vector3() noexcept;
            Vector3(float x, float y, float z) noexcept;
            Vector3(const Vector3& vec) noexcept;
            ~Vector3() noexcept;

            // Operator Overloading
            Vector3 operator+ (const Vector3& vec) const noexcept;
            Vector3 operator- (const Vector3& vec) const noexcept;
            Vector3 operator* (float k) const noexcept;
            Vector3& operator= (const Vector3& other) noexcept;

            // Vector Operation
            float Dot(const Vector3& vec) const noexcept;
            Vector3 Cross(const Vector3& vec) const noexcept;
            Vector3 Normalize() const;
            void NormalizeSelf();
            float Magnitude() const noexcept;

            static float Dot(const Vector3& vec1, const Vector3& vec2) noexcept;
            static Vector3 Cross(const Vector3& vec1, const Vector3& vec2) noexcept;

            // Debug Tools
            void PrintVec() const noexcept;

        private:

        };

        // For Color(RGBA) and homogeneous coordinate(XYZW)
        struct Vector4
        {
        public:
            float x;
            float y;
            float z;
            float w;

            Vector4() noexcept;
            Vector4(float x, float y, float z, float w) noexcept;
            Vector4(const Vector4& vec) noexcept;
            ~Vector4() noexcept;

            // Operator Overloading
            Vector4 operator+ (const Vector4& vec) const noexcept;
            Vector4 operator- (const Vector4& vec) const noexcept;
            Vector4 operator* (float k) const noexcept;
            Vector4& operator= (const Vector4& other) noexcept;

            // Vector Operation
            float Dot(const Vector4& vec) const noexcept;
            Vector4 Normalize() const;
            void NormalizeSelf();
            float Magnitude() const noexcept;

            static float Dot(const Vector4& vec1, const Vector4& vec2) noexcept;

            // Debug Tool
            void PrintVec() const noexcept;
        };
    }
}

#endif  // VECTOR_H