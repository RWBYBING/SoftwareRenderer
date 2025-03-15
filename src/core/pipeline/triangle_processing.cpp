#include <core/pipeline/triangle_processing.h>

using namespace Core::Pipeline;

TriangleProcessing::TriangleProcessing()
{

}

TriangleProcessing::~TriangleProcessing()
{

}

Core::Primitives::Triangle TriangleProcessing::AssembleTriangle(const Core::Primitives::Vertex& v0,
                                                                const Core::Primitives::Vertex& v1,
                                                                const Core::Primitives::Vertex& v2) const
{
    return Core::Primitives::Triangle{v0, v1, v2};
}

// void TriangleProcessing::MappingToScreenSpace(Core::Primitives::Triangle& triangle, int screenWidth, int screenHeight) const
// {
    
// }

// bool TriangleProcessing::InsideViewFrustum(const Core::Primitives::Vertex& vert) const
// {

// }