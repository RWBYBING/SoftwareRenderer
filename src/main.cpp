#include <memory>
#include <iostream>

#include <gui/window.h>
#include <core/math/vector.h>
#include <core/math/matrix.h>

int main(void)
{
    std::unique_ptr gui_ptr = std::make_unique<GUI::GLFWWindowManager>();
    gui_ptr->Run();

    return 0;
}