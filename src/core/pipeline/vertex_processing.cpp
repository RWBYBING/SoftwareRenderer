#include <core/pipeline/vertex_processing.h>

using namespace Core::Pipeline;

VertexProcessing::VertexProcessing()
{

}

VertexProcessing::~VertexProcessing() = default;


std::vector<Core::Primitives::Vertex> VertexProcessing::TransformMesh() const
{
    std::vector<Core::Primitives::Vertex> vertices;

    // // Set model transformation matrix
    // auto translation_matrix = Core::Math::Matrix4x4::Translation(this->mesh_ptr->translation);
    // auto scale_matrix = Core::Math::Matrix4x4::Scale(this->mesh_ptr->scale);
    // auto rotation_matrix = (
    //     Core::Math::Matrix4x4::Rotation(this->mesh_ptr->rotation.x, Core::Math::_3D_Cartesian_Coord::X) *
    //     Core::Math::Matrix4x4::Rotation(this->mesh_ptr->rotation.y, Core::Math::_3D_Cartesian_Coord::Y) *
    //     Core::Math::Matrix4x4::Rotation(this->mesh_ptr->rotation.z, Core::Math::_3D_Cartesian_Coord::Z)
    // );

    // auto model_matrix = scale_matrix * (rotation_matrix * translation_matrix);

    // // Set view transformation matrix
    // Core::Math::Matrix4x4 view_translation_matrix;
    // view_translation_matrix.element[0][0] = 1.0f;
    // view_translation_matrix.element[1][1] = 1.0f;
    // view_translation_matrix.element[2][2] = 1.0f;
    // view_translation_matrix.element[3][3] = 1.0f;
    // view_translation_matrix.element[0][3] = -this->camera_ptr->pos.x;
    // view_translation_matrix.element[0][3] = -this->camera_ptr->pos.y;
    // view_translation_matrix.element[0][3] = -this->camera_ptr->pos.z;

    // Core::Math::Matrix4x4 view_rotation_matrix;
    // Core::Math::Vector3 right_hand_side = this->camera_ptr->look_at.Cross(this->camera_ptr->up);
    // view_rotation_matrix.element[0][0] = right_hand_side.x;
    // view_rotation_matrix.element[0][1] = right_hand_side.y;
    // view_rotation_matrix.element[0][2] = right_hand_side.z;
    // view_rotation_matrix.element[1][0] = this->camera_ptr->up.x;
    // view_rotation_matrix.element[1][1] = this->camera_ptr->up.y;
    // view_rotation_matrix.element[1][2] = this->camera_ptr->up.z;
    // view_rotation_matrix.element[2][0] = -this->camera_ptr->look_at.x;
    // view_rotation_matrix.element[2][1] = -this->camera_ptr->look_at.y;
    // view_rotation_matrix.element[2][2] = -this->camera_ptr->look_at.z;
    // view_rotation_matrix.element[3][3] = 1.0f;

    // auto view_matrix = view_rotation_matrix * view_translation_matrix;

    // // Set projection transformation matix(Perspective)
    // Core::Math::Matrix4x4 perspective_projection_matrix;
    




    // // Apply MVP transformation on each vertex
    

    return vertices;
}

// Core::Primitives::Vertex VertexProcessing::TransformVertex(const Core::Primitives::Vertex& vert) const
// {
//     Core::Primitives::Vertex result = vert;

//     // Set model transformation matrix


//     // Apply MVP transformation
//     result.pos = this->projection_matrix * (this->view_matrix * (this->model_matrix * result.pos));

//     return result;
// }