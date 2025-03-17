#ifndef RENDERER_H
#define RENDERER_H

#include <GL3W/gl3w.h>

namespace Core
{
    namespace Renderer
    {
        class Renderer
        {
        public:
            virtual ~Renderer() = default;
            virtual void Init() = 0;                                            
            virtual void SetupPipeline() = 0;                                   
            virtual GLuint Render() = 0;                                                // Get the final result

            virtual void HandleWindowResize(int width, int height) = 0;                 // Change texture size when window size changed
            virtual int GetTextureWidth() = 0;                                       
            virtual int GetTextureHeight() = 0;
        };
    }
}

#endif  // RENDERER_H