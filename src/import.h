#ifndef IMPORT_H
#define IMPORT_H
#include"string"
#include"vector"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class AssetManager
{
public:
    std::vector<std::string> asset_mesh_name;
    std::vector<aiScene*> asset_mesh_value;
    AssetManager();
    void load_model(std::string path, std::string name, unsigned int import_flags);
    void load_audio(std::string path, std::string name);
    void* get_asset(std::string name);
};
#endif