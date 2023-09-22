cmake_minimum_required(VERSION 3.0.0)
project(Pomegranate_Engine VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

include_directories("lib/assimp/" "lib/imgui/" "lib/glm/" "lib/tea/")

link_directories("lib/tea/")

find_package(OpenGL REQUIRED)
find_package(assimp REQUIRED)
add_definitions(-DGLFW_INCLUDE_NONE)
set(CMAKE_CXX_FLAGS "-fsanitize=address -Wall")

file(GLOB SOURCES "src/*.cpp")

add_executable(Pomegranate_Engine 
lib/glad/glad.h
lib/glad/glad.c 
lib/imgui/imgui.cpp 
lib/imgui/imgui_demo.cpp 
lib/imgui/imgui_draw.cpp 
lib/imgui/imgui_tables.cpp 
lib/imgui/imgui_widgets.cpp 
lib/imgui/backends/imgui_impl_glfw.cpp 
lib/imgui/backends/imgui_impl_opengl3.cpp 
lib/imgui/misc/cpp/imgui_stdlib.cpp

src/main.cpp 
src/color.cpp
src/entity.cpp
src/hierarchy.cpp
src/editor_window.cpp
src/world.cpp
src/world_edit.cpp
src/import.cpp
src/entities_types.cpp
src/shaders.cpp
src/windows.cpp
src/debug.cpp
src/inspector.cpp
src/console.cpp
src/tea_tools.cpp
src/input.cpp
src/pomegranate_lib.cpp
)

set_target_properties(Pomegranate_Engine PROPERTIES RUNTIME_OUTPUT_DIRECTORY "build/")

target_link_libraries(Pomegranate_Engine glfw OpenGL::GL assimp libtea.so)