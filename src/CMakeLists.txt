cmake_minimum_required(VERSION 3.15)
project(natures CXX)

if (PROJECT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../modules/" ${CMAKE_MODULE_PATH})
endif ()

corrade_add_resource(NATURES_RESOURCES resources.conf)
#
#add_executable(embedfile inc/opengl/embed.cpp)
#
#add_custom_command(
#        OUTPUT  ${PROJECT_BINARY_DIR}/inc/vertex_shader.h
#        COMMAND embedfile vertex_shader inc/opengl/shaders/theshader.vert ${CMAKE_BINARY_DIR}/vertex_shader.h
#        DEPENDS inc/opengl/shaders/theshader.vert
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})


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
        Magnum::Sdl2Application
        Magnum::Shaders
        Magnum::GL
        Magnum::SceneGraph
        Magnum::Magnum
        Magnum::MeshTools
        Magnum::Primitives
        Magnum::SceneGraph
        Corrade::Utility
        MagnumIntegration::ImGui
        GLEW)
FILE(COPY ${PROJECT_SOURCE_DIR}/inc DESTINATION ${PROJECT_BINARY_DIR}})

add_executable(natures
        inc/natures.hpp
        inc/FlatShadeObject2D.h
        inc/WireframeObject2D.h
        GeoShader.cpp
        list.cpp
        event.cpp
        dna.cpp
        spritebatch.cpp
        organism.cpp
        quadtree.cpp
        timer.cpp
        natures.cpp
        ${NATURES_RESOURCES})
