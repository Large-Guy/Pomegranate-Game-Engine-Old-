#include"world_edit.h"


std::string removeToScripts(const std::string& filePath)
{
    // Find the position of "scripts/" in the file path
    size_t pos = filePath.find("scripts/");

    // Check if "scripts/" was found
    if (pos != std::string::npos)
    {
        // Return the substring starting from the position after "scripts/"
        return filePath.substr(pos + 8); // 8 is the length of "scripts/"
    }

    // If "scripts/" was not found, return the original path
    return filePath;
}
std::vector<std::string> getFilesOfTypeInFolder(const std::string& folderPath, const std::string& fileType) 
{
    std::vector<std::string> filePaths;
    
    try 
    {
        for (const std::filesystem::directory_entry& entry : std::filesystem::recursive_directory_iterator(folderPath)) 
        {
            if (entry.is_regular_file() && entry.path().extension() == fileType) 
            {
                filePaths.push_back(removeToScripts(entry.path().string()));
            }
        }
    } 
    catch (const std::filesystem::filesystem_error& ex) 
    {
        std::cerr << "Error accessing folder: " << ex.what() << std::endl;
    }
    
    return filePaths;
}
std::vector<std::string> splitAndCapitalize(const std::string& input) 
{
    std::vector<std::string> result;
    std::string current;

    for (char c : input) {
        if (c == '/') {
            if (!current.empty()) {
                // Capitalize the first letter of the current string
                current[0] = std::toupper(current[0]);
                result.push_back(current);
                current.clear();
            }
        } else {
            current += c;
        }
    }

    if (!current.empty()) {
        // Capitalize the first letter of the last string
        current[0] = std::toupper(current[0]);
        result.push_back(current);
    }

    return result;
}

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
        if(ImGui::BeginMenu("Scriptable Entity"))
        {
            if(ImGui::MenuItem("Empty"))
            {
               std::shared_ptr<ScriptableEntity> e = std::make_shared<ScriptableEntity>("Script","","");
                world->add_entity(e);
            }
            //Get custom
            std::vector<std::string> types = getFilesOfTypeInFolder("res/scripts",".tea");
            
            for (int i = 0; i < types.size(); i++)
            {
                std::vector<std::string> parts = splitAndCapitalize(types[i]);
                int count = 0;
                for (int i = 0; i < parts.size()-1; i++)
                {
                    if(!ImGui::BeginMenu(parts[i].c_str()))
                        break;
                    count++;
                }
                if(count == parts.size()-1)
                {
                    const char* t = parts[parts.size()-1].c_str();
                    if(ImGui::MenuItem(t))
                    {
                       std::shared_ptr<ScriptableEntity> e = std::make_shared<ScriptableEntity>("Script",types[i],"");
                        world->add_entity(e);
                    }
                }
                    
                for (int i = 0; i < count; i++)
                {
                    ImGui::EndMenu();
                }
            }
            
            
            ImGui::EndMenu();
        }
       
       ImGui::EndMenu();
    }
}