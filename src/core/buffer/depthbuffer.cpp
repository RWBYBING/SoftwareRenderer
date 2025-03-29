#include <core/buffer/depthbuffer.h>

#include <iostream>
#include <cstring>

using namespace Buffer;

DepthBuffer::DepthBuffer(int width, int height)
    : width{width}
    , height{height}
{
    this->data.resize(width * height, -1.0f);
}

DepthBuffer::~DepthBuffer() = default;

float DepthBuffer::GetDepth(int x, int y) const
{
    if (x >= 0 && x < this->width && y >= 0 && y < this->height)
    {
        return this->data[y * this->width + x];
    }
    return 1.0;
}

void DepthBuffer::SetDepth(int x, int y, float depth)
{
    if (x >= 0 && x < this->width && y >= 0 && y < this->height)
    {
        this->data[y * this->width + x] = depth;
    }
}

void DepthBuffer::Clear(float default_depth)
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

void DepthBuffer::SetWidth(int width)
{
    this->width = width;
}

void DepthBuffer::SetHeight(int height)
{
    this->height = height;
}

void DepthBuffer::ResizeBuffer()
{
    this->data.resize(this->width * this->height, -1.0f);
}