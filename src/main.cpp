#include <memory>
#include <iostream>

#include <gui/window.h>

int main(void)
{
    std::unique_ptr gui_ptr = std::make_unique<GUI::GLFWWindowManager>();
    gui_ptr->Run();

    return 0;
}