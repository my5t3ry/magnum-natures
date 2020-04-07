cmake_minimum_required(VERSION 3.15)
project(natures CXX)

if (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../modules/" ${CMAKE_MODULE_PATH})
endif ()

corrade_add_resource(NATURES_RESOURCES resources.conf)

include_directories(inc)
find_package(Corrade REQUIRED Main Utility)
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
        Corrade::Utility
        Magnum::Shaders
        m
        GL
        GLEW
        MagnumIntegration::ImGui)
FILE(COPY ${PROJECT_SOURCE_DIR}/inc DESTINATION ${CMAKE_BINARY_DIR}/Debug/bin/)

add_executable(natures
        inc/natures.hpp
        GeoShader.cpp
        list.cpp
        geoshader.cpp
        event.cpp
        dna.cpp
        spritebatch.cpp
        organism.cpp
        quadtree.cpp
        timer.cpp
        window.cpp
        natures.cpp
        ${NATURES_RESOURCES})
