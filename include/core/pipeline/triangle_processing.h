#ifndef TRIANGLE_PROCESSING_H
#define TRIANGLE_PROCESSING_H

#include <vector>
#include <cstdint>

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

            std::vector<Core::Primitives::Triangle> Processing(
                const std::vector<Core::Primitives::Vertex>& vertices,
                const std::vector<uint32_t>& indices) const;

        private:
            void BackfaceCulling(std::vector<Core::Primitives::Triangle>& triangles) const;
            void FrustumClipping(std::vector<Core::Primitives::Triangle>& triangles) const;
        };
    }
}

#endif // TRIANGLE_PROCESSING_H