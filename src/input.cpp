#include"input.h"
bool input_down(int key)
{
    return glfwGetKey(window,key);
}
void input_down_tea(TeaState*T)
{
    int l = 0;
    int i = 0;
    if(tea_is_number(T,0) == true)
        i = (int)tea_check_number(T,0);
    else if(tea_is_string(T,0) == true)
        i = toupper(tea_check_lstring(T,0,&l)[0]);
    tea_push_bool(T,glfwGetKey(window,i));
}
bool input_up(int key)
{
    return !glfwGetKey(window,key);
}
void input_up_tea(TeaState*T)
{
    int l = 0;
    int i = 0;
    if(tea_is_number(T,0) == true)
        i = (int)tea_check_number(T,0);
    else if(tea_is_string(T,0) == true)
        i = toupper(tea_check_lstring(T,0,&l)[0]);
    tea_push_bool(T,!glfwGetKey(window,i));
}
const TeaModule input_module[] = 
{
    {"down",input_down_tea},
    {"up",input_up_tea},
    {NULL,NULL}
};

void TeaModule_add_input(TeaState*T)
{
    tea_create_module(T,"input",input_module);
    tea_pop(T,1);
}