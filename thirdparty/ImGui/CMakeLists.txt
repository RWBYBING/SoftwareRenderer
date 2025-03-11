file(GLOB_RECURSE srcs CONFIGURE_DEPENDS src/*.cpp include/*.h)

add_library(imgui STATIC ${srcs})

target_include_directories(imgui PUBLIC include)

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

target_link_libraries(imgui OpenGL::GL)

# GLFW
set (GLFW_INCLUDE_DIR /usr/include/GLFW)
set (GLFW_LIB_DIR /usr/lib64)
target_include_directories(imgui PUBLIC ${GLFW_INCLUDE_DIR})
target_link_libraries(imgui ${GLFW_LIB_DIR}/libglfw.so.3.3)