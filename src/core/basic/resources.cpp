#include <core/basic/resources.h>

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

using namespace Resources;

void Mesh::AddVertex(const Primitives::Vertex vert)
{
    this->vertices.push_back(vert);
}

void Mesh::AddTriangle(uint32_t i0, uint32_t i1, uint32_t i2)
{
    assert(i0 < this->vertices.size() && i1 < this->vertices.size() && i2 < this->vertices.size());

    this->indices.push_back(i0);
    this->indices.push_back(i1);
    this->indices.push_back(i2);
}

Matrix4x4 Mesh::GetModelMatrix() const
{
    // Set model transformation matrix
    auto translation_matrix = glm::translate(glm::mat4(1.0f), this->translation);

    auto scale_matrix = glm::scale(glm::mat4(1.0f), this->scale);

    auto rotation_matrix = glm::mat4(1.0f);
    rotation_matrix = glm::rotate(rotation_matrix, this->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f)); // X-axis
    rotation_matrix = glm::rotate(rotation_matrix, this->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f)); // Y-axis
    rotation_matrix = glm::rotate(rotation_matrix, this->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f)); // Z-axis

    return scale_matrix * (rotation_matrix * translation_matrix);
}

Matrix4x4 OrthographicCamera::GetViewMatrix() const 
{
    // Calculate the forward, right and up vectors
    Vector3 F = glm::normalize(look_at);                    // Forward
    Vector3 U = glm::normalize(up);                         // Up
    Vector3 R = glm::normalize(glm::cross(U, F));           // Right = Up × Forward
    U = glm::normalize(glm::cross(F, R));
    
    // build the rotation matrix
    Matrix4x4 view_rotation = Matrix4x4(1.0f);
    view_rotation[0][0] = R.x; view_rotation[0][1] = U.x; view_rotation[0][2] = -F.x;
    view_rotation[1][0] = R.y; view_rotation[1][1] = U.y; view_rotation[1][2] = -F.y;
    view_rotation[2][0] = R.z; view_rotation[2][1] = U.z; view_rotation[2][2] = -F.z;

    // build the translation matrix
    Matrix4x4 view_translation(1.0f);
    view_translation[3][0] = -pos.x;
    view_translation[3][1] = -pos.y;
    view_translation[3][2] = -pos.z;

    return view_rotation * view_translation;
}

Matrix4x4 OrthographicCamera::GetProjectionMatrix() const 
{
    Matrix4x4 projection(0.0f);

    // scale part
    projection[0][0] = 2.0f / (right - left);
    projection[1][1] = 2.0f / (top - bottom);
    projection[2][2] = -2.0f / (near_clip - far_clip);

    // translation part
    projection[0][3] = -(right + left) / (right - left);
    projection[1][3] = -(top + bottom) / (top - bottom);
    projection[2][3] = -(near_clip + far_clip) / (near_clip - far_clip);
    projection[3][3] = 1.0f;

    return projection;
}

Matrix4x4 PerspectiveCamera::GetViewMatrix() const 
{
    // Calculate the forward, right and up vectors
    Vector3 F = glm::normalize(look_at);                    // Forward (-Z)
    Vector3 U = glm::normalize(up);                         // Up (+Y)
    Vector3 R = glm::normalize(glm::cross(F, U));           // Right = Up × Forward (+X)

    // build the rotation matrix
    Matrix4x4 view_rotation = Matrix4x4(1.0f);
    view_rotation[0][0] = R.x; view_rotation[0][1] = U.x; view_rotation[0][2] = -F.x;
    view_rotation[1][0] = R.y; view_rotation[1][1] = U.y; view_rotation[1][2] = -F.y;
    view_rotation[2][0] = R.z; view_rotation[2][1] = U.z; view_rotation[2][2] = -F.z;

    // build the translation matrix
    Matrix4x4 view_translation(1.0f);
    view_translation[3][0] = -pos.x;
    view_translation[3][1] = -pos.y;
    view_translation[3][2] = -pos.z;

    return view_rotation * view_translation;
}


Matrix4x4 PerspectiveCamera::GetProjectionMatrix() const
{
    float fov_radian = fov * (M_PI / 180.0f);

    Matrix4x4 projection_matrix{1.0f};

    projection_matrix[0][0] = -1 / (aspect_ratio * std::tanf(fov_radian / 2));
    projection_matrix[1][1] = -1 / (std::tanf(fov_radian / 2));
    projection_matrix[2][2] = -(far_clip + near_clip) / (far_clip - near_clip);
    projection_matrix[3][2] = -(2 * near_clip * far_clip) / (far_clip - near_clip);
    projection_matrix[2][3] = 1.0f;
    projection_matrix[3][3] = 0.0f;

    return projection_matrix;
}
