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
            ~DepthBuffer();

            double GetDepth(int x, int y) const;                            // Get Depth
            void SetDepth(int x, int y, double depth);                      // Set Depth
            void Clear(double default_depth = 1.0);                         // Clear buffer

            int GetWidth() const;                                           // Get buffer width
            int GetHeight() const;                                          // Get buffer height

        private:
            int width;
            int height;
            std::vector<double> data;                                       // store the value of depth
        };
    }
}

#endif // DEPTHBUFFER_H