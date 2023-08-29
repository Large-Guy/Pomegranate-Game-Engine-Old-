#ifndef ENTITIES_TYPES
#define ENTITIES_TYPES
#include"entity.h"
#include"vector"
#include"string"
#include"glm.hpp"
#include"ext.hpp"
#include "../lib/glad/glad.h"
#include"GLFW/glfw3.h"
#include"material.h"
#include"color.h"
#include"scene.h"
#include"debug.h"
#include"iostream"
#include"shaders.h"
#include"windows.h"

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
    void editor_draw(float delta);
};

class MeshRenderer : public Entity
{
public:
    std::string mesh_asset_path;
    std::string material_asset_path;
    aiMesh* mesh;
    Material* material;
    Color color;
    unsigned int EBO;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int VerticesCount;
    unsigned int IndicesCount;
    MeshRenderer(aiMesh* mesh, Material* material, std::string name);
    void draw(float delta);
};

#endif