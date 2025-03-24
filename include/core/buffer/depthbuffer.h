#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H

#include <vector>

namespace Core
{
    namespace Buffer
    {
        class DepthBuffer
        {
        public:
            DepthBuffer(int width, int height);
            DepthBuffer() = delete;
            ~DepthBuffer();

            float GetDepth(int x, int y) const;                            // Get Depth
            void SetDepth(int x, int y, float depth);                      // Set Depth
            void Clear(float default_depth = -1.0f);                       // Clear buffer

            int GetWidth() const;                                           // Get buffer width
            int GetHeight() const;                                          // Get buffer height
            void SetWidth(int width);                                       // Set buffer width
            void SetHeight(int height);                                     // Set buffer height
            void ResizeBuffer();                                            // Resize the buffer memory

        private:
            int width;
            int height;
            std::vector<float> data;                                       // store the value of depth
        };
    }
}

#endif // DEPTHBUFFER_H