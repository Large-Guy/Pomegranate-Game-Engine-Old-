#ifndef TEA_TOOLS_H
#define TEA_TOOLS_H

#include"tea.hpp"
#include"glm.hpp"
#include"ext.hpp"
#include"iostream"

//Functions
glm::vec3 tea_tools_check_vec3(TeaState* T, int i);
void tea_tools_push_vec3(TeaState* T,glm::vec3 v);
glm::vec4 tea_tools_check_vec4(TeaState* T, int i);
void tea_tools_push_vec4(TeaState* T,glm::vec4 v);
glm::vec2 tea_tools_check_vec2(TeaState* T, int i);
void tea_tools_push_vec2(TeaState* T,glm::vec2 v);

#endif