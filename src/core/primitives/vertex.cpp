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