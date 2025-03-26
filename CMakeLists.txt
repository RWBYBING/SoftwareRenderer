cmake_minimum_required(VERSION 3.10)
project(Renderer LANGUAGES C CXX)

# Compiler Flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROGRAM_NAME renderer)

# Print Brief Info
message("PROJECT_NAME: ${PROJECT_NAME}")
message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message("PROJECT_BINARY_DIR: ${PROJECT_BINARY_DIR}")

# Check the Binary Directory
if (PROJECT_BINARY_DIR STREQUAL PROJECT_SOURCE_DIR)
	message(WARNING "The binary directory of CMake cannot be the same as source directory!")
endif()

# Default Build Type
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# Build Type Specific Flags
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g -std=c++17")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3 -mavx2 -march=native -ffast-math -DNDEBUG")
    
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fopt-info-vec-missed -fopt-info-vec-optimized")
    
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -Wpedantic -std=c++17")
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS_RELEASE}")
endif()

# Windows _DNOMINMAX Problem Fix
if (WIN32)
	add_definitions(_DNOMINMAX -D_USE_MATH_DEFINES)
endif()

# Use Cache
if (NOT MSVC)
	find_program(CCACHE_PROGRAM ccache)
	if (CCACHE_PROGRAM)
		message(STATUS "Found CCache: ${CCACHE_PROGRAM}")
		set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE_PROGRAM})
        set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ${CCACHE_PROGRAM})
    endif()
endif()

# Include Directories
include_directories(include)
include_directories(include/core)
include_directories(include/gui)
include_directories(include/utils)

# Source Files
set(CORE_SOURCES
	
)

set(GUI_SOURCES
	src/gui/window.cpp
	src/utils/timer.cpp
	src/core/loader/obj_loader.cpp
	src/core/math/vector.cpp
	src/core/math/matrix.cpp
	src/core/primitives/vertex.cpp
	src/core/primitives/fragment.cpp
	src/core/primitives/triangle.cpp
	src/core/resources/camera.cpp
	src/core/resources/mesh.cpp
	src/core/resources/material.cpp
	src/core/buffer/framebuffer.cpp
	src/core/buffer/depthbuffer.cpp
	src/core/pipeline/vertex_processing.cpp
	src/core/pipeline/triangle_processing.cpp
	src/core/pipeline/rasterizer.cpp
	src/core/pipeline/fragment_processing.cpp
	src/core/pipeline/framebuffer_operation.cpp
	src/core/renderer/software_renderer.cpp
)

set(SOURCES 
	${CORE_SOURCES}
	${GUI_SOURCES}
	# ${UTILS_SOURCES}
)

# Add Third-Party
add_subdirectory(thirdparty)

# Doxygen Integration
find_program(DOXYGEN NAMES doxygen)
if(DOXYGEN)
    add_custom_target(doxygen
        COMMAND ${DOXYGEN} ../docs/doxygen/Doxyfile
        COMMENT "Generating Doxygen documentation..."
    )
endif()

# Cppcheck Integration
find_program(CPPCHECK NAMES cppcheck)
if(CPPCHECK)
	add_custom_target(cppcheck
		COMMAND ${CPPCHECK} --suppress=missingIncludeSystem --suppress=checkersReport --enable=all "${CMAKE_SOURCE_DIR}/src/" "${CMAKE_SOURCE_DIR}/include/"
		COMMENT "Running Cppcheck..."
	)
endif()

# Valgrind Integration
find_program(VALGRIND NAMES valgrind)
if(VALGRIND AND CMAKE_BUILD_TYPE STREQUAL Debug)	# Only in Debug mode
	add_custom_target(valgrind
		COMMAND ${VALGRIND} --leak-check=full --show-leak-kinds=all ./${PROGRAM_NAME}
		DEPENDS ${PROGRAM_NAME}
		COMMENT "Running Valgrind..."
	)
endif()

#Perf Integration
find_program(PERF NAMES perf)
if(PERF AND CMAKE_BUILD_TYPE STREQUAL Release)		# Only in Release mode
	add_custom_target(perf
		COMMAND ${PERF} stat ./${PROGRAM_NAME}
		DEPENDS ${PROGRAM_NAME}
		COMMENT "Running Perf..."
	)
endif()

# Google Test Integration
find_package(GTest REQUIRED)

# Test Source Files
set(TEST_SOURCES
	# test/core/math_test.cpp
)
enable_testing()

# Create Test Executables
foreach(TEST_FILE ${TEST_SOURCES})
	get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
	add_executable(${TEST_NAME} ${TEST_FILE} ${SOURCES})
	target_link_libraries(${TEST_NAME} GTest::gtest_main gl3w imgui)
	add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()

# Executable
add_executable(${PROGRAM_NAME} ${SOURCES} src/main.cpp)

target_link_libraries(${PROGRAM_NAME} PUBLIC gl3w imgui)