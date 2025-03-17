#include <core/buffer/framebuffer.h>

using namespace Core::Buffer;

FrameBuffer::FrameBuffer(int width, int height)
    : width{width}
    , height{height}
{
    this->data.resize(width * height, Core::Math::Vector4{0.0, 0.0, 0.0, 1.0});
}

FrameBuffer::~FrameBuffer() = default;

Core::Math::Vector4 FrameBuffer::GetPixel(int x, int y) const
{
    if (x >= 0 && x < this->width && y >= 0 && y < this->height) 
    {
        return this->data[y * this->width + x];
    }
    return Core::Math::Vector4{0.0f, 0.0f, 0.0f, 1.0f};
}

void FrameBuffer::SetPixel(int x, int y, const Core::Math::Vector4& color)
{
    if (x >= 0 && x < this->width && y >= 0 && y < this->height)
    {
        this->data[y * this->width + x] = color;
    }
}

void FrameBuffer::Clear(const Core::Math::Vector4& default_color)
{
    std::fill(this->data.begin(), this->data.end(), default_color);
}

int FrameBuffer::GetWidth() const
{
    return this->width;
}

int FrameBuffer::GetHeight() const
{
    return this->height;
}

void FrameBuffer::SetWidth(int width)
{
    this->width = width;
}

void FrameBuffer::SetHeight(int height)
{
    this->height = height;
}

void FrameBuffer::ResizeBuffer()
{
    this->data.resize(this->width * this->height, Core::Math::Vector4{0.0, 0.0, 0.0, 1.0});
}