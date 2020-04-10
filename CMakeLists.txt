cmake_minimum_required(VERSION 3.4)
project(magnum-nature-sim)

add_subdirectory(imgui)
set(WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/modules/" ${CMAKE_MODULE_PATH})
#set(BOX2D_INCLUDE_DIR box2d/include)
#set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
#set(WITH_IMGUI ON CACHE BOOL "" FORCE)
#add_subdirectory(magnum-integration EXCLUDE_FROM_ALL)
add_subdirectory(corrade EXCLUDE_FROM_ALL)
add_subdirectory(magnum EXCLUDE_FROM_ALL)

find_package(Magnum REQUIRED)
#find_package(MagnumIntegration REQUIRED ImGui)

add_subdirectory(src)
