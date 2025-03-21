#include <core/primitives/fragment.h>

using namespace Core::Primitives;

Fragment::Fragment()
    : x{0}, y{0}
    , color{Core::Math::Vector4{0.0f, 0.0f, 0.0f, 1.0f}}
    , normal{Core::Math::Vector3{0.0f, 0.0f, 0.0f}}
    , texcoord{Core::Math::Vector2{0.0f, 0.0f}}
{

}

Fragment::~Fragment() = default;