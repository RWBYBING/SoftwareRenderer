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
            void Render() override;
        };
    }
}

#endif // OPENGL_RENDERER_H