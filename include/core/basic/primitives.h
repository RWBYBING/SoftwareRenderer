#ifndef CORE_BASIC_PRIMITIVES
#define CORE_BASIC_PRIMITIVES

#include <core/basic/settings.h>

namespace Primitives
{
    struct Vertex
    {
        Color color{1.0f, 1.0f, 1.0f, 1.0f};
        Vector4 pos{0.0f, 0.0f, 0.0f, 1.0f};
        Vector3 normal{0.0f, 0.0f, 0.0f};
    };

    struct Fragment
    {
        int x, y;                               // Position on screen
        float depth;
        Color color;
        Vector3 normal{0.0f, 0.0f, 0.0f};
    };

    struct Triangle
    {
        Vertex v0;                              // Three vertex in the triangle
        Vertex v1;
        Vertex v2;
        Vector3 normal{0.0f, 0.0f, 0.0f};
    };
}


#endif // CORE_BASIC_VERTEX