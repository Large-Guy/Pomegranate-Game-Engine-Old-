#include"editor_window.h"

//Variables
int EditorWindow::WindowID = 0;

//Functions
EditorWindow::EditorWindow() : MyID(WindowID++), open(true){}

//Virtuals
void EditorWindow::update(){}
void EditorWindow::draw(){}

//Teascript
void teascript_begin_window(TeaState* T)
{
    int len;
    const char* Name = tea_get_lstring(T,0,&len);
    ImGui::Begin(Name);
    tea_push_null(T);
}
void teascript_button(TeaState*T)
{
    int len;
    const char* txt = tea_get_lstring(T,0,&len);
    int press = ImGui::Button(txt);
    tea_push_bool(T,press);
}
void teascript_text(TeaState*T)
{
    int len;
    const char* txt = tea_get_lstring(T,0,&len);
    ImGui::Text("%s",txt);
    tea_push_null(T);
}
void teascript_checkbox(TeaState*T)
{
    int len;
    const char* txt = tea_get_lstring(T,0,&len);
    bool pressed = tea_get_bool(T,1);
    ImGui::Checkbox(txt,&pressed);
    tea_push_bool(T,pressed);
}
void teascript_end_window(TeaState* T)
{
    ImGui::End();
    tea_push_null(T);
}

//Tea Module
const TeaModule window_module[] = {
    {"open",teascript_begin_window},
    {"button",teascript_button},
    {"text",teascript_text},
    {"checkbox",teascript_checkbox},
    {"close",teascript_end_window},
    {NULL,NULL}
};

void TeaModule_add_window(TeaState*T)
{
    tea_create_module(T,"window",window_module);
    tea_pop(T,1); //Pop the module object
}