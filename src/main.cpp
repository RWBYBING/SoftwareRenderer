#include <gui/window.h>

#include <memory>
#include <iostream>

int main(void)
{
    std::unique_ptr gui_ptr = std::make_unique<GUI::GLFWWindowManager>();
    gui_ptr->Run();

    

    return 0;
}