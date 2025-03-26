#include <core/renderer/software_renderer.h>

#include <chrono>

#include <utils/timer.h>
#include <core/loader/obj_loader.h>

using namespace Core::Renderer;

SoftwareRenderer::SoftwareRenderer()
    : projection_mode{1}
    , model_selection{0}
    , texture_width{0}
    , texture_height{0}
    , mesh_ptr{std::make_shared<Core::Resources::Mesh>()}
    , perspective_camera_ptr{std::make_shared<Core::Resources::PerspectiveCamera>()}
    , orthographic_camera_ptr{std::make_shared<Core::Resources::OrthographicCamera>()}
    , frame_buffer_ptr{std::make_shared<Core::Buffer::FrameBuffer>(100, 100)}
    , depth_buffer_ptr{std::make_shared<Core::Buffer::DepthBuffer>(100, 100)}
    , vertex_processing_ptr{std::make_unique<Core::Pipeline::VertexProcessing>()}
    , triangle_processing_ptr{std::make_unique<Core::Pipeline::TriangleProcessing>()}
    , rasterizer_ptr{std::make_unique<Core::Pipeline::Rasterizer>()}
    , fragment_processing_ptr{std::make_unique<Core::Pipeline::FragmentProcessing>()}
    , framebuffer_operation_ptr{std::make_unique<Core::Pipeline::FrameBufferOperation>()}
{

}

void SoftwareRenderer::Init()
{
    Core::Primitives::Vertex v00, v01, v02;
    Core::Primitives::Vertex v10, v11, v12;
    v00.SetPos(10.0f, 0.0f, -10.0f, 1.0f);
    v01.SetPos(0.0f, 10.0f, -10.0f, 1.0f);
    v02.SetPos(-10.0f, 0.0f, -10.0f, 1.0f);
    v10.SetPos(-5.0f, 0.0f, -15.0f, 1.0f);
    v11.SetPos(-15.0f, 10.0f, -15.0f, 1.0f);
    v12.SetPos(-25.0f, 0.0f, -15.0f, 1.0f);

    v10.SetColor(1.0f, 1.0f, 0.0f, 1.0f);
    v11.SetColor(1.0f, 1.0f, 0.0f, 1.0f);
    v12.SetColor(1.0f, 1.0f, 0.0f, 1.0f);

    this->mesh_ptr->AddVertex(v00);
    this->mesh_ptr->AddVertex(v01);
    this->mesh_ptr->AddVertex(v02);
    this->mesh_ptr->AddVertex(v10);
    this->mesh_ptr->AddVertex(v11);
    this->mesh_ptr->AddVertex(v12);
    this->mesh_ptr->AddTriangle(0, 1, 2);
    this->mesh_ptr->AddTriangle(3, 4, 5);
}

void SoftwareRenderer::SetupPipeline()
{
    this->vertex_processing_ptr->SetFrameBuffer(this->frame_buffer_ptr);

    this->rasterizer_ptr->SetFrameBuffer(this->frame_buffer_ptr);
    this->rasterizer_ptr->SetDepthBuffer(this->depth_buffer_ptr);

    this->framebuffer_operation_ptr->SetFrameBuffer(this->frame_buffer_ptr);
    this->framebuffer_operation_ptr->SetDepthBuffer(this->depth_buffer_ptr);
}

GLuint SoftwareRenderer::Render()
{
    // Utils::GlobalTimer::Instance().Start();
    this->frame_buffer_ptr->Clear();
    this->depth_buffer_ptr->Clear();
    // Utils::GlobalTimer::Instance().PrintElapsedTime();

    // Utils::GlobalTimer::Instance().Start();
    // 1. Vertex Processing
    this->vertex_processing_ptr->SetModelMatrix(this->mesh_ptr->GetModelMatrix());
    if (this->projection_mode == 0)
    {
        this->vertex_processing_ptr->SetViewMatrix(this->orthographic_camera_ptr->GetViewMatrix());
        this->vertex_processing_ptr->SetProjectionMatrix(this->orthographic_camera_ptr->GetProjectionMatrix());
    }
    if (this->projection_mode == 1)
    {
        this->vertex_processing_ptr->SetViewMatrix(this->perspective_camera_ptr->GetViewMatrix());
        this->vertex_processing_ptr->SetProjectionMatrix(this->perspective_camera_ptr->GetProjectionMatrix());
    }
    auto vertices_screen_space = this->vertex_processing_ptr->TransformVertices(this->mesh_ptr->vertices);
    // Utils::GlobalTimer::Instance().PrintElapsedTime();

    // Utils::GlobalTimer::Instance().Start();
    // 2. Triangle Processing
    auto triangles = this->triangle_processing_ptr->Processing(
        vertices_screen_space,
        this->mesh_ptr->indices
    );
    // Utils::GlobalTimer::Instance().PrintElapsedTime();

    Utils::GlobalTimer::Instance().Start();
    // 3. Rasterization
    auto fragments = this->rasterizer_ptr->RasterizeTriangle(triangles);
    Utils::GlobalTimer::Instance().PrintElapsedTime();

    // Utils::GlobalTimer::Instance().Start();
    // 4. Fragment Processing
    this->fragment_processing_ptr->ProcessFragments(fragments);
    // Utils::GlobalTimer::Instance().PrintElapsedTime();

    // Utils::GlobalTimer::Instance().Start();
    // 5. FrameBuffer Operation
    this->framebuffer_operation_ptr->WriteFragment2Buffer(fragments);
    // Utils::GlobalTimer::Instance().PrintElapsedTime();

    // Utils::GlobalTimer::Instance().Start();
    this->UpdateTexture();
    // Utils::GlobalTimer::Instance().PrintElapsedTime();

    // Utils::GlobalTimer::Instance().Start();
    // Utils::GlobalTimer::Instance().PrintElapsedTime();
    return this->texture;
}

int SoftwareRenderer::GetTextureWidth()
{
    return this->texture_width;
}

int SoftwareRenderer::GetTextureHeight()
{
    return this->texture_height;
}

void SoftwareRenderer::HandleWindowResize(int width, int height)
{
    this->CreateTexture(width, height);

    this->frame_buffer_ptr->SetWidth(width);
    this->frame_buffer_ptr->SetHeight(height);
    this->frame_buffer_ptr->ResizeBuffer();

    this->depth_buffer_ptr->SetWidth(width);
    this->depth_buffer_ptr->SetHeight(height);
    this->depth_buffer_ptr->ResizeBuffer();
}

void SoftwareRenderer::HandleCameraMove(float x, float y)
{
    // Update orthographic camera
    if (this->projection_mode == 0)
    {   
        this->orthographic_camera_ptr->pos.x += x / 50;
        this->orthographic_camera_ptr->pos.y += y / 50;
    }
    // Update perspective camera
    else
    {
        this->perspective_camera_ptr->pos.x += x / 50;
        this->perspective_camera_ptr->pos.y += y / 50;
    }
}

void SoftwareRenderer::HandleCameraMove(float z)
{
    // Update orthographic camera
    if (this->projection_mode == 0)
    {   
        this->orthographic_camera_ptr->pos.z += z;
    }
    // Update perspective camera
    else
    {
        this->perspective_camera_ptr->pos.z += z;
    }
}

void SoftwareRenderer::HandleMeshRotation(float x, float y)
{
    this->mesh_ptr->rotation.x += y / 20;
    this->mesh_ptr->rotation.y += x / 20;
}

void SoftwareRenderer::ReloadMesh()
{
    this->mesh_ptr = std::make_shared<Core::Resources::Mesh>();

    if (this->model_selection == Model::TWO_TRIANGLES)
    {
        Core::Primitives::Vertex v00, v01, v02;
        Core::Primitives::Vertex v10, v11, v12;
        v00.SetPos(10.0f, 0.0f, -10.0f, 1.0f);
        v01.SetPos(0.0f, 10.0f, -10.0f, 1.0f);
        v02.SetPos(-10.0f, 0.0f, -10.0f, 1.0f);
        v10.SetPos(-5.0f, 0.0f, -15.0f, 1.0f);
        v11.SetPos(-15.0f, 10.0f, -15.0f, 1.0f);
        v12.SetPos(-25.0f, 0.0f, -15.0f, 1.0f);
    
        v10.SetColor(1.0f, 1.0f, 0.0f, 1.0f);
        v11.SetColor(1.0f, 1.0f, 0.0f, 1.0f);
        v12.SetColor(1.0f, 1.0f, 0.0f, 1.0f);
    
        this->mesh_ptr->AddVertex(v00);
        this->mesh_ptr->AddVertex(v01);
        this->mesh_ptr->AddVertex(v02);
        this->mesh_ptr->AddVertex(v10);
        this->mesh_ptr->AddVertex(v11);
        this->mesh_ptr->AddVertex(v12);
        this->mesh_ptr->AddTriangle(0, 1, 2);
        this->mesh_ptr->AddTriangle(3, 4, 5);
    }

    if (this->model_selection == Model::CUBE)
    {
        Core::Loader::ParseOBJFile("../asset/cube/cube.obj", this->mesh_ptr);
    }

    if (this->model_selection == Model::STANDFORD_BUNNY)
    {
        Core::Loader::ParseOBJFile("../asset/stanford_bunny/bunny.obj", this->mesh_ptr);
    }
}

void SoftwareRenderer::ResetMeshPos()
{
    this->mesh_ptr->translation.x = 0.0f;
    this->mesh_ptr->translation.y = 0.0f;
    this->mesh_ptr->translation.z = 0.0f;
    this->mesh_ptr->rotation.x = 0.0f;
    this->mesh_ptr->rotation.y = 0.0f;
    this->mesh_ptr->rotation.z = 0.0f;
    this->mesh_ptr->scale.x = 1.0f;
    this->mesh_ptr->scale.y = 1.0f;
    this->mesh_ptr->scale.z = 1.0f;
}

void SoftwareRenderer::ResetCamera()
{
    // reset orthographic camera
    this->orthographic_camera_ptr->pos.x = 0.0f;
    this->orthographic_camera_ptr->pos.y = 0.0f;
    this->orthographic_camera_ptr->pos.z = 0.0f;
    this->orthographic_camera_ptr->look_at.x = 0.0f;
    this->orthographic_camera_ptr->look_at.y = 0.0f;
    this->orthographic_camera_ptr->look_at.z = -1.0f;
    this->orthographic_camera_ptr->up.x = 0.0f;
    this->orthographic_camera_ptr->up.y = 1.0f;
    this->orthographic_camera_ptr->up.z = 0.0f;
    this->orthographic_camera_ptr->left = -100.0f;
    this->orthographic_camera_ptr->right = 100.0f;
    this->orthographic_camera_ptr->bottom = -100.0f;
    this->orthographic_camera_ptr->top = 100.0f;
    this->orthographic_camera_ptr->near_clip = 0.1f;
    this->orthographic_camera_ptr->far_clip = 100.0f;

    // reset perspective camera
    this->perspective_camera_ptr->pos.x = 0.0f;
    this->perspective_camera_ptr->pos.y = 0.0f;
    this->perspective_camera_ptr->pos.z = 0.0f;
    this->perspective_camera_ptr->look_at.x = 0.0f;
    this->perspective_camera_ptr->look_at.y = 0.0f;
    this->perspective_camera_ptr->look_at.z = -1.0f;
    this->perspective_camera_ptr->up.x = 0.0f;
    this->perspective_camera_ptr->up.y = 1.0f;
    this->perspective_camera_ptr->up.z = 0.0f;
    this->perspective_camera_ptr->fov = 120.0f;
    this->perspective_camera_ptr->aspect_ratio = 1.33f;
    this->perspective_camera_ptr->near_clip = 0.1f;
    this->perspective_camera_ptr->far_clip = 100.0f;

}

std::shared_ptr<Core::Resources::PerspectiveCamera> SoftwareRenderer::GetPerspectiveCamera() const
{
    return this->perspective_camera_ptr;
}

std::shared_ptr<Core::Resources::OrthographicCamera> SoftwareRenderer::GetOrthographicCamera() const
{
    return this->orthographic_camera_ptr;
}

std::shared_ptr<Core::Resources::Mesh> SoftwareRenderer::GetMesh() const
{
    return this->mesh_ptr;
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