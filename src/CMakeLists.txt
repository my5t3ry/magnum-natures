cmake_minimum_required(VERSION 3.15)
project(natures)

set(CMAKE_CXX_STANDARD 11)


find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(inc)
include_directories(PUBLIC ${SDL2_INCLUDE_DIRS})
include_directories(PUBLIC ${OPENGL_INCLUDE_DIR})

FILE(COPY ${PROJECT_SOURCE_DIR}/inc DESTINATION ${CMAKE_BINARY_DIR}/Debug/bin/)

add_library(imgui
        # Main Imgui files
        ../imgui/imgui.cpp ../imgui/imgui_draw.cpp ../imgui/imgui_widgets.cpp ../imgui/imgui_demo.cpp
        # SDL2+OpenGL-specific files
        ../imgui/examples/imgui_impl_sdl.cpp ../imgui/examples/imgui_impl_opengl3.cpp inc/opengl/renderbatch.cpp inc/opengl/renderbatch.h)
# Make SDL2 available to Imgui
target_include_directories(imgui PUBLIC ${SDL2_INCLUDE_DIRS})
# imgui/exapmles/ contains the sdl implementation
target_include_directories(imgui PUBLIC ../imgui/ ../imgui/examples/)
# Configure Imgui to use OpengGL through SDL2
target_compile_definitions(imgui PUBLIC IMGUI_IMPL_OPENGL_LOADER_CUSTOM=<SDL_opengl.h> GL_GLEXT_PROTOTYPES=1)


link_libraries(
        ${SDL2_LIBRARIES}
        ${OPENGL_LIBRARIES}
        pthread
        m
        GLEW
        imgui)

add_executable(natures
        geoshader.cpp
        spritebatch.cpp
        treespritebatch.cpp
        list.cpp
        dna.cpp
        timer.cpp
        organism.cpp
        quadtree.cpp
        window.cpp
        main.cpp)
