#include <core/primitives/vertex.h>

using namespace Core::Primitives;

Vertex::Vertex()
    : color{Core::Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f)}
    , pos{Core::Math::Vector4(0.0f, 0.0f, 0.0f, 1.0f)}
    , normal{Core::Math::Vector3(0.0f, 0.0f, 0.0f)}
    , textcoord{Core::Math::Vector2(0.0f, 0.0f)}
{

}

Vertex::Vertex(Core::Math::Vector4 color, Core::Math::Vector4 pos, Core::Math::Vector3 normal, Core::Math::Vector2 textcoord)
    : color{color}
    , pos{pos}
    , normal{normal}
    , textcoord{textcoord}
{

}

Vertex::Vertex(const Vertex& vertex)
    : color{vertex.color}
    , pos{vertex.pos}
    , normal{vertex.normal}
    , textcoord{vertex.textcoord}
{

}

Vertex::~Vertex() = default;

Vertex& Vertex::operator=(const Vertex& other) = default;

void Vertex::SetColor(float r, float g, float b, float a)
{
    if (
        (r < 0.0f) || (r > 255.0f) || 
        (g < 0.0f) || (g > 255.0f) || 
        (b < 0.0f) || (b > 255.0f) ||
        (a < 0.0f) || (a > 255.0f)
    )
    {
        throw std::runtime_error("Invalid color values");
    }

    this->color = Core::Math::Vector4(r, g, b, a);
}

void Vertex::SetPos(float x, float y, float z, float w)
{
    this->pos = Core::Math::Vector4(x, y, z, w);
}

void Vertex::SetNormal(float x, float y, float z)
{
    this->normal = Core::Math::Vector3(x, y, z);
}

void Vertex::SetTexture(float u, float v)
{
    this->textcoord = Core::Math::Vector2(u, v);
}