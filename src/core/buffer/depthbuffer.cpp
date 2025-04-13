#include <core/buffer/depthbuffer.h>

#include <iostream>
#include <cstring>

using namespace Buffer;

DepthBuffer::DepthBuffer(int width, int height)
    : width{width}
    , height{height}
{
    this->data.resize(width * height, -1.0f);
    this->samples.resize(width * height, {-1.0f, -1.0f, -1.0f, -1.0f});
}

DepthBuffer::~DepthBuffer() = default;

float DepthBuffer::GetDepth(int x, int y) const
{
    if (x >= 0 && x < this->width && y >= 0 && y < this->height)
    {
        return this->data[y * this->width + x];
    }
    return -1.0;
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

void DepthBuffer::ClearSample(float default_depth)
{
    std::fill(
        this->samples.begin(),
        this->samples.end(),
        std::array<float, 4>{default_depth, default_depth, default_depth, default_depth}
    );
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
    this->data.resize(width * height, -1.0f);
    this->samples.resize(width * height, {-1.0f, -1.0f, -1.0f, -1.0f});
}

void DepthBuffer::SetSample(int x, int y, int sampleIdx, float depth)
{
    this->samples[y * this->width + x][sampleIdx] = depth;
}

float DepthBuffer::GetSample(int x, int y, int sampleIdx)
{
    return this->samples[y * this->width + x][sampleIdx];
}

// int DepthBuffer::GetCoverage(int x, int y, float currentDepth) const
// {
//     int count = 0;
//     for (int k = 0; k < 4; ++k) {
//         if (currentDepth <= samples[y * width + x][k]) 
//         {
//             count++;
//         }
//     }

//     return count;
// }