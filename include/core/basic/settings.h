#ifndef CORE_BASIC_SETTINGS_H
#define CORE_BASIC_SETTINGS_H

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

using Color = glm::vec4;                // Color: RGBA
using Vector2 = glm::vec2;              
using Vector3 = glm::vec3;
using Vector4 = glm::vec4;
using Matrix4x4 = glm::mat4x4;

enum RendererBackend
{
    Software,
    OpenGL,
    Vulkan
};

enum class Model
{
    TWO_TRIANGLES,              // Two simple triangles with the same size and different distance from the x-y plane
    CUBE,                       // A Cube with six faces
    STANDFORD_BUNNY             // The classical cute bunny                       
};


enum RenderingMode
{
    Vertex,
    LineFrame,
    Triangles
};

enum CameraMode
{
    Orthographics,
    Perspective
};

enum ShadingMode
{
    Flat,
    Gourand,
    Phong
};

enum AntiAliasingMode
{
    None,
    MSAA,
    FXAA
};


#endif // CORE_BASIC_SETTINGS_H