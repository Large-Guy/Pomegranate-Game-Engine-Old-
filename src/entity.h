#pragma once

#include <map>
#include <vector>
#include <string>
#include <memory>

#include "tea.hpp"
#include "glm.hpp"
#include "ext.hpp"

#include "tea_tools.h"

extern const TeaModule TeaModule_entity[];

enum PropertyType
{
    PROPERTY_FLOAT = 0,
    PROPERTY_INT = 1,
    PROPERTY_STRING = 2,
    PROPERTY_VECTOR4 = 3,
    PROPERTY_VECTOR3 = 5,
    PROPERTY_VECTOR2 = 6,
    PROPERTY_VECTOR1 = 7,
    PROPERTY_ASSET = 8,
    PROPERTY_COLOR = 9,
    PROPERTY_BOOL = 10,
};

class EntityProperty
{
public:
    std::string name;
    unsigned int type;
    void* value;
    EntityProperty(std::string name, unsigned int type, void* value);
};

class Entity
{
private:
    static int NODE_ID;
public:
    static Entity* current;
    static std::vector<Entity*> entities;
    std::vector<EntityProperty> properties;
    std::string name;
    int ID;
    int render_layers;
    Entity* parent;
    std::vector<std::shared_ptr<Entity>> children;
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 euler_angles;
    glm::vec3 rotation;
    glm::mat4 model_matrix;

    Entity();
    Entity(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
    void display_property(std::string name, void* property, unsigned int type);
    EntityProperty get_property(std::string name);
    void set_property(std::string name,PropertyType t, void* v);
    void add_child(std::shared_ptr<Entity> entity);
    virtual void update(float delta);
    virtual void draw(float delta);
    virtual void editor_draw(float delta);
    void entity_set_current();
    glm::mat4 get_model_matrix(int i = -1);
    static Entity* get_entity(std::string name);
    static Entity* get_entity(int id);
};

//Teascript

//Entity
void teascript_entity_display(TeaState*T);
void teascript_entity_self(TeaState*T);
void teascript_entity_find(TeaState*T);
void teascript_entity_get_property(TeaState*T);
void teascript_entity_set_property(TeaState*T);
void TeaModule_add_entity(TeaState* T);