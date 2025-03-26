add_subdirectory(GL3W)
add_subdirectory(ImGui)

find_package(TBB CONFIG REQUIRED)

if(TBB_FOUND)
    message(STATUS "TBB found: ${TBB_VERSION}")
    # include_directories(${TBB_INCLUDE_DIRS})
    # add_executable(my_app main.cpp)
    # target_link_libraries(my_app ${TBB_LIBRARIES})
else()
    message(FATAL_ERROR "TBB not found")
endif()