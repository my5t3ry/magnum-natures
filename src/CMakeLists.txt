cmake_minimum_required(VERSION 3.15)
project(natures)

set(CMAKE_CXX_STANDARD 11)

include_directories(inc)

find_package(GLFW REQUIRED)

find_package(Corrade REQUIRED Main)
find_package(Magnum REQUIRED GL Shaders)
if(CORRADE_TARGET_APPLE)
    find_package(Magnum REQUIRED CglContext)
elseif(CORRADE_TARGET_UNIX)
    find_package(Magnum REQUIRED GlxContext)
elseif(CORRADE_TARGET_WINDOWS)
    find_package(Magnum REQUIRED WglContext)
else()
    message(FATAL_ERROR "No context handler available on this platform")
endif()

set_directory_properties(PROPERTIES CORRADE_USE_PEDANTIC_FLAGS ON)

link_libraries(GLFW::GLFW
        Corrade::Main
        Magnum::GL
        Magnum::GLContext
        Magnum::Magnum
        Magnum::Shaders)

add_executable(natures
        list.cpp
        geoshader.cpp
        dna.cpp
        spritebatch.cpp
        organism.cpp
        quadtree.cpp
        main.cpp)
