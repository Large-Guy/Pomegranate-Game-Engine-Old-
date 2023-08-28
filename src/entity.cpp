#include"entity.h"
Entity::Entity(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
    properties = std::vector<std::tuple<std::string,unsigned int,void*>>();
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
    this->children = std::vector<std::shared_ptr<Entity>>();
    this->parent = nullptr;
    this->model_matrix = glm::mat4(1.0f);
    ID = NODE_ID;
    NODE_ID++;
    add_property("Name",&this->name,PROPERTY_STRING);
    add_property("Position",&this->position,PROPERTY_VECTOR3);
    add_property("Scale",&this->scale,PROPERTY_VECTOR3);
    add_property("Rotation",&this->rotation,PROPERTY_VECTOR3);
}
Entity::Entity()
{
    properties = std::vector<std::tuple<std::string,unsigned int,void*>>();
    this->position = glm::vec3(0.0f);
    this->scale = glm::vec3(1.0f);
    this->rotation = glm::vec3(0.0f,0.0f,0.0f);
    this->children = std::vector<std::shared_ptr<Entity>>();
    this->parent = nullptr;
    this->model_matrix = glm::mat4(1.0f);
    ID = NODE_ID;
    NODE_ID++;
    add_property("Name",&this->name,PROPERTY_STRING);
    add_property("Position",&this->position,PROPERTY_VECTOR3);
    add_property("Scale",&this->scale,PROPERTY_VECTOR3);
    add_property("Rotation",&this->rotation,PROPERTY_VECTOR3);
}
void Entity::add_property(std::string name, void* property, unsigned int type)
{
    properties.push_back(std::tuple<std::string,unsigned int,void*>{name,type,property});
}
void Entity::add_child(std::shared_ptr<Entity> entity)
{
    entity->parent = this;
    children.push_back(entity);
}
void Entity::update(float delta){}
void Entity::draw(float delta){} 
glm::mat4 Entity::get_model_matrix(int i)
{
    glm::mat4 modelMatrix = glm::mat4(1.0f); // Initialize as an identity matrix
    modelMatrix = glm::translate(modelMatrix, position);
    //modelMatrix = glm::scale(modelMatrix,scale);
    modelMatrix = modelMatrix * glm::mat4_cast(glm::quat(rotation));
    if(parent!=nullptr)
    {
        modelMatrix = parent->model_matrix*modelMatrix;
    }
    this->model_matrix = modelMatrix;
    return modelMatrix;
}
int Entity::NODE_ID = 0;