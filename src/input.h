#pragma once

#include <iostream>
#include <string>

#include "../lib/glad/glad.h"
#include <GLFW/glfw3.h>

#include "tea.hpp"

#include "windows.h"

//Variables
extern const TeaModule input_module[];

//Functions
bool input_down(int key);
void input_down_tea(TeaState*T);
bool input_up(int key);
void input_up_tea(TeaState*T);
void teascript_input_axis(TeaState*T);
void TeaModule_add_input(TeaState*T);