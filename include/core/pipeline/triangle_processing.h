#ifndef TRIANGLE_PROCESSING_H
#define TRIANGLE_PROCESSING_H

#include <core/primitives/triangle.h>

namespace Core
{
    namespace Pipeline
    {
        class TriangleProcessing
        {
        public:
            TriangleProcessing();
            ~TriangleProcessing();

            // Triangle Assembly
            Core::Primitives::Triangle AssembleTriangle(const Core::Primitives::Vertex& v0,
                                                        const Core::Primitives::Vertex& v1,
                                                        const Core::Primitives::Vertex& v2) const;

            // Clipping

            // Mapping to Screen
            void MappingToScreenSpace(Core::Primitives::Triangle& triangle, int screenWidth, int screenHeight) const;
          
        private:
            bool InsideViewFrustum(const Core::Primitives::Vertex& vert) const;       // Determine if a vertex is inside the view frustum
        };
    }
}

#endif // TRIANGLE_PROCESSING_H