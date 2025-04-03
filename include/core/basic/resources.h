#ifndef CORE_BASIC_RESOURCES
#define CORE_BASIC_RESOURCES

#include <vector>
#include <cstdint>

#include <core/basic/primitives.h>

namespace Resources
{
    struct Material
    {
        Color diffuse_color{0.2f, 0.2f, 0.2f, 1.0f};
        Color specular_color{1.0f, 1.0f, 1.0f, 1.0f};
        float shininess{32.0f};
    };
    
    struct Light
    {
        Vector3 dir{0.0f, 0.0f, -1.0f};
        Color diffuse_intensity{1.0f, 1.0f, 1.0f, 1.0f};
        Color specular_intensity{1.0f, 1.0f, 1.0f, 1.0f};
        Color ambient_intensity{0.3f, 0.3f, 0.3f, 1.0f};
    };
    
    struct Mesh
    {
    public:
        std::vector<Primitives::Vertex> vertices;
        std::vector<uint32_t> indices;

        Vector3 translation{0.0f, 0.0f, 0.0f};                              // Translation coefficient on xyz direction
        Vector3 rotation{0.0f, 0.0f, 0.0f};                                 // Rotation coefficient on xyz direction
        Vector3 scale{1.0f, 1.0f, 1.0f};                                    // Scale coefficient on xyz direction
        
        void AddVertex(const Primitives::Vertex vert);                      // Add a new vertex into our mesh object
        void AddTriangle(uint32_t i0, uint32_t i1, uint32_t i2);            // Add three indices of the vertex

        Matrix4x4 GetModelMatrix() const;                                   // Get the model transformation matrix
    };

    struct OrthographicCamera
    {
    public:
        Vector3 pos{0.0f, 0.0f, 10.0f};
        Vector3 look_at{0.0f, 0.0f, -1.0f};
        Vector3 up{0.0f, 1.0f, 0.0f};

        float left{-30.0f};
        float right{30.0f};
        float bottom{-30.0f};
        float top{30.0f};
        float near_clip{0.1f};
        float far_clip{30.0f};

        Matrix4x4 GetViewMatrix() const;
        Matrix4x4 GetProjectionMatrix() const;
    };

    struct PerspectiveCamera
    {
    public:
        Vector3 pos{0.0f, 0.0f, 20.0f};
        Vector3 look_at{0.0f, 0.0f, -1.0f};
        Vector3 up{0.0f, 1.0f, 0.0f};

        float fov{120.f};
        float aspect_ratio{1.33f};
        float near_clip{0.1f};
        float far_clip{100.0f};

        Matrix4x4 GetViewMatrix() const;
        Matrix4x4 GetProjectionMatrix() const;
    };
}

#endif // CORE_BASIC_RESOURCES