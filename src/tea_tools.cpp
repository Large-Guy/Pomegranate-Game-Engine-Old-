#include"tea_tools.h"
glm::vec3 tea_tools_check_vec3(TeaState* T, int i)
{
    if(tea_is_list(T, i))
    {
        tea_get_item(T, i, 0);
        double x = tea_check_number(T, -1); //Gets stuck here
        tea_pop(T, 1);
        tea_get_item(T, i, 1);
        double y = tea_check_number(T, -1);
        tea_pop(T, i+1);
        tea_get_item(T, i, 2);
        double z = tea_check_number(T, -1);
        tea_pop(T, i+1);
        return glm::vec3(x,y,z);
    }
    return glm::vec3(0,0,0);
}
glm::vec2 tea_tools_check_vec2(TeaState* T, int i)
{
    if(tea_is_list(T, i))
    {
        tea_get_item(T, i, 0);
        double x = tea_check_number(T, -1); //Gets stuck here
        tea_pop(T, 1);
        tea_get_item(T, i, 1);
        double y = tea_check_number(T, -1);
        tea_pop(T, i+1);
        return glm::vec2(x,y);
    }
    return glm::vec2(0,0);
}
glm::vec4 tea_tools_check_vec4(TeaState* T, int i)
{
    if(tea_is_list(T, i))
    {
        tea_get_item(T, i, 0);
        double x = tea_check_number(T, -1); //Gets stuck here
        tea_pop(T, 1);
        tea_get_item(T, i, 1);
        double y = tea_check_number(T, -1);
        tea_pop(T, i+1);
        tea_get_item(T, i, 2);
        double z = tea_check_number(T, -1);
        tea_pop(T, i+1);
        tea_get_item(T, i, 3);
        double w = tea_check_number(T, -1);
        tea_pop(T, i+1);
        return glm::vec4(x,y,z,w);
    }
    return glm::vec4(0,0,0,0);
}
void tea_tools_push_vec3(TeaState* T,glm::vec3 v)
{
    tea_new_list(T);
    tea_push_number(T,(double)v.x);
    tea_add_item(T,-2);
    tea_push_number(T,(double)v.y);
    tea_add_item(T,-2);
    tea_push_number(T,(double)v.z);
    tea_add_item(T,-2);
}