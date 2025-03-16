#include <core/buffer/depthbuffer.h>

using namespace Core::Buffer;

DepthBuffer::DepthBuffer(int width, int height)
    : width{width}
    , height{height}
{

}

DepthBuffer::~DepthBuffer() = default;

double DepthBuffer::GetDepth(int x, int y) const
{
    if (x >= 0 && x < this->width && y >= 0 && y < this->height)
    {
        return this->data[y * this->width + x];
    }
    return 1.0;
}

void DepthBuffer::SetDepth(int x, int y, double depth)
{
    if (x >= 0 && x < this->width && y >= 0 && y < this->height)
    {
        this->data[y * this->width + x] = depth;
    }
}

void DepthBuffer::Clear(double default_depth)
{
    std::fill(this->data.begin(), this->data.end(), default_depth);
}

int DepthBuffer::GetWidth() const
{
    return this->width;
}

int DepthBuffer::GetHeight() const
{
    return this->height;
}