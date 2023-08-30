#include"pomegranate_lib.h"

//Functions
void teascript_vec4_add(TeaState* T)
{
    glm::vec4 a = tea_tools_check_vec4(T,0);
    glm::vec4 b = tea_tools_check_vec4(T,1);
    tea_tools_push_vec4(T,a+b);
}
void teascript_vec3_add(TeaState* T)
{
    glm::vec3 a = tea_tools_check_vec3(T,0);
    glm::vec3 b = tea_tools_check_vec3(T,1);
    tea_tools_push_vec3(T,a+b);
}
void teascript_vec2_add(TeaState* T)
{
    glm::vec2 a = tea_tools_check_vec2(T,0);
    glm::vec2 b = tea_tools_check_vec2(T,1);
    tea_tools_push_vec2(T,a+b);
}
void teascript_vec4_sub(TeaState* T)
{
    glm::vec4 a = tea_tools_check_vec4(T,0);
    glm::vec4 b = tea_tools_check_vec4(T,1);
    tea_tools_push_vec4(T,a-b);
}
void teascript_vec3_sub(TeaState* T)
{
    glm::vec3 a = tea_tools_check_vec3(T,0);
    glm::vec3 b = tea_tools_check_vec3(T,1);
    tea_tools_push_vec3(T,a-b);
}
void teascript_vec2_sub(TeaState* T)
{
    glm::vec2 a = tea_tools_check_vec2(T,0);
    glm::vec2 b = tea_tools_check_vec2(T,1);
    tea_tools_push_vec2(T,a-b);
}
void teascript_vec4_mul(TeaState* T)
{
    glm::vec4 a = tea_tools_check_vec4(T,0);
    glm::vec4 b = tea_tools_check_vec4(T,1);
    tea_tools_push_vec4(T,a*b);
}
void teascript_vec3_mul(TeaState* T)
{
    glm::vec3 a = tea_tools_check_vec3(T,0);
    float b = tea_check_number(T,1);
    tea_tools_push_vec3(T,a*b);
}
void teascript_vec2_mul(TeaState* T)
{
    glm::vec2 a = tea_tools_check_vec2(T,0);
    float b = tea_check_number(T,1);
    tea_tools_push_vec2(T,a*b);
}
void teascript_vec4_div(TeaState* T)
{
    glm::vec4 a = tea_tools_check_vec4(T,0);
    glm::vec4 b = tea_tools_check_vec4(T,1);
    tea_tools_push_vec4(T,a/b);
}
void teascript_vec3_div(TeaState* T)
{
    glm::vec3 a = tea_tools_check_vec3(T,0);
    float b = tea_check_number(T,1);
    tea_tools_push_vec3(T,a/b);
}
void teascript_vec2_div(TeaState* T)
{
    glm::vec2 a = tea_tools_check_vec2(T,0);
    float b = tea_check_number(T,1);
    tea_tools_push_vec2(T,a/b);
}
void teascript_vec4_dist(TeaState*T)
{
    glm::vec4 a = tea_tools_check_vec4(T,0);
    glm::vec4 b = tea_tools_check_vec4(T,1);
    tea_push_number(T,glm::distance(a,b));
}
void teascript_vec3_dist(TeaState*T)
{
    glm::vec3 a = tea_tools_check_vec3(T,0);
    glm::vec3 b = tea_tools_check_vec3(T,1);
    tea_push_number(T,glm::distance(a,b));
}
void teascript_vec2_dist(TeaState*T)
{
    glm::vec2 a = tea_tools_check_vec2(T,0);
    glm::vec2 b = tea_tools_check_vec2(T,1);
    tea_push_number(T,glm::distance(a,b));
}


//Tea module
const TeaModule TeaModule_pomegranate[] = {
    {"add4",teascript_vec4_add},
    {"add3",teascript_vec3_add},
    {"add2",teascript_vec2_add},
    {"sub4",teascript_vec4_sub},
    {"sub3",teascript_vec3_sub},
    {"sub2",teascript_vec2_sub},
    {"mul4",teascript_vec4_mul},
    {"mul3",teascript_vec3_mul},
    {"mul2",teascript_vec2_mul},
    {"div4",teascript_vec4_div},
    {"div3",teascript_vec3_div},
    {"div2",teascript_vec2_div},
    {"dist4",teascript_vec4_dist},
    {"dist3",teascript_vec3_dist},
    {"dist2",teascript_vec2_dist},
    {NULL,NULL}
};

void TeaModule_add_pomegranate(TeaState* T)
{
    tea_create_module(T,"pomegranate",TeaModule_pomegranate);
    tea_pop(T,1);
}