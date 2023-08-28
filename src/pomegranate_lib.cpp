#include"pomegranate_lib.h"
void teascript_vec3_add(TeaState* T)
{
    glm::vec3 a = tea_tools_check_vec3(T,0);
    glm::vec3 b = tea_tools_check_vec3(T,1);
    glm::vec3 c = a+b;
    //tea_tools_push_vec3(T,a+b);
    tea_push_null(T);
}

const TeaModule TeaModule_pomegranate[] = {
    {"add3",teascript_vec3_add}
};

void TeaModule_add_pomegranate(TeaState* T)
{
    tea_create_module(T,"pomegranate",TeaModule_pomegranate);
    tea_pop(T,1);
}