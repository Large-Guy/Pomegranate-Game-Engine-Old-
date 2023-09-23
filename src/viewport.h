#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>

#include "../lib/glad/glad.h"
#include <GLFW/glfw3.h>

#include"editor_window.h"
#include"entities_types.h"

class Viewport : public EditorWindow
{
public:
    GLuint texture;
    ImVec2 window_size;
    double editor_mouse_x = 0;
    double editor_mouse_y = 0;
    double prev_editor_mouse_x = editor_mouse_x;
    double prev_editor_mouse_y = editor_mouse_y;
    static Camera3d world_camera;
    Viewport(GLuint texture);
    void draw();
    void update();
};
