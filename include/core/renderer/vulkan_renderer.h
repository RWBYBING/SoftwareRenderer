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
            void Render() override;
        };
    }
}

#endif // VULKAN_RENDERER_H