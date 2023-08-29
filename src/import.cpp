#include"import.h"

AssetManager::AssetManager()
{
    asset_mesh_name = std::vector<std::string>();
    asset_mesh_value = std::vector<aiScene*>();
}
void AssetManager::load_model(std::string path, std::string name, unsigned int import_flags)
{
    Assimp::Importer importer;
    asset_mesh_name.push_back(name);
    asset_mesh_value.push_back((aiScene*)importer.ReadFile(path, import_flags));
}
void AssetManager::load_audio(std::string path, std::string name)
{

}
void* AssetManager::get_asset(std::string name)
{
    for (size_t i = 0; i < asset_mesh_name.size(); i++)
    {
        if(name == asset_mesh_name[i])
        {
            return (void*)asset_mesh_value[i];
        }
    }
    return nullptr;
}