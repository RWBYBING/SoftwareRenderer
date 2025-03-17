#ifndef SOFTWARE_RENDERER_H
#define SOFTWARE_RENDERER_H

#include <memory>

#include <core/renderer/renderer.h>
#include <core/pipeline/vertex_processing.h>
#include <core/pipeline/triangle_processing.h>
#include <core/pipeline/rasterizer.h>

namespace Core
{
    namespace Renderer
    {
        class SoftwareRenderer : public Renderer
        {
        public:
            SoftwareRenderer();

            void Init() override;
            void SetupPipeline() override;
            GLuint Render() override;

            void HandleWindowResize(int width, int height) override;
            int GetTextureWidth() override;
            int GetTextureHeight() override;

        private:
            void CreateTexture(int width, int height);          // Create the 2D texture for final displaying
            void UpdateTexture();                               // Update the 2D texture for final displaying

        private:
            GLuint texture;                                     // OpenGL Texture id(only for displaying the final image)
        
        private:
            int texture_width;
            int texture_height;

        private:
            std::unique_ptr<Core::Pipeline::VertexProcessing> vertex_processing_ptr;
            std::unique_ptr<Core::Pipeline::TriangleProcessing> triangle_processing_ptr;
            std::unique_ptr<Core::Pipeline::Rasterizer> rasterizer_ptr;
            std::shared_ptr<Core::Buffer::FrameBuffer> frame_buffer_ptr;
            std::shared_ptr<Core::Buffer::DepthBuffer> depth_buffer_ptr;
        };
    }
}

#endif // SOFTWARE_RENDERER_H