#include"entity.h"

//Variables
int Entity::NODE_ID = 0;
Entity* Entity::current = nullptr;
std::vector<std::shared_ptr<Entity>> Entity::entities = std::vector<std::shared_ptr<Entity>>();

//Functions
EntityProperty::EntityProperty(std::string name, unsigned int type, void* value)
{
    this->name = name;
    this->type = type;
    this->value = value;
}

Entity::Entity(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
    this->properties = std::vector<EntityProperty>();
    this->position = position;
    this->scale = scale;
    this->rotation = rotation;
    this->children = std::vector<std::shared_ptr<Entity>>();
    this->parent = nullptr;
    this->model_matrix = glm::mat4(1.0f);
    this->ID = Entity::NODE_ID++;
    std::cout << "Pushed me" << std::endl;
    Entity::entities.push_back(std::make_shared<Entity>(*this));
    std::cout << entities.size() << std::endl;
    //Display base properties
    display_property("name",&this->name,PROPERTY_STRING);
    display_property("position",&this->position,PROPERTY_VECTOR3);
    display_property("scale",&this->scale,PROPERTY_VECTOR3);
    display_property("rotation",&this->rotation,PROPERTY_VECTOR3);
}
Entity::Entity()
{
    this->properties = std::vector<EntityProperty>();
    this->position = glm::vec3(0.0f);
    this->scale = glm::vec3(1.0f);
    this->rotation = glm::vec3(0.0f,0.0f,0.0f);
    this->children = std::vector<std::shared_ptr<Entity>>();
    this->parent = nullptr;
    this->model_matrix = glm::mat4(1.0f);
    this->ID = Entity::NODE_ID++;
    std::cout << "Pushed me" << std::endl;
    Entity::entities.push_back(std::make_shared<Entity>(*this));
    std::cout << entities.size() << std::endl;
    //Display base properties
    display_property("name",&this->name,PROPERTY_STRING);
    display_property("position",&this->position,PROPERTY_VECTOR3);
    display_property("scale",&this->scale,PROPERTY_VECTOR3);
    display_property("rotation",&this->rotation,PROPERTY_VECTOR3);
}
void Entity::display_property(std::string name, void* property, unsigned int type)
{
    properties.push_back(EntityProperty(name,type,property));
}
EntityProperty Entity::get_property(std::string name)
{
    std::cout << "finding property: " << name << std::endl;
    for (size_t i = 0; i < properties.size(); i++)
    {
        if(properties[i].name==name)
        {
            std::cout << "Found property :)" << std::endl;
            return properties[i];
        }
    }
}
void Entity::set_property(std::string name,PropertyType t, void* v)
{
    for (size_t i = 0; i < properties.size(); i++)
    {
        if(properties[i].name==name)
        {
            switch (t)
            {
                case PROPERTY_FLOAT:
                {
                    *(float*)properties[i].value = *(float*)v;
                    break;
                }
                case PROPERTY_INT:
                {
                    *(int*)properties[i].value = *(int*)v;
                    break;
                }
                case PROPERTY_STRING:
                {
                    *(std::string*)properties[i].value = *(std::string*)v;
                    break;
                }
                case PROPERTY_BOOL:
                {
                    *(bool*)properties[i].value = *(bool*)v;
                    break;
                }
            }
            break;
        }
    }
}
void Entity::add_child(std::shared_ptr<Entity> entity)
{
    entity->parent = this;
    children.push_back(entity);
}
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
void Entity::entity_set_current()
{
    Entity::current = this;
}
std::shared_ptr<Entity> Entity::get_entity(std::string name)
{
    std::cout << "Finding Entity, Total: " << Entity::entities.size() << " Searching: " << std::endl;
    for (int i = 0; i < Entity::entities.size(); i++)
    {
        std::cout << Entity::entities[i]->ID << std::endl;
        if(Entity::entities[i]->name == name)
        {
            return Entity::entities[i];
        }
    }
    return nullptr;
}
std::shared_ptr<Entity> Entity::get_entity(int id)
{
    std::cout << "Finding Entity, Total: " << Entity::entities.size() << " Searching: " << std::endl;
    for (int i = 0; i < Entity::entities.size(); i++)
    {
        std::cout << Entity::entities[i]->ID << std::endl;
        if(Entity::entities[i]->ID == id)
        {
            return Entity::entities[i];
        }
    }
    return nullptr;
}
//Virtuals
void Entity::update(float delta){}
void Entity::draw(float delta){} 
void Entity::editor_draw(float delta){}

//Teascript

void teascript_entity_display(TeaState*T)
{
    int len = 0;
    const char* name = tea_check_lstring(T,0,&len);
    Entity::current->display_property(name,NULL,PROPERTY_FLOAT);
    tea_push_null(T);
}
void teascript_entity_self(TeaState*T)
{
    if(Entity::current!=nullptr)
        tea_push_number(T,Entity::current->ID);
    else
        tea_push_null(T);
}
void teascript_entity_find(TeaState*T)
{
    int len;
    const char* name = tea_check_lstring(T,0,&len);
    tea_push_number(T,Entity::get_entity(std::string(name))->ID);
}
void teascript_entity_get_property(TeaState*T)
{
    int entityID = tea_check_number(T,0);
    int len = 0;
    const char* name = tea_check_lstring(T,1,&len);
    std::shared_ptr<Entity> e = Entity::get_entity(entityID);
    if(e==nullptr)
    {
        std::cout << "NULL??!?" << std::endl;
    }
    EntityProperty t = e->get_property(name);
    void* v = t.value;
    if(t.type == PROPERTY_FLOAT)
    {
        tea_push_number(T,*(float *)v);
        return;
    }
    else if(t.type == PROPERTY_INT)
    {
        tea_push_number(T,*(int *)v);
        return;
    }
    else if(t.type == PROPERTY_VECTOR1)
    {
        tea_push_number(T,(*(glm::vec1 *)v).x);
        return;
    }
    else if(t.type == PROPERTY_VECTOR2)
    {
        tea_tools_push_vec2(T,*(glm::vec2 *)v);
        return;
    }
    else if(t.type == PROPERTY_VECTOR3)
    {
        tea_tools_push_vec3(T,*(glm::vec3 *)v);
        return;
    }
    else if(t.type == PROPERTY_VECTOR4)
    {
        tea_tools_push_vec4(T,*(glm::vec4 *)v);
        return;
    }
    tea_push_null(T);
}
void teascript_entity_set_property(TeaState*T)
{
    int entityID = tea_check_number(T,0);
    int len = 0;
    const char* name = tea_check_lstring(T,1,&len);
    if(tea_is_number(T,1))
    {
        float n = tea_check_number(T,1);
        Entity::get_entity(entityID)->set_property(name,PROPERTY_FLOAT,&n);
    }
    else if(tea_is_bool(T,1))
    {
        bool n = tea_check_bool(T,1);
        Entity::get_entity(entityID)->set_property(name,PROPERTY_BOOL,&n);
    }
    else if(tea_is_string(T,1))
    {
        int len = 0;
        std::string n = tea_check_lstring(T,1,&len);
        Entity::get_entity(entityID)->set_property(name,PROPERTY_STRING,&n);
    }
    tea_push_null(T);
}

//Tea module
const TeaModule TeaModule_entity[] = {
    {"display_property",teascript_entity_display},
    {"self",teascript_entity_self},
    {"find",teascript_entity_find},
    {"get_property",teascript_entity_get_property},
    {"set_property",teascript_entity_set_property},
    {NULL,NULL}
};

void TeaModule_add_entity(TeaState* T)
{
    tea_create_module(T,"Entity",TeaModule_entity);
    tea_pop(T,1);
}