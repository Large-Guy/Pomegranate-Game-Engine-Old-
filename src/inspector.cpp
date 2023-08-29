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
void Inspector::display_color(Color* v)
{
    ImGui::ColorPicker4("COLOR", v->data);
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
            ImGui::Text(((std::string)std::get<0>(Hierarchy::selected_entity->properties[i])).c_str()); ImGui::SameLine();
            
            //Display properties
            switch ((unsigned int)std::get<1>(Hierarchy::selected_entity->properties[i])) 
            {
                case PROPERTY_FLOAT: 
                {
                    float* v = ((float*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                    display_float(v);
                    break;
                }
                case PROPERTY_STRING: 
                {
                    std::string* v = ((std::string*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                    display_string(v);
                    break;
                }
                case PROPERTY_ASSET: 
                {
                    std::string* v = ((std::string*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                    display_asset(v);
                    break;
                }
                case PROPERTY_VECTOR1: 
                {
                    glm::vec1* v = ((glm::vec1*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                    display_vector1(v);
                    break;
                }
                case PROPERTY_VECTOR2: 
                {
                    glm::vec2* v = ((glm::vec2*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                    display_vector2(v);
                    break;
                }
                case PROPERTY_VECTOR3: 
                {
                    glm::vec3* v = ((glm::vec3*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                    display_vector3(v);
                    break;
                }
                case PROPERTY_VECTOR4: 
                {
                    glm::vec4* v = ((glm::vec4*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                    display_vector4(v);
                    break;
                }
                case PROPERTY_COLOR: 
                {
                    Color* v = ((Color*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                    display_color(v);
                    break;
                }
            }
        }
    }

    ImGui::End();
}