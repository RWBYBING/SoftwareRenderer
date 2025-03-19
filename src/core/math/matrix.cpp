#include <core/math/matrix.h>

#include <cassert>

using namespace Core::Math;

Matrix4x4::Matrix4x4() 
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            element[i][j] = 0.0f;
        }
    }
}

Matrix4x4::Matrix4x4(const Matrix4x4& mat)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            element[i][j] = mat.element[i][j];
        }
    }
}

Matrix4x4::Matrix4x4(const float matValue[4][4])
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            element[i][j] = matValue[i][j];
        }
    }
}

Matrix4x4::~Matrix4x4() = default;

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other) = default;

Matrix4x4 Matrix4x4::operator+ (const Matrix4x4& mat) const
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

Matrix4x4 Matrix4x4::operator- (const Matrix4x4& mat) const
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

Matrix4x4 Matrix4x4::operator* (const Matrix4x4& mat) const
{
    Matrix4x4 result = Matrix4x4();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            float temp = 0.0f;
            for (int k = 0; k < 4; ++k)
            {
                temp += this->element[i][k] * mat.element[i][k];
            }
            result.element[i][j] = temp;
        }
    }
    return result;
}

Vector4 Matrix4x4::operator* (const Vector4& vec) const
{
    Vector4 result = Vector4();
    result.x = this->GetRowVector(0).Dot(vec);
    result.y = this->GetRowVector(1).Dot(vec);
    result.z = this->GetRowVector(2).Dot(vec);
    result.w = this->GetRowVector(3).Dot(vec);
    return result;
}

Matrix4x4 Matrix4x4::operator* (const float k) const
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

Vector4 Matrix4x4::GetRowVector(int i) const
{
    assert(i <= 3 && i >= 0);
    return Vector4(element[i][0], element[i][1], element[i][2], element[i][3]);
}

Vector4 Matrix4x4::GetColVector(int j) const
{
    assert(j <= 3 && j >= 0);
    return Vector4(element[0][j], element[1][j], element[2][j], element[3][j]);
}

Matrix4x4 Matrix4x4::GetTranspose() const
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

Matrix4x4 Matrix4x4::GetIdentity()
{
    Matrix4x4 result = Matrix4x4();
    result.element[0][0] = 1.0;
    result.element[1][1] = 1.0;
    result.element[2][2] = 1.0;
    result.element[3][3] = 1.0;
    return result;
}

Matrix4x4 Matrix4x4::Translation(const Vector3& vec)
{
    Matrix4x4 result = GetIdentity();
    result.element[0][3] = vec.x;
    result.element[1][3] = vec.y;
    result.element[2][3] = vec.z;
    return result;
}

Matrix4x4 Matrix4x4::Scale(const Vector3& vec)
{
    Matrix4x4 result = GetIdentity();
    result.element[0][0] = vec.x;
    result.element[1][1] = vec.y;
    result.element[2][2] = vec.z;
    return result;
}

Matrix4x4 Matrix4x4::Rotation(float angle, _3D_Cartesian_Coord axis)
{
    float radian = angle * (M_PI / 180.0f);
    Matrix4x4 result = GetIdentity();
    // Rotation around X-axis
    if (axis == _3D_Cartesian_Coord::X)
    {
        result.element[1][1] = std::cos(radian);
        result.element[1][2] = -std::sin(radian);
        result.element[2][1] = std::sin(radian);
        result.element[2][2] = std::cos(radian);
    }
    // Rotation around Y-axis
    if (axis == _3D_Cartesian_Coord::Y)
    {
        result.element[0][0] = std::cos(radian);
        result.element[0][2] = std::sin(radian);
        result.element[2][0] = -std::sin(radian);
        result.element[2][2] = std::cos(radian);
    }
    // Rotation around Z-axis
    if (axis == _3D_Cartesian_Coord::Z)
    {
        result.element[0][0] = std::cos(radian);
        result.element[0][1] = -std::sin(radian);
        result.element[1][0] = std::sin(radian);
        result.element[1][1] = std::cos(radian);
    }

    return result;
}

void Matrix4x4::PrintMat() const
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