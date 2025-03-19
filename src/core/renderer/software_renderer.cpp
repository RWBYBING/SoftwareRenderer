#include <core/renderer/software_renderer.h>

#include <chrono>

#include <utils/timer.h>

using namespace Core::Renderer;

SoftwareRenderer::SoftwareRenderer()
    : texture_width{0}
    , texture_height{0}
    , vertex_processing_ptr{std::make_unique<Core::Pipeline::VertexProcessing>()}
    , triangle_processing_ptr{std::make_unique<Core::Pipeline::TriangleProcessing>()}
    , rasterizer_ptr{std::make_unique<Core::Pipeline::Rasterizer>()}
    , frame_buffer_ptr{std::make_shared<Core::Buffer::FrameBuffer>(100, 100)}
    , depth_buffer_ptr{std::make_shared<Core::Buffer::DepthBuffer>(100, 100)}
{

}

void SoftwareRenderer::Init()
{
    
}

void SoftwareRenderer::SetupPipeline()
{
    
}

GLuint SoftwareRenderer::Render()
{
    this->UpdateTexture();
    return this->texture;
}

void SoftwareRenderer::HandleWindowResize(int width, int height)
{
    this->CreateTexture(width, height);

    this->frame_buffer_ptr->SetWidth(width);
    this->frame_buffer_ptr->SetHeight(height);
    this->frame_buffer_ptr->ResizeBuffer();
}

int SoftwareRenderer::GetTextureWidth()
{
    return this->texture_width;
}

int SoftwareRenderer::GetTextureHeight()
{
    return this->texture_height;
}

void SoftwareRenderer::CreateTexture(int width, int height)
{
    // Generate and bind the texture
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Allocate the texture memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Update the size
    this->texture_width = width;
    this->texture_height = height;
}

void SoftwareRenderer::UpdateTexture()
{
    if (!this->frame_buffer_ptr)
    {
        return;
    }

    // Bind Texture
    glBindTexture(GL_TEXTURE_2D, this->texture);

    float* buffer = frame_buffer_ptr->GetBuffer();
    if (buffer == nullptr) {
        std::cerr << "Buffer pointer is null!" << std::endl;
        return;
    }

    glTexSubImage2D(
        GL_TEXTURE_2D,
        0, 
        0, 
        0, 
        this->frame_buffer_ptr->GetWidth(), 
        this->frame_buffer_ptr->GetHeight(), 
        GL_RGBA, 
        GL_FLOAT, 
        buffer
    );

    // Unbind Texture
    glBindTexture(GL_TEXTURE_2D, 0);
}