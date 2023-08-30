#include"debug.h"

//Variables
Material debug_material;
std::vector<glm::vec3> debug_line_points;
glm::vec3 debug_color;

//Functions
void teascript_debug_begin_frame(TeaState*T)
{
    debug_line_points.clear();

    tea_push_null(T);
}
void debug_begin_frame()
{
    debug_line_points.clear();
}
void teascript_debug_set_color(TeaState*T)
{
    glm::vec3 c = tea_tools_check_vec3(T,0);

    debug_color = c;

    tea_push_null(T);
}
void debug_set_color(glm::vec3 color)
{
    debug_color = color;
}
void debug_draw_sphere(glm::vec3 a, float r) 
{
    int d = (int)(24 * r); //Detail
    for (int i = 0; i < d; ++i) 
    {
        float angle1 = (float)(i) / d * 6.28319;
        float angle2 = (float)(i + 1) / d * 6.28319;

        float px1 = std::sin(angle1) * r;
        float py1 = std::cos(angle1) * r;

        float px2 = std::sin(angle2) * r;
        float py2 = std::cos(angle2) * r;

        //Draw the 3 spheres
        debug_draw_line({px1 + a.x, a.y, py1 + a.z}, {px2 + a.x, a.y, py2 + a.z});
        debug_draw_line({px1 + a.x, py1 + a.y, a.z}, {px2 + a.x, py2 + a.y, a.z});
        debug_draw_line({a.x, px1 + a.y, py1 + a.z}, {a.x, px2 + a.y, py2 + a.z});
    }
}
void teascript_debug_draw_sphere(TeaState*T) 
{
    glm::vec3 p = tea_tools_check_vec3(T,0);
    double r = tea_check_number(T,1);

    debug_draw_sphere(p,r);

    tea_push_null(T);
}
void teascript_debug_draw_line(TeaState*T)
{
    glm::vec3 a = tea_tools_check_vec3(T,0);
    glm::vec3 b = tea_tools_check_vec3(T,1);

    debug_draw_line(a,b);

    tea_push_null(T);
}
void teascript_debug_draw_point(TeaState*T)
{
    glm::vec3 a = tea_tools_check_vec3(T,0);

    debug_draw_point(a);

    tea_push_null(T);
}
void debug_draw_line(glm::vec3 a, glm::vec3 b)
{
    debug_line_points.push_back(a);
    debug_line_points.push_back(b);
}
void debug_draw_point(glm::vec3 a)
{
    //Push 2 points for point
    debug_line_points.push_back(a);
    debug_line_points.push_back(a);
}
void teascript_debug_end_frame(TeaState*T)
{
    debug_end_frame();
}
void debug_end_frame()
{
    //Setup shader for drawing
    glUseProgram(debug_material.GL_shader_id);
    glm::mat4 projection = Camera3d::current->get_perspective_matrix(current_framebuffer_width,currrent_framebuffer_height);
    set_shader_matrix4_value(debug_material.GL_shader_id, "Projection", projection);
    set_shader_matrix4_value(debug_material.GL_shader_id, "View", Camera3d::current->get_view_matrix());
    set_shader_matrix4_value(debug_material.GL_shader_id, "Model", glm::mat4(1.0f));
    set_shader_vector4_value(debug_material.GL_shader_id, "Color", glm::vec4(debug_color.x,debug_color.y,debug_color.z,1.0f));
    
    //Draw lines
    glLineWidth(1);
    glBegin(GL_LINES);
    for (size_t i = 0; i < debug_line_points.size(); i += 2)
    {
        if(debug_line_points[i]!=debug_line_points[i+1]) //Check if not at same position, else draw point later
        {
            glVertex3f(debug_line_points[i].x,debug_line_points[i].y,debug_line_points[i].z);
            glVertex3f(debug_line_points[i+1].x,debug_line_points[i+1].y,debug_line_points[i+1].z);
        }
    }
    glEnd();
    
    //Draw points
    glUseProgram(debug_material.GL_shader_id); //Don't think i need this (not able to debug at the moment)
    glPointSize(10);
    glBegin(GL_POINTS);
    for (size_t i = 0; i < debug_line_points.size(); i += 2)
    {
        if(debug_line_points[i]==debug_line_points[i+1])
        {
            glVertex3f(debug_line_points[i].x,debug_line_points[i].y,debug_line_points[i].z);
        }
    }
    glEnd();
}
//Tea module
const TeaModule debug_module[] = 
{
    {"begin",teascript_debug_begin_frame},
    {"end",teascript_debug_end_frame},
    {"line",teascript_debug_draw_line},
    {"sphere",teascript_debug_draw_sphere},
    {"point",teascript_debug_draw_point},
    {"color",teascript_debug_set_color},
    {"clear",Console::teascript_clear},
    {"print",Console::teascript_print},
    {NULL,NULL}
};

void TeaModule_add_debug(TeaState* T)
{
    tea_create_module(T,"debug",debug_module);
    tea_pop(T,1); //Pop the module object
}