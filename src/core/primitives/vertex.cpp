#include <core/primitives/vertex.h>

using namespace Core::Primitives;

Vertex::Vertex()
    : color{Core::Math::Vector4(1.0, 1.0, 1.0, 1.0)}
    , pos{Core::Math::Vector4(0.0, 0.0, 0.0, 1.0)}
    , normal{Core::Math::Vector3(0.0, 0.0, 0.0)}
    , textcoord{Core::Math::Vector2(0.0, 0.0)}
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

void Vertex::SetColor(double r, double g, double b, double a)
{
    if (
        (r < 0.0) || (r > 255.0) || 
        (g < 0.0) || (g > 255.0) || 
        (b < 0.0) || (b > 255.0) ||
        (a < 0.0) || (a > 255.0)
    )
    {
        throw std::runtime_error("Invalid color values");
    }

    this->color = Core::Math::Vector4(r, g, b, a);
}

void Vertex::SetPos(double x, double y, double z, double w)
{
    this->pos = Core::Math::Vector4(x, y, z, w);
}

void Vertex::SetNormal(double x, double y, double z)
{
    this->normal = Core::Math::Vector3(x, y, z);
}