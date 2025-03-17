#include <core/renderer/software_renderer.h>

#include <chrono>

using namespace Core::Renderer;

inline std::vector<float> ConvertFrameBuffer2Vector(std::shared_ptr<Core::Buffer::FrameBuffer> buffer)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<float> result;
    result.reserve(buffer->GetWidth() * buffer->GetHeight() * 4);

    for (int i = 0; i < buffer->GetWidth(); ++i)
    {
        for (int j = 0; j < buffer->GetHeight(); ++j)
        {
            auto color = buffer->GetPixel(i, j);
            result.push_back(color.x);
            result.push_back(color.y);
            result.push_back(color.z);
            result.push_back(color.w);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << duration.count() << " ms" << std::endl;

    return result;
}

SoftwareRenderer::SoftwareRenderer()
    : texture_width{0}
    , texture_height{0}
    , vertex_processing_ptr{std::make_unique<Core::Pipeline::VertexProcessing>()}
    , triangle_processing_ptr{std::make_unique<Core::Pipeline::TriangleProcessing>()}
    , rasterizer_ptr{std::make_unique<Core::Pipeline::Rasterizer>()}
    , frame_buffer_ptr{std::make_shared<Core::Buffer::FrameBuffer>(1000, 2000)}
    , depth_buffer_ptr{std::make_shared<Core::Buffer::DepthBuffer>(1000, 2000)}
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
    // Bind Texture
    glBindTexture(GL_TEXTURE_2D, this->texture);

    auto buffer = ConvertFrameBuffer2Vector(this->frame_buffer_ptr);

    auto start = std::chrono::high_resolution_clock::now();

    glTexSubImage2D(
        GL_TEXTURE_2D,
        0, 
        0, 
        0, 
        this->frame_buffer_ptr->GetWidth(), 
        this->frame_buffer_ptr->GetHeight(), 
        GL_RGBA, 
        GL_FLOAT, 
        buffer.data()
    );

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << duration.count() << " ms" << std::endl;

    // Unbind Texture
    glBindTexture(GL_TEXTURE_2D, 0);
}