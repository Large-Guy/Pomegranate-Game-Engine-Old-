#include"inspector.h"

//Functions
Inspector::Inspector() : inspector_id(0){}
void Inspector::display_vector4(glm::vec4*v)
{
    ImGui::PushItemWidth(40);
    ImGui::InputFloat("X", &v->x, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::InputFloat("Y", &v->y, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::InputFloat("Z", &v->z, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::InputFloat("W", &v->w, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::PopItemWidth();
    ImGui::Text("VECTOR 4");
    ImGui::PopID();
}
void Inspector::display_vector3(glm::vec3*v)
{
    ImGui::PushItemWidth(40);
    ImGui::InputFloat("X", &v->x, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::InputFloat("Y", &v->y, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::InputFloat("Z", &v->z, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::PopItemWidth();
    ImGui::Text("VECTOR 3");
    ImGui::PopID();
}
void Inspector::display_vector2(glm::vec2*v)
{
    ImGui::PushItemWidth(80);
    ImGui::InputFloat("X", &v->x, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::InputFloat("Y", &v->y, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::PopItemWidth();
    ImGui::Text("VECTOR 2");
    ImGui::PopID();
}
void Inspector::display_vector1(glm::vec1*v)
{
    ImGui::PushItemWidth(120);
    ImGui::InputFloat("X", &v->x, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::PopItemWidth();
    ImGui::Text("VECTOR 1");
    ImGui::PopID();
}
void Inspector::display_float(float*v)
{
    ImGui::PushItemWidth(120);
    ImGui::InputFloat("FLOAT", v, 0.0f, 5.0f);
    ImGui::PopItemWidth();
    ImGui::PopID();
}
void Inspector::display_bool(bool*v)
{
    ImGui::PushItemWidth(120);
    ImGui::Checkbox("BOOL", v);
    ImGui::PopItemWidth();
    ImGui::PopID();
}
void Inspector::display_multiline(std::string*v)
{
    ImGui::PushItemWidth(ImGui::GetWindowWidth()-32);
    ImGui::Text("STRING");
    ImGui::InputTextMultiline("", v);
    ImGui::PopItemWidth();
    ImGui::PopID();
}
void Inspector::display_string(std::string*v)
{
    ImGui::PushItemWidth(120);
    ImGui::InputText("STRING", v);
    ImGui::PopItemWidth();
    ImGui::PopID();
}
void Inspector::display_asset(std::string*v)
{
    ImGui::PushItemWidth(120);
    ImGui::InputText("STRING", v); ImGui::SameLine();
    if(ImGui::Button("BROWSE"))
    {
        std::cout << "BROWSING" << std::endl;
    }
    ImGui::PopItemWidth();
    ImGui::PopID();
}
void Inspector::display_color(glm::vec4* v)
{
    float c[4] = {v->x,v->y,v->z,v->w};
    ImGui::ColorPicker4("COLOR",c);
    v->x = c[0];
    v->y = c[1];
    v->z = c[2];
    v->w = c[3];
    ImGui::PopID();
}
void Inspector::draw()
{
    ImGui::Begin((std::string("Inspector - WinID") + std::to_string(MyID)).c_str(),&open);
    inspector_id = 0;

    //Inspect entity
    if(Hierarchy::selected_entity!=nullptr)
    {
        //Display entity ID
        ImGui::Text("Entity ID: %i",Hierarchy::selected_entity->ID);

        //Display properties
        for (size_t i = 0; i < Hierarchy::selected_entity->properties.size(); i++)
        {
            //Push Id and display properties name
            ImGui::PushID(inspector_id++);
            ImGui::Text(Hierarchy::selected_entity->properties[i].name.c_str()); ImGui::SameLine();
            
            //Display properties
            switch (Hierarchy::selected_entity->properties[i].type) 
            {
                case PROPERTY_FLOAT: 
                {
                    float* v = (float*)Hierarchy::selected_entity->properties[i].value;
                    display_float(v);
                    break;
                }
                case PROPERTY_STRING: 
                {
                    std::string* v = (std::string*)Hierarchy::selected_entity->properties[i].value;
                    display_string(v);
                    break;
                }
                case PROPERTY_MULTILINE: 
                {
                    std::string* v = (std::string*)Hierarchy::selected_entity->properties[i].value;
                    display_multiline(v);
                    break;
                }
                case PROPERTY_ASSET: 
                {
                    std::string* v = (std::string*)Hierarchy::selected_entity->properties[i].value;
                    display_asset(v);
                    break;
                }
                case PROPERTY_VECTOR1: 
                {
                    glm::vec1* v = (glm::vec1*)Hierarchy::selected_entity->properties[i].value;
                    display_vector1(v);
                    break;
                }
                case PROPERTY_VECTOR2: 
                {
                    glm::vec2* v = (glm::vec2*)Hierarchy::selected_entity->properties[i].value;
                    display_vector2(v);
                    break;
                }
                case PROPERTY_VECTOR3: 
                {
                    glm::vec3* v = (glm::vec3*)Hierarchy::selected_entity->properties[i].value;
                    display_vector3(v);
                    break;
                }
                case PROPERTY_VECTOR4: 
                {
                    glm::vec4* v = (glm::vec4*)Hierarchy::selected_entity->properties[i].value;
                    display_vector4(v);
                    break;
                }
                case PROPERTY_COLOR: 
                {
                    glm::vec4* v = (glm::vec4*)Hierarchy::selected_entity->properties[i].value;
                    display_color(v);
                    break;
                }
                case PROPERTY_BOOL: 
                {
                    bool* v = (bool*)Hierarchy::selected_entity->properties[i].value;
                    display_bool(v);
                    break;
                }
            }
        }
    }

    ImGui::End();
}