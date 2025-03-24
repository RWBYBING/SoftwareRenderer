#ifndef SOFTWARE_RENDERER_H
#define SOFTWARE_RENDERER_H

#include <memory>

#include <GL3W/gl3w.h>

#include <core/pipeline/vertex_processing.h>
#include <core/pipeline/triangle_processing.h>
#include <core/pipeline/rasterizer.h>
#include <core/pipeline/fragment_processing.h>
#include <core/pipeline/framebuffer_operation.h>

#include <core/resources/camera.h>
#include <core/resources/mesh.h>

namespace Core
{
    namespace Renderer
    {
        enum class Object
        {
            TWO_TRIANGLES,              // Two simple triangles with the same size and different distance from the x-y plane
            CUBE,                       // A Cube with six faces
            STANDFORD_BUNNY             // The classical cute bunny                       
        };

        class SoftwareRenderer
        {
        public:
            SoftwareRenderer();

            void Init();
            void SetupPipeline();
            GLuint Render();

            void HandleWindowResize(int width, int height);
            int GetTextureWidth();
            int GetTextureHeight();

            void HandleCameraMove(float x, float y);

            std::shared_ptr<Core::Resources::PerspectiveCamera> GetPerspectiveCamera() const;
            std::shared_ptr<Core::Resources::OrthographicCamera> GetOrthographicCamera() const;
            std::shared_ptr<Core::Resources::Mesh> GetMesh() const;

        private:
            void CreateTexture(int width, int height);          // Create the 2D texture for final displaying
            void UpdateTexture();                               // Update the 2D texture for final displaying

        public:
            int projection_mode;                                // 0: Orthographic, 1: Perspective
            bool enable_backface_culling;                       
            bool enable_frustum_clipping;

        private:
            GLuint texture;                                     // OpenGL Texture id(only for displaying the final image)
        
        private:
            int texture_width;
            int texture_height;

        // Resources
        private:
            std::shared_ptr<Core::Resources::Mesh> mesh_ptr;
            std::shared_ptr<Core::Resources::PerspectiveCamera> perspective_camera_ptr;
            std::shared_ptr<Core::Resources::OrthographicCamera> orthographic_camera_ptr;

        // Buffer
        private:
            std::shared_ptr<Core::Buffer::FrameBuffer> frame_buffer_ptr;
            std::shared_ptr<Core::Buffer::DepthBuffer> depth_buffer_ptr;

        // Pipeline
        private:
            std::unique_ptr<Core::Pipeline::VertexProcessing> vertex_processing_ptr;
            std::unique_ptr<Core::Pipeline::TriangleProcessing> triangle_processing_ptr;
            std::unique_ptr<Core::Pipeline::Rasterizer> rasterizer_ptr;
            std::unique_ptr<Core::Pipeline::FragmentProcessing> fragment_processing_ptr;
            std::unique_ptr<Core::Pipeline::FrameBufferOperation> framebuffer_operation_ptr;
        };
    }
}

#endif // SOFTWARE_RENDERER_H