#include"input.h"

//Functions
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
        i = toupper(tea_check_lstring(T,0,&l)[0]); //Convert to upper for correct char code
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
        i = toupper(tea_check_lstring(T,0,&l)[0]);//Convert to upper for correct char code

    tea_push_bool(T,!glfwGetKey(window,i));
}
void teascript_input_axis(TeaState*T)
{
    int l = 0;
    int a = 0;
    if(tea_is_number(T,0) == true)
        a = (int)tea_check_number(T,0);
    else if(tea_is_string(T,0) == true)
        a = toupper(tea_check_lstring(T,0,&l)[0]); //Convert to upper for correct char code
    int b = 0;
    if(tea_is_number(T,1) == true)
        b = (int)tea_check_number(T,1);
    else if(tea_is_string(T,1) == true)
        b = toupper(tea_check_lstring(T,1,&l)[0]); //Convert to upper for correct char code
    float axis = 0;
    if(glfwGetKey(window,a)) axis -= 1;
    if(glfwGetKey(window,b)) axis += 1;
    tea_push_number(T,axis);
}
//Tea module
const TeaModule input_module[] = 
{
    {"down",input_down_tea},
    {"up",input_up_tea},
    {"axis",teascript_input_axis},
    {NULL,NULL}
};

void TeaModule_add_input(TeaState*T)
{
    tea_create_module(T,"input",input_module);
    tea_pop(T,1);
}