set(gl3w_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(gl3w_inc ${gl3w_dir}/include)
set(gl3w_src ${gl3w_dir}/src/gl3w.c)

if (EXISTS ${gl3w_src})
    message(STATUS "Found gl3w source files")
endif()

add_library(gl3w STATIC ${gl3w_src})
target_include_directories(gl3w PUBLIC ${gl3w_inc})