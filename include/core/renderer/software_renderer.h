#ifndef SOFTWARE_RENDERER_H
#define SOFTWARE_RENDERER_H

#include <core/renderer/renderer.h>

namespace Core
{
    namespace Renderer
    {
        class SoftwareRenderer : public Renderer
        {
        public:
            SoftwareRenderer();
            void Init() override;
            void SetupPipeline() override;
            void Render() override;
        };
    }
}

#endif // SOFTWARE_RENDERER_H