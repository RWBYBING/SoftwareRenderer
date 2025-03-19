#ifndef CAMERA_H
#define CAMERA_H

#include <core/math/vector.h>
#include <core/math/matrix.h>

namespace Core
{
    namespace Primitives
    {
        struct Camera
        {
        public:
            Core::Math::Vector3 pos;
            Core::Math::Vector3 look_at;
            Core::Math::Vector3 up;
            
            float fov;
            float aspect_ratio;
            float near_clip;
            float far_clip;

            Camera();
            ~Camera();
        };
    }
}

#endif // CAMERA_H