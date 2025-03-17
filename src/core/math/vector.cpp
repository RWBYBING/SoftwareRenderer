#include <core/math/vector.h>

using namespace Core::Math;

Vector2::Vector2() : x{0}, y{0} {}

Vector2::Vector2(float x, float y) : x{x}, y{y} {}

Vector2::Vector2(const Vector2& vec) : x{vec.x}, y{vec.y} {}

Vector2::~Vector2() = default;

Vector2& Vector2::operator=(const Vector2& other) = default;

Vector2 Vector2::operator+(const Vector2& vec) const 
{
    return Vector2(this->x + vec.x, this->y + vec.y);
}

Vector2 Vector2::operator-(const Vector2& vec) const
{
    return Vector2(this->x - vec.x, this->y - vec.y);
}

Vector2 Vector2::operator*(float k) const
{
    return Vector2(k * this->x, k * this->y);
}

float Vector2::Dot(const Vector2& vec) const
{
    return this->x * vec.x + this->y * vec.y;
}

Vector2 Vector2::Normalize() const
{
    float mag = this->Magnitude();
    return Vector2(this->x / mag, this->y / mag);
}

float Vector2::Magnitude() const
{
    return std::sqrt(this->x * this->x + this->y * this->y);
}

float Vector2::Dot(const Vector2& vec1, const Vector2& vec2) 
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}

void Vector2::PrintVec() const 
{
    std::cout << "(" << this->x << ", " << this->y << ")" << std::endl;
}

Vector3::Vector3() : x{0}, y{0}, z{0} {}

Vector3::Vector3(float x, float y, float z) : x{x}, y{y}, z{z} {}

Vector3::Vector3(const Vector3& vec) : x{vec.x}, y{vec.y}, z{vec.z} {}

Vector3::~Vector3() = default;

Vector3& Vector3::operator=(const Vector3& other) = default;

Vector3 Vector3::operator+ (const Vector3& vec) const
{
    return Vector3(this->x + vec.x, this->y + vec.y, this->z + vec.z);
}

Vector3 Vector3::operator- (const Vector3& vec) const
{
    return Vector3(this->x - vec.x, this->y - vec.y, this->z - vec.z);
}

Vector3 Vector3::operator* (float k) const
{
    return Vector3(k * this->x, k * this->y, k * this->z);
}

float Vector3::Dot(const Vector3& vec) const
{
    return this->x * vec.x + this->y * vec.y + this->z * vec.z;
}

Vector3 Vector3::Cross(const Vector3& vec) const
{
    return Vector3(
        this->y * vec.z - this->z * vec.y,
        this->z * vec.x - this->x * vec.z,
        this->x * vec.y - this->y * vec.x
    );
}

Vector3 Vector3::Normalize() const 
{
    float mag = this->Magnitude();
    return Vector3(this->x / mag, this->y / mag, this->z / mag);
}

float Vector3::Magnitude() const 
{
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

float Vector3::Dot(const Vector3& vec1, const Vector3& vec2) 
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}

Vector3 Vector3::Cross(const Vector3& vec1, const Vector3& vec2) 
{
    return Vector3(
        vec1.y * vec2.z - vec1.z * vec2.y,
        vec1.z * vec2.x - vec1.x * vec2.z,
        vec1.x * vec2.y - vec1.y * vec2.x
    );
}

void Vector3::PrintVec() const 
{
    std::cout << "(" << this->x << ", " << this->y << ", " << this->z << ")" << std::endl;
}

Vector4::Vector4() : x{0}, y{0}, z{0}, w{0} {}

Vector4::Vector4(float x, float y, float z, float w) : x{x}, y{y}, z{z}, w{w} {}

Vector4::Vector4(const Vector4& vec) : x{vec.x}, y{vec.y}, z{vec.z}, w{vec.w} {}

Vector4::~Vector4() = default;

Vector4& Vector4::operator=(const Vector4& other) = default;

Vector4 Vector4::operator+ (const Vector4& vec) const
{
    return Vector4(this->x + vec.x, this->y + vec.y, this->z + vec.z, this->w + vec.w);
}

Vector4 Vector4::operator- (const Vector4& vec) const
{
    return Vector4(this->x - vec.x, this->y - vec.y, this->z - vec.z, this->w - vec.w);
}

Vector4 Vector4::operator* (float k) const
{
    return Vector4(k * this->x, k * this->y, k * this->z, k * this->w);
}

float Vector4::Dot(const Vector4& vec) const
{
    return this->x * vec.x + this->y * vec.y + this->z * vec.z + this->w * vec.w;
}

Vector4 Vector4::Normalize() const 
{
    float mag = Magnitude();
    return Vector4(this->x / mag, this->y / mag, this->z / mag, this->w / mag);
}

float Vector4::Magnitude() const
{
    return std::sqrt(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

float Vector4::Dot(const Vector4& vec1, const Vector4& vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z + vec1.w * vec2.w;
}

void Vector4::PrintVec() const
{
    std::cout << "(" << this->x << ", " << this->y << ", " << this->z << ", " << this->w << ")" << std::endl;
}