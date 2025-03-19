#ifndef VERTEX_H
#define VERTEX_H

#include <core/math/vector.h>

namespace Core
{
    namespace Primitives
    {
        struct Vertex
        {
        public:
            Vertex();
            Vertex(Core::Math::Vector4 color, Core::Math::Vector4 pos, Core::Math::Vector3 normal, Core::Math::Vector2 textcoord);
            Vertex(const Vertex& vertex);
            ~Vertex();

            // Vertex attributes
            Core::Math::Vector4 color;                  
            Core::Math::Vector4 pos;
            Core::Math::Vector3 normal;
            Core::Math::Vector2 textcoord;

            // Operator overloading
            Vertex& operator= (const Vertex& other);

            // Set attributes
            void SetColor(float r, float g, float b, float a);
            void SetPos(float x, float y, float z, float w);
            void SetNormal(float x, float y, float z);
            void SetTexture(float u, float v);

        private:

        };
    }
}

#endif  // VERTEX_H