#include <core/pipeline/triangle_processing.h>

using namespace Core::Pipeline;

TriangleProcessing::TriangleProcessing()
{

}

TriangleProcessing::~TriangleProcessing()
{

}

std::vector<Core::Primitives::Triangle> TriangleProcessing::Processing(
    const std::vector<Core::Primitives::Vertex>& vertices,
    const std::vector<uint32_t>& indices) const
{
    std::vector<Core::Primitives::Triangle> triangles;

    // 1. Triangle Assembly
    for (size_t i = 0; i < indices.size(); i += 3) {
        Core::Primitives::Triangle triangle;
        triangle.vertices[0] = vertices[indices[i]];
        triangle.vertices[1] = vertices[indices[i + 1]];
        triangle.vertices[2] = vertices[indices[i + 2]];
        triangles.push_back(triangle);
    }

    return triangles;
}