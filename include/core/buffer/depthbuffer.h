#ifndef CORE_BUFFER_DEPTHBUFFER_H
#define CORE_BUFFER_DEPTHBUFFER_H

#include <vector>
#include <array>

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

        // MSAA related funcs
        void SetSample(int x, int y, int sampleIdx, float depth);       // Set the depth of the sub-sample of a pixel
        float GetSample(int x, int y, int sampleIdx);                   // Get the depth of the sub-sample of a pixel
        void ClearSample(float default_depth = -1.0f);                  // Clear the sample buffer

    private:
        int width;
        int height;
        std::vector<float> data;                                        // store the value of depth
        std::vector<std::array<float, 4>> samples;                      // store the depth for MSAA Anti-aliasing
    };
}


#endif // CORE_BUFFER_DEPTHBUFFER