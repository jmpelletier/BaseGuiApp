# Set the minimum CMAKE version
cmake_minimum_required(VERSION 3.13)

# Set the project name and version
project(GuiApp VERSION 1.0)

# Specify that we are using C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable target
add_executable(GuiApp "" )

# Add target sources
target_sources(GuiApp PUBLIC "src/Application.cpp")

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
if (WIN32)
    SET(IMGGUI_SRC "${IMGGUI_SRC}" "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_win32.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends/imgui_impl_dx12.cpp")
    
    # This definition is required for imgui using the DirectX12 backend.
    target_compile_definitions(GuiApp PUBLIC ImTextureID=ImU64)

    # Add the main file
    target_sources(GuiApp PUBLIC "src/Windows/main.cpp")
    target_include_directories(GuiApp PUBLIC "src/Windows/")

    # Add the imgui backend
    target_sources(GuiApp PUBLIC "imgui/backends/imgui_impl_win32.cpp" "imgui/backends/imgui_impl_dx12.cpp")

    # Link to the DirectX 12 library
    target_link_libraries(GuiApp PUBLIC d3d12.lib dxgi.lib) 
elseif(APPLE)
    # TODO
else()
    # TODO
endif()

