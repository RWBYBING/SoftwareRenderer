#include <core/buffer/framebuffer.h>

#include <cassert>

using namespace Core::Buffer;

static Core::Math::Vector4 DEFAULT_COLOR{0.0f, 0.0f, 0.0f, 1.0f};

FrameBuffer::FrameBuffer(int width, int height)
    : width{width}
    , height{height}
{
    this->data.resize(this->width * this->height * 4, 0.0f);
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            this->data.at((j * width + i) * 4) = DEFAULT_COLOR.x;
            this->data.at((j * width + i) * 4 + 1)  = DEFAULT_COLOR.y;
            this->data.at((j * width + i) * 4 + 2)  = DEFAULT_COLOR.z;
            this->data.at((j * width + i) * 4 + 3)  = DEFAULT_COLOR.w;
        }
    }
}

FrameBuffer::~FrameBuffer() = default;

Core::Math::Vector4 FrameBuffer::GetPixel(int x, int y) const
{
    if (x >= 0 && x < this->width && y >= 0 && y < this->height) 
    {
        Core::Math::Vector4 result;
        result.x = this->data.at((y * width + x) * 4);
        result.y = this->data.at((y * width + x) * 4 + 1);
        result.z = this->data.at((y * width + x) * 4 + 2);
        result.w = this->data.at((y * width + x) * 4 + 3);

        return result;
    }
    return Core::Math::Vector4{0.0f, 0.0f, 0.0f, 1.0f};
}

void FrameBuffer::SetPixel(int x, int y, const Core::Math::Vector4& color)
{
    if (x >= 0 && x < this->width && y >= 0 && y < this->height)
    {
        this->data.at((y * width + x) * 4) = color.x;
        this->data.at((y * width + x) * 4 + 1) = color.y;
        this->data.at((y * width + x) * 4 + 2) = color.z;
        this->data.at((y * width + x) * 4 + 3) = color.w;
    }
}

void FrameBuffer::Clear()
{
    
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
    assert(width > 0);
    this->width = width;
}

void FrameBuffer::SetHeight(int height)
{
    assert(height > 0);
    this->height = height;
}

void FrameBuffer::ResizeBuffer()
{
    this->data.resize(this->width * this->height * 4, 0.0f);
    for (int j = 0; j < height; ++j)
    {
        for (int i = 0; i < width; ++i)
        {
            this->data.at((j * width + i) * 4) = DEFAULT_COLOR.x;
            this->data.at((j * width + i) * 4 + 1)  = DEFAULT_COLOR.y;
            this->data.at((j * width + i) * 4 + 2)  = DEFAULT_COLOR.z;
            this->data.at((j * width + i) * 4 + 3)  = DEFAULT_COLOR.w;
        }
    }
}

float* FrameBuffer::GetBuffer()
{
    return this->data.data();
}