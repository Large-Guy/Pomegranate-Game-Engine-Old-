#ifndef CONSOLE_H
#define CONSOLE_H

#include"imgui.h"
#include"editor_window.h"
#include"string"
#include"tea.hpp"
#include"vector"

class Console : public EditorWindow
{
public:
    Console();
    static std::vector<std::string> output;
    static void print(std::string v);
    static void teascript_print(TeaState* T);
    static void clear();
    static void teascript_clear(TeaState* T);
    void draw() override;
};

#endif