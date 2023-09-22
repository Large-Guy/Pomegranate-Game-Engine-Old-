#pragma once

#include <vector>

#include "../lib/glad/glad.h"
#include "GLFW/glfw3.h"

#include "glm.hpp"
#include "ext.hpp"
#include "tea.hpp"

#include "shaders.h"
#include "entities_types.h"
#include "windows.h"
#include "console.h"
#include "tea_tools.h"

//Variables
extern Material debug_material;
extern std::vector<glm::vec3> debug_line_points;
extern glm::vec3 debug_color;
extern const TeaModule debug_module[];

//Functions
void debug_begin_frame_tea(TeaState*T);
void debug_begin_frame();
void debug_set_color_tea(TeaState*T);
void debug_set_color(glm::vec3 color);
void debug_draw_line_tea(TeaState*T);
void debug_draw_line(glm::vec3 a, glm::vec3 b);
void debug_end_frame_tea(TeaState*T);
void debug_end_frame();
void TeaModule_add_debug(TeaState* T);
void debug_draw_point_tea(TeaState*T);
void debug_draw_point(glm::vec3 a);