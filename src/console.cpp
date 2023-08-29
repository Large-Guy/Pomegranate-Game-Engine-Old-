#include"console.h"

std::vector<std::string> Console::output;

Console::Console()
{
    
}
void Console::print(std::string v)
{
    Console::output.push_back(v);
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
    output.clear();
}
void Console::teascript_clear(TeaState*T)
{
    clear();

    tea_push_null(T);
}
void Console::draw() 
{
    ImGui::Begin((std::string("Console - WinID") + std::to_string(MyID)).c_str(),&open);

    // Display the console output
    for (const std::string& message : output)
    {
        ImGui::Text("%s", message.c_str());
    }

    ImGui::End();
}