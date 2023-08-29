#ifndef INSPECTOR_H
#define INSPECTOR_H

#include"editor_window.h"
#include"glm.hpp"
#include"ext.hpp"
#include"string"
#include"color.h"
#include"hierarchy.h"
#include"imgui.h"

class Inspector : public EditorWindow
{
public:
    int inspector_id;

    Inspector();
    void display_vector4(glm::vec4*v);
    void display_vector3(glm::vec3*v);
    void display_vector2(glm::vec2*v);
    void display_vector1(glm::vec1*v);
    void display_float(float*v);
    void display_string(std::string*v);
    void display_asset(std::string*v);
    void display_color(Color* v);
    void draw() override;
};

#endif