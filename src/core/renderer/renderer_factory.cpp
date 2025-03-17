#include <core/renderer/renderer_factory.h>

#include <core/renderer/software_renderer.h>
#include <core/renderer/opengl_renderer.h>
#include <core/renderer/vulkan_renderer.h>

using namespace Core::Renderer;

std::unique_ptr<Renderer> SoftwareRendererFactory::CreateRenderer() const
{
    return std::make_unique<SoftwareRenderer>();
}

std::unique_ptr<Renderer> OpenGLRendererFactory::CreateRenderer() const
{
    return std::make_unique<OpenGLRenderer>();
}

std::unique_ptr<Renderer> VulkanRendererFactory::CreateRenderer() const
{
    return std::make_unique<VulkanRenderer>();
}