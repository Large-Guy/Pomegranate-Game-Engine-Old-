#include"hierarchy.h"

//Variables
std::shared_ptr<Entity> Hierarchy::selected_entity  = std::shared_ptr<Entity>(nullptr);

//Functions
Hierarchy::Hierarchy() : selected_world_entity_ID(0), ID(0){}
void Hierarchy::imgui_entity_children(std::shared_ptr<Entity> entity)
{
    ImGui::PushID(ID++);
    const char* name = "Empty Entity";
    if(!entity->name.empty())
    {
        name = entity->name.c_str();
    }
    if (entity->children.empty()) 
    {
        if(ImGui::Selectable(name,entity->ID == selected_world_entity_ID))
        {
            selected_entity = (entity);
            selected_world_entity_ID = entity->ID;
        }
    }
    else
    {
        ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
        if(selected_world_entity_ID == entity->ID)
        {
            flags |= ImGuiTreeNodeFlags_Selected;
        }
        bool open = ImGui::TreeNodeEx((void*)(intptr_t)entity->ID,flags,name,entity->ID);
        if(ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
            if(entity->name.empty())
            {
                ImGui::Text("");
            }
            else
            {
                ImGui::Text(name);
            }
            ImGui::EndDragDropSource();
        }
        if(ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
        {
            selected_entity = (entity);
            selected_world_entity_ID = entity->ID;
        }
        if(open)
        {
            for (long unsigned int i = 0; i < entity->children.size(); i++)
            {
                std::shared_ptr<Entity> child = entity->children[i];
                // Recursively print children of the child entity
                imgui_entity_children(child);
            }
            ImGui::TreePop();
        }
    }
    ImGui::PopID();
}
void Hierarchy::imgui_hierarchy()
{
    ID = 0;
    for (long unsigned int i = 0; i < World::current->entities.size(); i++)
    {
        std::shared_ptr<Entity> entity = World::current->entities[i];

        // Print the current entity's name
        // Print children of the current entity (if any)
        imgui_entity_children(entity);
    }
}
void Hierarchy::update(){}
void Hierarchy::draw()
{
    ImGui::Begin((std::string("Hierarchy - WinID") + std::to_string(MyID)).c_str(),&open);
    ImGui::BeginChild("Hierarchy Scroll");
    imgui_hierarchy();
    ImGui::EndChild();
    ImGui::End();
}