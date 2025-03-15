#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>

#include <core/math/vector.h>

namespace Core
{
    namespace Buffer
    {
        class FrameBuffer
        {
        public:
            FrameBuffer(int width, int height);
            ~FrameBuffer();

            Core::Math::Vector4 GetPixel(int x, int y) const;                           // Get pixel
            void SetPixel(int x, int y, const Core::Math::Vector4& color);              // Set pixel
            void Clear(const Core::Math::Vector4& default_color = 
                       Core::Math::Vector4{0.0, 0.0, 0.0, 1.0});                        // Clear buffer
            
            
            int GetWidth() const;                                                       // Get buffer height
            int GetHeight() const;                                                      // Get buffer width

        private:
            int width;
            int height;
            std::vector<Core::Math::Vector4> data;                                      // Store the value of color
        };
    }
}

#endif // FRAMEBUFFER_H