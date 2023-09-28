#include"world.h"

//Variables
World* World::current = nullptr;

//Functions
World::World()
{
    entities = std::vector<std::shared_ptr<Entity>>();
}
void World::add_entity(std::shared_ptr<Entity> entity)
{
    entities.push_back(entity);
}
std::shared_ptr<Entity> World::get_entity(std::string name)
{
    for (long unsigned int i = 0; i < entities.size(); i++)
    {
        if(entities[i]->name == name)
        {
            return entities[i];
        }
    }
}
void World::print_entity_children(std::shared_ptr<Entity> entity, int tab)
{
    if (entity->children.empty()) {
        return; // No children, so we don't need to print anything
    }

    for (long unsigned int i = 0; i < entity->children.size(); i++)
    {
        std::shared_ptr<Entity> child = entity->children[i];

        // Print indentation for visualizing the hierarchy
        for (int j = 0; j < tab; j++)
        {
            std::cout << "  "; // Two spaces for each level of indentation
        }

        // Print the child entity's name
        std::cout << "- " << child->name << std::endl;

        // Recursively print children of the child entity
        print_entity_children(child, tab + 1);
    }
}
void World::print_hierarchy()
{
    for (long unsigned int i = 0; i < entities.size(); i++)
    {
        std::shared_ptr<Entity> entity = entities[i];

        // Print the current entity's name
        std::cout << entity->name << std::endl;

        // Print children of the current entity (if any)
        print_entity_children(entity, 1);
    }
}
void World::set_current()
{
    current = this;
}
void World::update(int render_layers)
{
    for(long unsigned int i = 0; i < entities.size(); i++)
    {
        if(entities[i]->render_layers & render_layers)
        {
            entities[i]->entity_set_current();
            entities[i]->update(0.016f);
            
            //Editor
            entities[i]->editor_update(0.016f);
            
            for(long unsigned int z = 0; z < entities[i]->children.size(); z++)
            {
                entities[i]->children[z]->entity_set_current();
                entities[i]->children[z]->update(0.016f);
                //Editor
                entities[i]->editor_update(0.016f);
            }
        }
    }
}

void World::ui(int render_layers)
{
    for(long unsigned int i = 0; i < entities.size(); i++)
    {
        if(entities[i]->render_layers & render_layers)
        {
            entities[i]->entity_set_current();
            entities[i]->ui(0.016f);
            
            //Editor
            entities[i]->editor_ui(0.016f);
            
            for(long unsigned int z = 0; z < entities[i]->children.size(); z++)
            {
                entities[i]->children[z]->entity_set_current();
                entities[i]->children[z]->update(0.016f);
                //Editor
                entities[i]->editor_update(0.016f);
            }
        }
    }
}
void World::draw(int render_layers)
{
    for(long unsigned int i = 0; i < entities.size(); i++)
    {
        if(entities[i]->render_layers & render_layers)
        {
            entities[i]->entity_set_current();
            entities[i]->draw(0.016f);
            
            //editor
            entities[i]->editor_draw(0.016f);
            for(long unsigned int z = 0; z < entities[i]->children.size(); z++)
            {
                entities[i]->children[z]->entity_set_current();
                entities[i]->children[z]->draw(0.016f);
                //editor
                entities[i]->editor_draw(0.016f);
            }
        }
    }
}