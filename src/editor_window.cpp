#include"editor_window.h"
int EditorWindow::WindowID = 0;
EditorWindow::EditorWindow() : MyID(WindowID++), open(true){}
void EditorWindow::update(){}
void EditorWindow::draw(){}