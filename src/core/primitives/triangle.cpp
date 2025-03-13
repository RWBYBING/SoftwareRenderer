#include <core/primitives/triangle.h>

using namespace Core::Primitives;

Triangle::Triangle()
{   
    this->vertices[0] = Vertex();
    this->vertices[1] = Vertex();
    this->vertices[2] = Vertex();
}

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2)
{
    this->vertices[0] = v0;
    this->vertices[1] = v1;
    this->vertices[2] = v2;
}

Triangle::Triangle(const Triangle& tri)
{
    this->vertices[0] = tri.vertices[0];
    this->vertices[1] = tri.vertices[1];
    this->vertices[2] = tri.vertices[2];
}

Triangle::~Triangle() = default;

