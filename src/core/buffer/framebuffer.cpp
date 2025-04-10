#include <core/buffer/framebuffer.h>

#include <tbb/parallel_for.h>
#include <tbb/concurrent_vector.h>
#include <tbb/blocked_range2d.h>

#include <cassert>
#include <cstring>

using namespace Buffer;

FrameBuffer::FrameBuffer(int width, int height)
    : width{width}
    , height{height}
{
    this->data.resize(this->width * this->height * 4, 0.0f);
}

FrameBuffer::~FrameBuffer() = default;

Color FrameBuffer::GetPixel(int x, int y) const
{
    if (x >= 0 && x < this->width && y >= 0 && y < this->height) 
    {
        Color result;
        result.x = this->data.at((y * width + x) * 4);
        result.y = this->data.at((y * width + x) * 4 + 1);
        result.z = this->data.at((y * width + x) * 4 + 2);
        result.w = this->data.at((y * width + x) * 4 + 3);

        return result;
    }
    return Color{0.0f, 0.0f, 0.0f, 1.0f};
}

void FrameBuffer::SetPixel(int x, int y, const Color& color)
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
    // std::fill(this->data.begin(), this->data.end(), 1.0f);
    memset(data.data(), 0, data.size() * sizeof(float));
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
}

float* FrameBuffer::GetBuffer()
{
    return this->data.data();
}

void FrameBuffer::ApplyFXAA(float edgeThreshold, float edgeThresholdMin)
{
    std::vector<float> tempData(data.size());

    tbb::parallel_for(tbb::blocked_range2d<int>(0, height, 0, width),
        [&](const tbb::blocked_range2d<int>& range) {
            for (int y = range.rows().begin(); y < range.rows().end(); ++y) {
                for (int x = range.cols().begin(); x < range.cols().end(); ++x) {
                    // Current Pixel and the adjacent 8 pixels
                    Vector4 colorCenter = GetPixel(x, y);
                    Vector4 colorNW = GetPixel(x - 1, y + 1);
                    Vector4 colorNE = GetPixel(x + 1, y + 1);
                    Vector4 colorSW = GetPixel(x - 1, y - 1);
                    Vector4 colorSE = GetPixel(x + 1, y - 1);
        
                    // Calculate luma
                    float lumaCenter = CalculateLuma(colorCenter);
                    float lumaNW = CalculateLuma(colorNW);
                    float lumaNE = CalculateLuma(colorNE);
                    float lumaSW = CalculateLuma(colorSW);
                    float lumaSE = CalculateLuma(colorSE);
        
                    // Edge detection
                    float lumaMin = std::min(lumaCenter, std::min(std::min(lumaNW, lumaNE), std::min(lumaSW, lumaSE)));
                    float lumaMax = std::max(lumaCenter, std::max(std::max(lumaNW, lumaNE), std::max(lumaSW, lumaSE)));
                    float lumaRange = lumaMax - lumaMin;
        
                    // determine if to execute FXAA or not
                    if (lumaRange < std::max(edgeThresholdMin, lumaMax * edgeThreshold)) {
                        tempData[(y * width + x) * 4 + 0] = colorCenter.x;
                        tempData[(y * width + x) * 4 + 1] = colorCenter.y;
                        tempData[(y * width + x) * 4 + 2] = colorCenter.z;
                        tempData[(y * width + x) * 4 + 3] = colorCenter.w;
                        continue;
                    }
        
                    // Blend adjacent color
                    Vector4 blendedColor = (colorCenter + colorNW + colorNE + colorSW + colorSE) / 5.0f;
                    
                    // save data to the temp
                    tempData[(y * width + x) * 4 + 0] = blendedColor.x;
                    tempData[(y * width + x) * 4 + 1] = blendedColor.y;
                    tempData[(y * width + x) * 4 + 2] = blendedColor.z;
                    tempData[(y * width + x) * 4 + 3] = blendedColor.w;
                }
            }
        }
    );


    data = std::move(tempData);
}

float FrameBuffer::CalculateLuma(const Color& color) const
{
    return 0.299f * color.x + 0.587f * color.y + 0.114f * color.z;
}