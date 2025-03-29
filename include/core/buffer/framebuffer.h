#ifndef CORE_BUFFER_FRAMEBUFFER_H
#define CORE_BUFFER_FRAMEBUFFER_H

#include <vector>

#include <core/basic/primitives.h>

namespace Buffer
{
    class FrameBuffer
    {
    public:
        FrameBuffer(int width, int height);
        FrameBuffer() = delete;
        ~FrameBuffer();

        Vector4 GetPixel(int x, int y) const;                           // Get pixel
        void SetPixel(int x, int y, const Vector4& color);              // Set pixel
        void Clear();                                                   // Clear buffer
        
        int GetWidth() const;                                           // Get buffer height
        int GetHeight() const;                                          // Get buffer width
        void SetWidth(int width);                                       // Set buffer width
        void SetHeight(int height);                                     // Set buffer height
        void ResizeBuffer();                                            // Resize the buffer
        float* GetBuffer();                                             // Get the raw data

    private:
        int width;
        int height;
        std::vector<float> data;
    };
}

#endif // CORE_BUFFER_FRAMEBUFFER_H