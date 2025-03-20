#include <core/resources/camera.h>

using namespace Core::Resources;

Camera::Camera()
    : pos{Core::Math::Vector3{0.0f, 0.0f, 0.0f}}
    , look_at{Core::Math::Vector3{0.0f, 0.0f, -1.0f}}
    , up{Core::Math::Vector3{0.0f, 1.0f, 0.0f}}
    , fov{60.0f}
    , aspect_ratio{1.33f}
    , near_clip{0.1f}
    , far_clip{100.0f}
{

}

Camera::~Camera() = default;