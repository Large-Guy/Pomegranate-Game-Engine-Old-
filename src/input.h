#ifndef INPUT_H
#define INPUT_H

#include"tea.hpp"
#include"string"
#include "../lib/glad/glad.h"
#include <GLFW/glfw3.h>
#include"iostream"
#include"windows.h"

//Variables
extern const TeaModule input_module[];

//Functions
bool input_down(int key);
void input_down_tea(TeaState*T);
bool input_up(int key);
void input_up_tea(TeaState*T);
void TeaModule_add_input(TeaState*T);

#endif