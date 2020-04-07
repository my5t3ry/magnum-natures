cmake_minimum_required(VERSION 3.15)
project(natures)

set(CMAKE_CXX_STANDARD 11)

include_directories(inc)
find_package(Corrade REQUIRED Main)
find_package(Magnum REQUIRED
        GL
        MeshTools
        Primitives
        SceneGraph
        Shaders
        Sdl2Application)
find_package(MagnumIntegration REQUIRED ImGui)

link_libraries(Corrade::Main
        Magnum::Application
        Magnum::GL
        Magnum::Magnum
        Magnum::MeshTools
        Magnum::Primitives
        Magnum::SceneGraph
        Magnum::Shaders
        pthread
        MagnumIntegration::ImGui
        m
        GLEW
        )
FILE(COPY ${PROJECT_SOURCE_DIR}/inc DESTINATION ${CMAKE_BINARY_DIR}/Debug/bin/)


add_executable(natures
        list.cpp
        geoshader.cpp
        event.cpp
        dna.cpp
        spritebatch.cpp
        organism.cpp
        quadtree.cpp
        timer.cpp
        window.cpp
        main.cpp)
