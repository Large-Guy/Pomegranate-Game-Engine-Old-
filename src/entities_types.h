#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

#include "../lib/glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm.hpp"
#include "ext.hpp"

#include"tea.hpp"
#include"tea_tools.h"

#include "entity.h"
#include "material.h"
#include "input.h"
#include "pomegranate_lib.h"
#include "color.h"
#include "scene.h"
#include "debug.h"
#include "shaders.h"
#include "windows.h"
#include "gtx/quaternion.hpp"

class Camera3d : public Entity
{
private:
    glm::mat4 perspective_matrix_cache;
    glm::mat4 create_perspective_matrix(float fov, float aspectRatio, float near, float far);
public:
    float FOV;
    static Camera3d* current;
    Camera3d(float FOV, std::string name);
    void set_current();
    glm::mat4 get_perspective_matrix(int w, int h);
    glm::mat4 get_view_matrix();
    void draw(float delta);
};

class MeshRenderer : public Entity
{
public:
    std::string mesh_asset_path;
    std::string material_asset_path;
    aiMesh* mesh;
    Material* material;
    glm::vec4 color;
    unsigned int EBO;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int VerticesCount;
    unsigned int IndicesCount;
    MeshRenderer(aiMesh* mesh, Material* material, std::string name);
    void draw(float delta);
};

class ScriptableEntity: public Entity
{
private:
    std::string lst_src_script;
    bool opened;
public:
    std::string script_src;
    std::string script_string;
    TeaState* my_script_state;
    ScriptableEntity(std::string name,std::string script_src, std::string script_string);
    void update(float delta);
    void draw(float delta);
    void editor_draw(float delta);
    void editor_update(float delta);
    ~ScriptableEntity();
};