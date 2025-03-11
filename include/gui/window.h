#ifndef WINDOW_H
#define WINDOW_H

#include <GL3W/gl3w.h>
#include <GLFW/glfw3.h>

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

namespace GUI
{
    class GLFWWindowManager
    {
    public:
        GLFWWindowManager();
        ~GLFWWindowManager();
        void Run();                                     // Start the GLFW window loop

    private:
        void Update();                                  // Update a new frame
        void Startup();                                 // Initialize the resources before the loop
        void UpdateImGuiWindow();                       
        void UpdateRenderingContext();                       

    private:
        

    private:
        GLFWwindow* window;
        

    };
}


#endif  // WINDOW_H