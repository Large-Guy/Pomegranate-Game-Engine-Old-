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
    void DisplayVector4(glm::vec4*v);
    void DisplayVector3(glm::vec3*v);
    void DisplayVector2(glm::vec2*v);
    void DisplayVector1(glm::vec1*v);
    void DisplayFloat(float*v);
    void DisplayString(std::string*v);
    void DisplayAsset(std::string*v);
    void DisplayColor(Color* v);
    void draw() override;
};
#endif