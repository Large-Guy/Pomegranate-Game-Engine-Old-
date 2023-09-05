#include"console.h"

std::ostringstream Console::output;

Console::Console()
{
    Console::output = std::ostringstream();
}
void Console::print(std::string v)
{
    Console::output << v;
}
void Console::teascript_print(TeaState*T)
{
    int* len;
    const char* s = tea_check_lstring(T,0,len);

    print(std::string(s));

    tea_push_null(T);
}
void Console::clear()
{
    Console::output.str("");
}
void Console::teascript_clear(TeaState*T)
{
    clear();

    tea_push_null(T);
}
void Console::draw() 
{
    ImGui::Begin((std::string("Console - WinID") + std::to_string(MyID)).c_str(),&open);

    ImGui::Text("%s", output.str().c_str());

    ImGui::End();
}