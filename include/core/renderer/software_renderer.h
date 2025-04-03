#ifndef SOFTWARE_RENDERER_H
#define SOFTWARE_RENDERER_H

#include <memory>

#include <GL3W/gl3w.h>

#include <core/basic/resources.h>
#include <core/buffer/framebuffer.h>
#include <core/buffer/depthbuffer.h>
#include <core/pipeline/vertex_processing.h>
#include <core/pipeline/rasterizer.h>

namespace Core
{
    namespace Renderer
    {
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

            void HandleCameraMove(float x, float y);            // Camera translation in x-y plane
            void HandleCameraMove(float z);                     // Camera translation on z-axis
            void HandleMeshRotation(float x, float y);          // Mesh rotation on x-axis and y-axis
            
            void ReloadMesh();                                  // Load a new mesh ptr
            void ResetMesh();                                   // Reset the mesh position
            void ResetCamera();                                 // Reset the camera

            std::shared_ptr<Resources::PerspectiveCamera> GetPerspectiveCamera() const;
            std::shared_ptr<Resources::OrthographicCamera> GetOrthographicCamera() const;
            std::shared_ptr<Resources::Mesh> GetMesh() const;
            std::shared_ptr<Resources::Light> GetLight() const;
            std::shared_ptr<Resources::Material> GetMaterial() const;

        private:
            void CreateTexture(int width, int height);          // Create the 2D texture for final displaying
            void UpdateTexture();                               // Update the 2D texture for final displaying

        public:
            Model model_selection;                              // 0: two triangles, 1: cube, 2: stanford bunny
            RenderingMode rendering_mode;                       // 0: Vertex only, 1: Lineframe, 2: Triangles
            CameraMode camera_mode;                             // 0: Orthographic, 1: Perspective
            ShadingMode shading_mode;                           // 0: Flat shading, 1: Gourand shading, 2: Phong shading
            AntiAliasingMode anti_aliasing_mode;                // 0: None, 1: FXAA, 2: MSAA
            bool enable_backface_culling;
            bool enable_frustum_clipping;

        private:
            GLuint texture;                                     // OpenGL Texture id(only for displaying the final image)
        
        public:
            int texture_width;
            int texture_height;
            int triangle_num;                                   // total triangles to be processed in the pipeline

        // Resources
        private:
            std::shared_ptr<Resources::Mesh> mesh_ptr;
            std::shared_ptr<Resources::Material> material_ptr;
            std::shared_ptr<Resources::Light> light_ptr;
            std::shared_ptr<Resources::PerspectiveCamera> perspective_camera_ptr;
            std::shared_ptr<Resources::OrthographicCamera> orthographic_camera_ptr;

        // Buffer
        private:
            std::shared_ptr<Buffer::FrameBuffer> frame_buffer_ptr;
            std::shared_ptr<Buffer::DepthBuffer> depth_buffer_ptr;

        // Pipeline
        private:
            std::unique_ptr<Pipeline::VertexProcessing> vertex_processing_ptr;
            std::unique_ptr<Pipeline::Rasterizer> rasterizer_ptr;
        };
    }
}

#endif // SOFTWARE_RENDERER_H