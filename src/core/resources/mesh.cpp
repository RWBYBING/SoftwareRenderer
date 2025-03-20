#include <core/resources/mesh.h>

#include <cassert>

using namespace Core::Resources;

Mesh::Mesh()
    : vertices{}
    , indices{}
    , material{}
    , translation{0.0f, 0.0f, 0.0f}
    , rotation{0.0f, 0.0f, 0.0f}
    , scale{0.0f, 0.0f, 0.0f}
{
    
}

Mesh::~Mesh() = default;

void Mesh::AddVertex(const Core::Primitives::Vertex vert)
{
    this->vertices.push_back(vert);
}

void Mesh::AddTriangle(uint32_t i0, uint32_t i1, uint32_t i2)
{
    assert(i0 < this->vertices.size() && i1 < this->vertices.size() && i2 < this->vertices.size());

    this->indices.push_back(i0);
    this->indices.push_back(i1);
    this->indices.push_back(i2);
}