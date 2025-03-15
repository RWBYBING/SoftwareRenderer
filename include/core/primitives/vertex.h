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

            Core::Math::Vector4 color;                  
            Core::Math::Vector4 pos;
            Core::Math::Vector3 normal;
            Core::Math::Vector2 textcoord;

            void SetColor(double r, double g, double b, double a);
            void SetPos(double x, double y, double z, double w);
            void SetNormal(double x, double y, double z);

        private:

        };
    }
}

#endif  // VERTEX_H