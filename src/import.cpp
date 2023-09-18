#include"import.h"

AssetManager::AssetManager()
{
    asset_mesh_name = std::vector<std::string>();
    asset_mesh_value = std::vector<const aiScene*>();
    asset_model_importers = std::vector<std::shared_ptr<Assimp::Importer>>();
}
void AssetManager::load_model(std::string path, std::string name, unsigned int import_flags)
{
    std::shared_ptr<Assimp::Importer> importer = std::make_shared<Assimp::Importer>();
    asset_model_importers.push_back(importer);
    asset_mesh_name.push_back(name);
    const aiScene* sc = asset_model_importers[asset_model_importers.size()-1]->ReadFile(path, import_flags);
    asset_mesh_value.push_back(sc);
}
void AssetManager::load_audio(std::string path, std::string name)
{

}
const void* AssetManager::get_asset(std::string name)
{
    for (size_t i = 0; i < asset_mesh_name.size(); i++)
    {
        if(name == asset_mesh_name[i])
        {
            return (const void*)asset_mesh_value[i];
        }
    }
    return nullptr;
}