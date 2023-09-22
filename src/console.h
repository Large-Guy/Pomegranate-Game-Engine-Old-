#pragma once

#include <sstream>
#include <string>
#include <vector>

#include <imgui.h>

#include "tea.hpp"

#include "editor_window.h"

class Console : public EditorWindow
{
public:
    Console();
    static std::ostringstream output;
    static void print(std::string v);
    static void teascript_print(TeaState* T);
    static void clear();
    static void teascript_clear(TeaState* T);
    void draw() override;
};