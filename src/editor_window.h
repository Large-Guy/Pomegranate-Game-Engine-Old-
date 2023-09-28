#pragma once

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>

#include "tea.hpp"

#include "tea_tools.h"

extern const TeaModule window_module[];

class EditorWindow
{
public:
    static int WindowID;
    int MyID;
    bool open;

    EditorWindow();

    virtual void update();
    virtual void draw();
};

void teascript_begin_window(TeaState* T);
void teascript_button(TeaState*T);
void teascript_text(TeaState*T);
void teascript_checkbox(TeaState*T);
void teascript_end_window(TeaState* T);
void TeaModule_add_window(TeaState*T);