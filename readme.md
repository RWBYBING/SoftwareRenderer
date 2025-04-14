# Software Renderer

## Intro
---
I’m excited to introduce this software rasterizer (I haven’t decided on a name yet—once the project matures, I’ll give it a proper one). This project aims to implement a simplified real-time rendering pipeline purely through C/C++ code, without relying on modern graphics APIs, while incorporating foundational computer graphics functionalities. First, it's important to clarify that this renderer's computational workflow relies entirely on the CPU for processing (only utilizing the GPU during the final drawing stage). This renderer is merely a simplified simulation of a basic rasterization pipeline. As a result, **its performance is in no way comparable to modern rendering pipelines.** 

Yet I firmly believe that implementing such a rendering pipeline from scratch remains absolutely essential—what I consider a rite of passage for every computer graphics practitioner. Through this process, we materialize every mathematical concept in rendering through self-developed code, which profoundly deepens our understanding of the entire rasterization pipeline and establishes an unshakable foundation.



## ThirdParty
---
**GLFW:** For establishing the window and displaying final result.
**Dear ImGui:** For designing the control panel for tuning the parameters of rendering options.
**GLM:** For the Math computations (also for enable the SIMD).
**TBB:** For enabling the parallel computing.

## Features
---
Below is all the graphics features which are implemented in this project:
+ MVP Transformation(including both orthographics projection and perspective projections)
+ Backface Culling and Frustum Clipping
+ Rasterizatoin options: Vertex Only, LineFrame only and the entire triangle
+ Different shading methods: Flat shading, Gourand shading and Phong shading
+ Blinn-Phong reflection model
+ Anti-Aliasing: FXAA and MSAA
+ User-friendly interface for customized parameters of Mesh, Camera, Light and Material
+ Enabled CPU-based parallel computing