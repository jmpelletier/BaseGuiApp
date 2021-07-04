# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

# Set the minimum CMAKE version
cmake_minimum_required(VERSION 3.13)

# Set the project name and version
project(GuiApp VERSION 1.0)

# Specify whether we will use OpenGL or DirectX/Metal
set(USE_OPENGL True)

# Specify that we are using C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable target
add_executable(GuiApp "" )

# Add target sources
target_sources(GuiApp PUBLIC "src/Application.cpp" "src/Application.hpp")

# Check if Git is installed, and source directory
# is under version control.
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")

	# Update Git submodules
	execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)

    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "Git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
endif()

# Add imgui sources and include directories
target_sources(GuiApp PUBLIC "imgui/imgui.cpp" "imgui/imgui_draw.cpp" "imgui/imgui_tables.cpp" "imgui/imgui_widgets.cpp" "imgui/imgui_demo.cpp")
target_include_directories(GuiApp PUBLIC "imgui" "imgui/backends")


# Add platform-specific sources
if (USE_OPENGL)
    target_include_directories(GuiApp PUBLIC "src/OpenGL/" "imgui/examples/libs/glfw/include" "imgui/examples/libs" "imgui/examples/libs/gl3w")
    if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8") # Is this a 64-bit platform?
        set(GLFW_LIB_DIR "imgui/examples/libs/glfw/lib-vc2010-64")
    else()
        set(GLFW_LIB_DIR "imgui/examples/libs/glfw/lib-vc2010-32")
    endif()
    
    find_library(GLFW_LIB glfw3 HINTS ${GLFW_LIB_DIR} REQUIRED)
    if(NOT GLFW_LIB)
        message(FATAL_ERROR "Could not find GLFW library.")
    endif()

    find_library(GL3_LIB opengl32 REQUIRED)
    if(NOT GL3_LIB)
        message(FATAL_ERROR "Could not find OpenGL 3 library.")
    endif()

    message("Found OpenGL: ${GL3_LIB}")

    target_link_libraries(GuiApp PUBLIC ${GLFW_LIB} ${GL3_LIB})

    link_directories(GuiApp PUBLIC "imgui/examples/libs")
    target_sources(GuiApp PUBLIC "src/OpenGL/main.cpp")

    # Add the imgui backend
    target_sources(GuiApp PUBLIC "imgui/backends/imgui_impl_glfw.cpp" "imgui/backends/imgui_impl_opengl3.cpp" "imgui/examples/libs/gl3w/GL/gl3w.c")

elseif(WIN32)
    target_include_directories(GuiApp PUBLIC "src/Windows/")
    target_sources(GuiApp PUBLIC "src/Windows/main.cpp")

    # This definition is required for imgui using the DirectX12 backend.
    target_compile_definitions(GuiApp PUBLIC ImTextureID=ImU64)

    # Add the imgui backend
    target_sources(GuiApp PUBLIC "imgui/backends/imgui_impl_win32.cpp" "imgui/backends/imgui_impl_dx12.cpp")

    # Link to the DirectX 12 library
    target_link_libraries(GuiApp PUBLIC d3d12.lib dxgi.lib) 
elseif(APPLE)
    # TODO
endif()

