#include <core/math/matrix.h>

#include <cassert>
#include <cstring>

using namespace Core::Math;

Matrix4x4::Matrix4x4() noexcept : element{} {}

Matrix4x4::Matrix4x4(const Matrix4x4& mat) noexcept = default;

Matrix4x4::Matrix4x4(const float matValue[4][4]) noexcept
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            element[i][j] = matValue[i][j];
        }
    }
}

Matrix4x4::~Matrix4x4() noexcept = default;

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other) noexcept = default;

Matrix4x4 Matrix4x4::operator+ (const Matrix4x4& mat) const noexcept
{
    Matrix4x4 result = Matrix4x4();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result.element[i][j] = this->element[i][j] + mat.element[i][j];
        }
    }
    return result;
}

Matrix4x4 Matrix4x4::operator- (const Matrix4x4& mat) const noexcept
{
    Matrix4x4 result = Matrix4x4();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result.element[i][j] = this->element[i][j] - mat.element[i][j];    
        }
    }
    return result;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mat) const noexcept
{
    Matrix4x4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.element[i][j] = element[i][0] * mat.element[0][j] +
                                  element[i][1] * mat.element[1][j] +
                                  element[i][2] * mat.element[2][j] +
                                  element[i][3] * mat.element[3][j];
        }
    }
    return result;
}

Vector4 Matrix4x4::operator*(const Vector4& vec) const noexcept
{
    return Vector4(
        element[0][0] * vec.x + element[0][1] * vec.y + element[0][2] * vec.z + element[0][3] * vec.w,
        element[1][0] * vec.x + element[1][1] * vec.y + element[1][2] * vec.z + element[1][3] * vec.w,
        element[2][0] * vec.x + element[2][1] * vec.y + element[2][2] * vec.z + element[2][3] * vec.w,
        element[3][0] * vec.x + element[3][1] * vec.y + element[3][2] * vec.z + element[3][3] * vec.w
    );
}

Matrix4x4 Matrix4x4::operator* (const float k) const noexcept
{
    Matrix4x4 result = Matrix4x4();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result.element[i][j] = k * this->element[i][j];
        }
    }
    return result;
}

Vector4 Matrix4x4::GetRowVector(int i) const noexcept
{
    assert(i <= 3 && i >= 0);
    return Vector4(element[i][0], element[i][1], element[i][2], element[i][3]);
}

Vector4 Matrix4x4::GetColVector(int j) const noexcept
{
    assert(j <= 3 && j >= 0);
    return Vector4(element[0][j], element[1][j], element[2][j], element[3][j]);
}

Matrix4x4 Matrix4x4::GetTranspose() const noexcept
{
    Matrix4x4 result = Matrix4x4();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            result.element[i][j] = this->element[j][i];
        }
    }
    return result;
}

Matrix4x4 Matrix4x4::GetIdentity() noexcept
{
    Matrix4x4 result = Matrix4x4();
    result.element[0][0] = 1.0;
    result.element[1][1] = 1.0;
    result.element[2][2] = 1.0;
    result.element[3][3] = 1.0;
    return result;
}

Matrix4x4 Matrix4x4::Translation(const Vector3& vec) noexcept
{
    Matrix4x4 result = GetIdentity();
    result.element[0][3] = vec.x;
    result.element[1][3] = vec.y;
    result.element[2][3] = vec.z;
    return result;
}

Matrix4x4 Matrix4x4::Scale(const Vector3& vec) noexcept
{
    Matrix4x4 result = GetIdentity();
    result.element[0][0] = vec.x;
    result.element[1][1] = vec.y;
    result.element[2][2] = vec.z;
    return result;
}

Matrix4x4 Matrix4x4::Rotation(float angle, _3D_Cartesian_Coord axis) noexcept
{
    float radian = angle * (M_PI / 180.0f);
    Matrix4x4 result = GetIdentity();
    // Rotation around X-axis
    if (axis == _3D_Cartesian_Coord::X)
    {
        result.element[1][1] = std::cosf(radian);
        result.element[1][2] = -std::sinf(radian);
        result.element[2][1] = std::sinf(radian);
        result.element[2][2] = std::cosf(radian);
    }
    // Rotation around Y-axis
    if (axis == _3D_Cartesian_Coord::Y)
    {
        result.element[0][0] = std::cosf(radian);
        result.element[0][2] = std::sinf(radian);
        result.element[2][0] = -std::sinf(radian);
        result.element[2][2] = std::cosf(radian);
    }
    // Rotation around Z-axis
    if (axis == _3D_Cartesian_Coord::Z)
    {
        result.element[0][0] = std::cosf(radian);
        result.element[0][1] = -std::sinf(radian);
        result.element[1][0] = std::sinf(radian);
        result.element[1][1] = std::cosf(radian);
    }

    return result;
}

void Matrix4x4::PrintMat() const noexcept
{
    std::cout << "Matrix4x4: " << std::endl;
    for (int i = 0; i < 4; ++i)
    {
        std::cout << "[";
        for (int j = 0; j < 4; ++j)
        {
            std::cout << this->element[i][j] << " ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << std::endl;
}