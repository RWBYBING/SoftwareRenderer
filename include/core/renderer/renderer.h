#ifndef RENDERER_H
#define RENDERER_H

namespace Core
{
    namespace Renderer
    {
        class Renderer
        {
        public:
            virtual ~Renderer() = default;
            virtual void Init() = 0;
            virtual void SetupPipeline() = 0;                    
            virtual void Render() = 0;
        };
    }
}

#endif  // RENDERER_H