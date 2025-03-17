#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H

#include <core/renderer/renderer.h>

namespace Core
{
    namespace Renderer
    {
        class VulkanRenderer : public Renderer
        {
        public:
            VulkanRenderer();
            void Init() override;
            void SetupPipeline() override;
            GLuint Render() override;

            void HandleWindowResize(int width, int height) override;
            int GetTextureWidth() override;
            int GetTextureHeight() override;
        };
    }
}

#endif // VULKAN_RENDERER_H