#ifndef FRAGMENT_H
#define FRAGMENT_H

#include <core/math/vector.h>

namespace Core
{
    namespace Primitives
    {
        struct Fragment
        {
        public:
            Fragment();
            Fragment(Core::Math::Vector4 color, Core::Math::Vector4 pos, Core::Math::Vector3 normal, Core::Math::Vector2 textcoord);
            Fragment(const Fragment& vertex);
            ~Fragment();
                
            // Fragment attributes
            Core::Math::Vector4 color;
            Core::Math::Vector4 pos;
            Core::Math::Vector3 normal;
            Core::Math::Vector2 textcoord;

            // Operator overloading
            Fragment& operator= (const Fragment& other);

            // Set attributes
            void SetColor(float r, float g, float b, float a);
            void SetPos(float x, float y, float z, float w);
            void SetNormal(float x, float y, float z);

        private:

        };
    }
}

#endif // FRAGMENT_H