#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>

#include <core/math/vector.h>

namespace Core
{
    namespace Resources
    {
        struct Material
        {
        public:
            Core::Math::Vector4 diffuse_color;
            Core::Math::Vector4 specular_color;
            float shininess;

            Material();
            ~Material();
        };
    }
}

#endif // MATERIAL_H