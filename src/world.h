#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "entity.h"

class World
{
public:
    std::vector<std::shared_ptr<Entity>> entities;
    static World* current;
    
    World();
    void add_entity(std::shared_ptr<Entity> entity);
    std::shared_ptr<Entity> get_entity(std::string name);
    void print_entity_children(std::shared_ptr<Entity> entity, int tab);
    void print_hierarchy();
    void set_current();
    void update(int render_layers);
    void draw(int render_layers);
    void ui(int render_layers);
};