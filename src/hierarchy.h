#pragma once

#include <memory>

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include "world.h"
#include "entity.h"
#include "editor_window.h"

class Hierarchy : public EditorWindow
{
public:
    static std::shared_ptr<Entity> selected_entity;
    int selected_world_entity_ID = 0;
    int ID;
    
    Hierarchy();
    void imgui_entity_children(std::shared_ptr<Entity> entity);
    void imgui_hierarchy();
    void update() override;
    void draw() override;
};