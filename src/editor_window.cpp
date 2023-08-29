#include"editor_window.h"

//Variables
int EditorWindow::WindowID = 0;

//Functions
EditorWindow::EditorWindow() : MyID(WindowID++), open(true){}

//Virtuals
void EditorWindow::update(){}
void EditorWindow::draw(){}