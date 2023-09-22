#pragma once

#include <string>
#include <memory>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <misc/cpp/imgui_stdlib.h>

#include "entities_types.h"
#include "world.h"
#include "import.h"
#include "material.h"

//Functions
void editor_new_camera();
void editor_new_mesh(std::string mesh_name);
void editor_new_entity(AssetManager*asset_manager,Material* mat,World* world);