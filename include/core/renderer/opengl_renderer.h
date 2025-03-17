#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <core/renderer/renderer.h>

namespace Core
{
    namespace Renderer
    {
        class OpenGLRenderer : public Renderer
        {
        public:
            OpenGLRenderer();
            void Init() override;
            void SetupPipeline() override;
            GLuint Render() override;

            void HandleWindowResize(int width, int height) override;
            int GetTextureWidth() override;
            int GetTextureHeight() override;
        };
    }
}

#endif // OPENGL_RENDERER_H