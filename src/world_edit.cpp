#include"world_edit.h"

//Functions
void editor_new_entity(AssetManager*asset_manager,Material* mat,World* world)
{
    if(ImGui::BeginMenu("New Entity"))
    {
        if(ImGui::MenuItem("Cube"))
        {
            std::shared_ptr<MeshRenderer> e = std::make_shared<MeshRenderer>(((aiScene*)asset_manager->get_asset("mesh_cube"))->mMeshes[0],mat,"Cube Mesh");
            world->add_entity(e);
        }
        if(ImGui::MenuItem("Sphere"))
        {
            std::shared_ptr<MeshRenderer> e = std::make_shared<MeshRenderer>(((aiScene*)asset_manager->get_asset("mesh_sphere"))->mMeshes[0],mat,"Sphere Mesh");
            world->add_entity(e);
        }
        if(ImGui::MenuItem("Cylinder"))
        {
            std::shared_ptr<MeshRenderer> e = std::make_shared<MeshRenderer>(((aiScene*)asset_manager->get_asset("mesh_cylinder"))->mMeshes[0],mat,"Cylinder Mesh");
            world->add_entity(e);
        }
        if(ImGui::MenuItem("Torus"))
        {
            std::shared_ptr<MeshRenderer> e = std::make_shared<MeshRenderer>(((aiScene*)asset_manager->get_asset("mesh_torus"))->mMeshes[0],mat,"Torus Mesh");
            world->add_entity(e);
        }
        if(ImGui::MenuItem("Camera"))
        {
           std::shared_ptr<Camera3d> e = std::make_shared<Camera3d>(90.0f,"Camera3d");
            world->add_entity(e);
        }
       
       ImGui::EndMenu();
    }
}