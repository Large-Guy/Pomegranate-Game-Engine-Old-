#pragma once

#include <iostream>

#include "tea.hpp"
#include "glm.hpp"
#include "ext.hpp"

#include "tea_tools.h"
#include "windows.h"

//Variables
extern const TeaModule TeaModule_pomegranate[];

//Functions

//Vec
void teascript_vec4_add(TeaState* T);
void teascript_vec4_sub(TeaState* T);
void teascript_vec4_mul(TeaState* T);
void teascript_vec4_div(TeaState* T);

void teascript_vec3_add(TeaState* T);
void teascript_vec3_sub(TeaState* T);
void teascript_vec3_mul(TeaState* T);
void teascript_vec3_div(TeaState* T);

void teascript_vec2_add(TeaState* T);
void teascript_vec2_sub(TeaState* T);
void teascript_vec2_mul(TeaState* T);
void teascript_vec2_div(TeaState* T);

void teascript_vec4_dist(TeaState* T);
void teascript_vec3_dist(TeaState* T);
void teascript_vec2_dist(TeaState* T);

void teascript_vec4_dot(TeaState* T);
void teascript_vec3_dot(TeaState* T);
void teascript_vec2_dot(TeaState* T);

void teascript_vec4_nor(TeaState* T);
void teascript_vec3_nor(TeaState* T);
void teascript_vec2_nor(TeaState* T);

//Editor
//Temp
void teascript_editor_close(TeaState*T);

void TeaModule_add_pomegranate(TeaState* T);