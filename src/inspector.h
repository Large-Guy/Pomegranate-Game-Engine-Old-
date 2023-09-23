#pragma once

#include <string>

#include <imgui.h>
#include"imfilebrowser.h"

#include "glm.hpp"
#include "ext.hpp"

#include "editor_window.h"
#include "color.h"
#include "hierarchy.h"

class Inspector : public EditorWindow
{
private:
    ImGui::FileBrowser fileDialog;
    std::string* fileBrowserString;
public:
    int inspector_id;

    Inspector();
    void display_vector4(glm::vec4*v);
    void display_vector3(glm::vec3*v);
    void display_vector2(glm::vec2*v);
    void display_vector1(glm::vec1*v);
    void display_float(float*v);
    void display_string(std::string*v);
    void display_multiline(std::string*v);
    void display_asset(std::string*v);
    void display_script(std::string*v);
    void display_color(glm::vec4*v);
    void display_bool(bool*v);
    void draw() override;
};