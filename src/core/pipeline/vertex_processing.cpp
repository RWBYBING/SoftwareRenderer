#include <core/pipeline/vertex_processing.h>

#include <iostream>
#include <cmath>

#include <glm/ext/matrix_transform.hpp> 

using namespace Pipeline;

VertexProcessing::VertexProcessing()
    : model_matrix{glm::identity<glm::mat4>()}
    , view_matrix{glm::identity<glm::mat4>()}
    , projection_matrix{glm::identity<glm::mat4>()}
    , frame_buffer{nullptr}
{

}

VertexProcessing::~VertexProcessing() = default;

void VertexProcessing::SetModelMatrix(const Matrix4x4& mat)
{
    this->model_matrix = mat;
}

void VertexProcessing::SetViewMatrix(const Matrix4x4& mat)
{
    this->view_matrix = mat;
}

void VertexProcessing::SetProjectionMatrix(const Matrix4x4& mat)
{
    this->projection_matrix = mat;
}

void VertexProcessing::SetFrameBuffer(std::shared_ptr<Buffer::FrameBuffer> buffer)
{
    this->frame_buffer = buffer;
}

std::vector<Primitives::Triangle> VertexProcessing::TransformVertices(
    const std::vector<Primitives::Vertex>& vertices,
    const std::vector<uint32_t>& indices,
    ShadingMode shading_mode
) const 
{
    std::vector<Primitives::Vertex> temp_vertices = vertices;

    const auto mvp = projection_matrix * (view_matrix * model_matrix);

    // 1. Apply MVP Matrix on each vertex, now all the vertices are in the clip space
    for (auto& vertex : temp_vertices)
    {
        vertex.pos = mvp * vertex.pos;
    }

    // 2. Assembly triangles (include backface culling and frustum clipping)
    auto triangles = this->TriangleAssembly(temp_vertices, indices);

    for (auto& triangle : triangles)
    {
        // // TODO: Optimize the performance
        // // calculate the normal
        // Vector3 edge1 = triangle.v1.pos - triangle.v0.pos;
        // Vector3 edge2 = triangle.v2.pos - triangle.v0.pos;
        // Vector3 normal = glm::normalize(glm::cross(edge1, edge2));

        // // 计算光照（假设使用简单的漫反射模型）
        // Vector3 lightDir = glm::normalize(Vector3(0, 0, -1)); // 假设光源在摄像机方向
        // float diffuse = std::max(0.0f, glm::dot(normal, lightDir));
        // Color triangleColor = Color(diffuse, diffuse, diffuse, 1.0f); // 单色光照

        // // 将颜色赋给三角形的所有顶点（Flat Shading的核心）
        // triangle.v0.color = triangleColor;
        // triangle.v1.color = triangleColor;
        // triangle.v2.color = triangleColor;

        // 3. NDC
        this->NDC(triangle.v0);
        this->NDC(triangle.v1);
        this->NDC(triangle.v2);

        // 4. Viewport transformation
        this->ViewportTransformation(triangle.v0);
        this->ViewportTransformation(triangle.v1);
        this->ViewportTransformation(triangle.v2);
    }

    return triangles;
}

std::vector<Primitives::Triangle> VertexProcessing::TriangleAssembly(const std::vector<Primitives::Vertex>& vertices, const std::vector<uint32_t>& indices) const
{
    std::vector<Primitives::Triangle> triangles;
    triangles.reserve(indices.size() / 3 + 1);

    for (size_t i = 0; i < indices.size(); i += 3) {
        Primitives::Triangle triangle;
        triangle.v0 = vertices[indices[i]];
        triangle.v1 = vertices[indices[i + 1]];
        triangle.v2 = vertices[indices[i + 2]];

        // execute backface culling
        // if (this->IsBackface(triangle))
        // {
        //     continue;
        // }

        // execute frustum clipping
        if (
            this->IsInsideViewFrustum(triangle.v0) ||
            this->IsInsideViewFrustum(triangle.v1) ||
            this->IsInsideViewFrustum(triangle.v2)
        )
        {
            triangles.push_back(triangle);
        }
    }

    // std::cout << triangles.size() << std::endl;
    return triangles;
}

bool VertexProcessing::IsBackface(const Primitives::Triangle& triangle) const
{
    // calculate the normal
    Vector3 edge1 = triangle.v1.pos - triangle.v0.pos;
    Vector3 edge2 = triangle.v2.pos - triangle.v0.pos;
    Vector3 normal = glm::normalize(glm::cross(edge1, edge2));

    // determine if the normal is back to the camera
    Vector3 viewDir = -glm::normalize(triangle.v0.pos);

    return glm::dot(normal, viewDir) < 0;
}

bool VertexProcessing::IsInsideViewFrustum(const Primitives::Vertex& vertex) const 
{
    float x = std::abs(vertex.pos.x);
    float y = std::abs(vertex.pos.y);
    float z = std::abs(vertex.pos.z);
    float w = std::abs(vertex.pos.w);

    return (x < w) && (y < w) && (z < w);
}

void VertexProcessing::NDC(Primitives::Vertex& vertex) const 
{
    float reciprocalW = 1.0f / vertex.pos.w;
    vertex.pos.x *= reciprocalW;
    vertex.pos.y *= reciprocalW;
    vertex.pos.z *= reciprocalW;
    vertex.pos.w = 1.0f;
}

void VertexProcessing::ViewportTransformation(Primitives::Vertex& vertex) const
{
    int screen_width = this->frame_buffer->GetWidth();
    int screen_height = this->frame_buffer->GetHeight();

    vertex.pos.x = (1.0f - vertex.pos.x) * 0.5f * screen_width;
    vertex.pos.y = (1.0f - vertex.pos.y) * 0.5f * screen_height;
    vertex.pos.z = vertex.pos.z;   // (depth_near = 1, depth_far = -1)
}

