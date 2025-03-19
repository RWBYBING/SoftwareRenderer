#include <core/primitives/fragment.h>

using namespace Core::Primitives;

Fragment::Fragment()
    : color{Core::Math::Vector4{1.0f, 1.0f, 1.0f, 1.0f}}
    , pos{Core::Math::Vector4{0.0f, 0.0f, 0.0f, 1.0f}}
    , normal{Core::Math::Vector3{0.0f, 0.0f, 0.0f}}
    , textcoord{Core::Math::Vector2{0.0f, 0.0f}}
{

}

Fragment::Fragment(Core::Math::Vector4 color, Core::Math::Vector4 pos, Core::Math::Vector3 normal, Core::Math::Vector2 textcoord)
    : color{color}
    , pos{pos}
    , normal{normal}
    , textcoord{textcoord}
{

}

Fragment::Fragment(const Fragment& frag)
    : color{frag.color}
    , pos{frag.pos}
    , normal{frag.normal}
    , textcoord{frag.textcoord}
{

}

Fragment::~Fragment() = default;

Fragment& Fragment::operator=(const Fragment& other) = default;

void Fragment::SetColor(float r, float g, float b, float a)
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

void Fragment::SetPos(float x, float y, float z, float w)
{
    this->pos = Core::Math::Vector4(x, y, z, w);
}

void Fragment::SetNormal(float x, float y, float z)
{
    this->normal = Core::Math::Vector3(x, y, z);
}