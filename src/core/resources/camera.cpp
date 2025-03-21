#include <core/resources/camera.h>

#include <cmath>

using namespace Core::Resources;

PerspectiveCamera::PerspectiveCamera()
    : pos{Core::Math::Vector3{0.0f, 0.0f, 0.0f}}
    , look_at{Core::Math::Vector3{0.0f, 0.0f, -1.0f}}
    , up{Core::Math::Vector3{0.0f, 1.0f, 0.0f}}
    , fov{60.0f}
    , aspect_ratio{1.33f}
    , near_clip{0.1f}
    , far_clip{100.0f}
{

}

PerspectiveCamera::~PerspectiveCamera() = default;

Core::Math::Matrix4x4 PerspectiveCamera::GetViewMatrix() const
{
    // Set view transformation matrix
    Core::Math::Matrix4x4 view_translation_matrix;
    view_translation_matrix.element[0][0] = 1.0f;
    view_translation_matrix.element[1][1] = 1.0f;
    view_translation_matrix.element[2][2] = 1.0f;
    view_translation_matrix.element[3][3] = 1.0f;
    view_translation_matrix.element[0][3] = -this->pos.x;
    view_translation_matrix.element[0][3] = -this->pos.y;
    view_translation_matrix.element[0][3] = -this->pos.z;

    Core::Math::Matrix4x4 view_rotation_matrix;
    Core::Math::Vector3 right_hand_side = this->look_at.Cross(this->up);
    view_rotation_matrix.element[0][0] = right_hand_side.x;
    view_rotation_matrix.element[0][1] = right_hand_side.y;
    view_rotation_matrix.element[0][2] = right_hand_side.z;
    view_rotation_matrix.element[1][0] = this->up.x;
    view_rotation_matrix.element[1][1] = this->up.y;
    view_rotation_matrix.element[1][2] = this->up.z;
    view_rotation_matrix.element[2][0] = -this->look_at.x;
    view_rotation_matrix.element[2][1] = -this->look_at.y;
    view_rotation_matrix.element[2][2] = -this->look_at.z;
    view_rotation_matrix.element[3][3] = 1.0f;

    return view_rotation_matrix * view_translation_matrix;
}

Core::Math::Matrix4x4 PerspectiveCamera::GetProjectionMatrix() const
{
    float fov_radian = this->fov * (M_PI / 180.0f);

    Core::Math::Matrix4x4 projection_matrix;
    projection_matrix.element[0][0] = 1 / (this->aspect_ratio * std::tanf(fov_radian / 2));
    projection_matrix.element[1][1] = 1 / (std::tanf(fov_radian / 2));
    projection_matrix.element[2][2] = -(this->far_clip + this->near_clip) / (this->far_clip - this->near_clip);
    projection_matrix.element[2][3] = -(2 * this->near_clip * this->far_clip) / (this->far_clip - this->near_clip);
    projection_matrix.element[3][2] = -1.0f;

    return projection_matrix;
}

OrthographicCamera::OrthographicCamera()
    : pos{Core::Math::Vector3{0.0f, 0.0f, 0.0f}}
    , look_at{Core::Math::Vector3{0.0f, 0.0f, -1.0f}}
    , up{Core::Math::Vector3{0.0f, 1.0f, 0.0f}}
    , left{-100.0f}
    , right{100.0f}
    , bottom{-100.0f}
    , top{100.0f}
    , near_clip{0.1f}
    , far_clip{100.0f}
{

}

OrthographicCamera::~OrthographicCamera() = default;

Core::Math::Matrix4x4 OrthographicCamera::GetViewMatrix() const
{
    // Set view transformation matrix
    Core::Math::Matrix4x4 view_translation_matrix;
    view_translation_matrix.element[0][0] = 1.0f;
    view_translation_matrix.element[1][1] = 1.0f;
    view_translation_matrix.element[2][2] = 1.0f;
    view_translation_matrix.element[3][3] = 1.0f;
    view_translation_matrix.element[0][3] = -this->pos.x;
    view_translation_matrix.element[0][3] = -this->pos.y;
    view_translation_matrix.element[0][3] = -this->pos.z;

    Core::Math::Matrix4x4 view_rotation_matrix;
    Core::Math::Vector3 right_hand_side = this->look_at.Cross(this->up);
    view_rotation_matrix.element[0][0] = right_hand_side.x;
    view_rotation_matrix.element[0][1] = right_hand_side.y;
    view_rotation_matrix.element[0][2] = right_hand_side.z;
    view_rotation_matrix.element[1][0] = this->up.x;
    view_rotation_matrix.element[1][1] = this->up.y;
    view_rotation_matrix.element[1][2] = this->up.z;
    view_rotation_matrix.element[2][0] = -this->look_at.x;
    view_rotation_matrix.element[2][1] = -this->look_at.y;
    view_rotation_matrix.element[2][2] = -this->look_at.z;
    view_rotation_matrix.element[3][3] = 1.0f;

    return view_rotation_matrix * view_translation_matrix;
}

Core::Math::Matrix4x4 OrthographicCamera::GetProjectionMatrix() const
{
    Core::Math::Matrix4x4 projection_matrix;
    projection_matrix.element[0][0] = 2 / (this->right - this->left);
    projection_matrix.element[1][1] = 2 / (this->top - this->bottom);
    projection_matrix.element[2][2] = 2 / (this->near_clip - this->far_clip);
    projection_matrix.element[0][3] = -(this->right + this->left) / (this->right - this->left);
    projection_matrix.element[1][3] = -(this->top + this->bottom) / (this->top - this->bottom);
    projection_matrix.element[2][3] = -(this->near_clip + this->far_clip) / (this->near_clip - this->far_clip);
    projection_matrix.element[3][3] = 1.0f;

    return projection_matrix;
}