cmake_minimum_required(VERSION 3.15)
project(natures)

set(CMAKE_CXX_STANDARD 11)

include_directories(inc)

link_libraries(m GL GLEW SDL2 pthread)
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
