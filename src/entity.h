#ifndef ENTITY_H
#define ENTITY_H

#include"glm.hpp"
#include "ext.hpp"
#include"vector"
#include"string"
#include"memory"

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
};

class Entity
{
private:
    static int NODE_ID;
public:
    std::vector<std::tuple<std::string,unsigned int,void*>> properties;
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
    void add_child(std::shared_ptr<Entity> entity);
    virtual void update(float delta);
    virtual void draw(float delta);
    virtual void editor_draw(float delta);
    glm::mat4 get_model_matrix(int i = -1);
};

#endif