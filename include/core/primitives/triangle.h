#ifndef TRIANGlE_H
#define TRIANGLE_H

#include <core/primitives/vertex.h>

namespace Core
{
    namespace Primitives
    {
        struct Triangle
        {
        public:
            Triangle();
            Triangle(Vertex v0, Vertex v1, Vertex v2);
            Triangle(const Triangle& tri);
            ~Triangle();

            Vertex vertices[3];             // Three vertices in a triangle
        };
        
    }
}

#endif // TRIANGLE_H