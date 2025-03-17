#ifndef RENDERER_FACTORY_H
#define RENDERER_FACTORY_H

#include <memory>

#include <core/renderer/renderer.h>

namespace Core
{
    namespace Renderer
    {
        class RendererFactory
        {
        public:
            virtual std::unique_ptr<Renderer> CreateRenderer() const = 0;
            virtual ~RendererFactory() = default;
        };

        class SoftwareRendererFactory : public RendererFactory
        {
        public:
            virtual std::unique_ptr<Renderer> CreateRenderer() const override;
        };

        class OpenGLRendererFactory : public RendererFactory
        {
        public:
            virtual std::unique_ptr<Renderer> CreateRenderer() const override;
        };

        class VulkanRendererFactory : public RendererFactory
        {
        public:
            virtual std::unique_ptr<Renderer> CreateRenderer() const override;  
        };
    }
}

#endif // RENDERER_FACTORY_H