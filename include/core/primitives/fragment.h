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
            int x, y;                           // Position on screen
            float depth;
            Core::Math::Vector4 color;
            Core::Math::Vector3 normal;
            Core::Math::Vector2 texcoord;

            Fragment();
            ~Fragment();
        };
    }
}

#endif // FRAGMENT_H