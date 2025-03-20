#include <core/resources/material.h>

using namespace Core::Resources;

Material::Material()
    : diffuse_color{Core::Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f)}
    , specular_color{Core::Math::Vector4{0.0f, 0.0f, 0.0f, 1.0f}}
    , shininess{32.0f}
{

}

Material::~Material() = default;