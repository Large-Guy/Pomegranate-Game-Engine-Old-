#include"inspector.h"
Inspector::Inspector() : inspector_id(0)
{
}
void Inspector::DisplayVector4(glm::vec4*v)
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
void Inspector::DisplayVector3(glm::vec3*v)
{
    ImGui::PushItemWidth(40);
    ImGui::InputFloat("X", &v->x, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::InputFloat("Y", &v->y, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::InputFloat("Z", &v->z, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::PopItemWidth();
    ImGui::Text("VECTOR 3");
    ImGui::PopID();
}
void Inspector::DisplayVector2(glm::vec2*v)
{
    ImGui::PushItemWidth(80);
    ImGui::InputFloat("X", &v->x, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::InputFloat("Y", &v->y, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::PopItemWidth();
    ImGui::Text("VECTOR 2");
    ImGui::PopID();
}
void Inspector::DisplayVector1(glm::vec1*v)
{
    ImGui::PushItemWidth(120);
    ImGui::InputFloat("X", &v->x, 0.0f, 5.0f); ImGui::SameLine();
    ImGui::PopItemWidth();
    ImGui::Text("VECTOR 1");
    ImGui::PopID();
}
void Inspector::DisplayFloat(float*v)
{
    ImGui::PushItemWidth(120);
    ImGui::InputFloat("FLOAT", v, 0.0f, 5.0f);
    ImGui::PopItemWidth();
    ImGui::PopID();
}
void Inspector::DisplayString(std::string*v)
{
    ImGui::PushItemWidth(120);
    ImGui::InputText("STRING", v);
    ImGui::PopItemWidth();
    ImGui::PopID();
}
void Inspector::DisplayAsset(std::string*v)
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
void Inspector::DisplayColor(Color* v)
{
    ImGui::ColorPicker4("COLOR", v->data);
    ImGui::PopID();
}
void Inspector::draw()
{
    ImGui::Begin((std::string("Inspector - WinID") + std::to_string(MyID)).c_str(),&open);
    inspector_id = 0;
    if(Hierarchy::selected_entity!=nullptr)
    {
        ImGui::Text("Entity ID: %i",Hierarchy::selected_entity->ID);
        for (size_t i = 0; i < Hierarchy::selected_entity->properties.size(); i++)
        {
            ImGui::PushID(inspector_id++);
            ImGui::Text(((std::string)std::get<0>(Hierarchy::selected_entity->properties[i])).c_str()); ImGui::SameLine();
            if(((unsigned int)std::get<1>(Hierarchy::selected_entity->properties[i])) == PROPERTY_FLOAT)
            {
                float*v = ((float*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                DisplayFloat(v);
            }
            else if(((unsigned int)std::get<1>(Hierarchy::selected_entity->properties[i])) == PROPERTY_STRING)
            {
                std::string*v = ((std::string*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                DisplayString(v);
            }
            else if(((unsigned int)std::get<1>(Hierarchy::selected_entity->properties[i])) == PROPERTY_ASSET)
            {
                std::string*v = ((std::string*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                DisplayAsset(v);
            }
            else if(((unsigned int)std::get<1>(Hierarchy::selected_entity->properties[i])) == PROPERTY_VECTOR1)
            {
                glm::vec1*v = ((glm::vec1*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                DisplayVector1(v);
            }
            else if(((unsigned int)std::get<1>(Hierarchy::selected_entity->properties[i])) == PROPERTY_VECTOR2)
            {
                glm::vec2*v = ((glm::vec2*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                DisplayVector2(v);
            }
            else if(((unsigned int)std::get<1>(Hierarchy::selected_entity->properties[i])) == PROPERTY_VECTOR3)
            {
                glm::vec3*v = ((glm::vec3*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                DisplayVector3(v);
            }
            else if(((unsigned int)std::get<1>(Hierarchy::selected_entity->properties[i])) == PROPERTY_COLOR)
            {
                Color*v = ((Color*)std::get<2>(Hierarchy::selected_entity->properties[i]));
                DisplayColor(v);
            }
        }
        
    }
    ImGui::End();
}