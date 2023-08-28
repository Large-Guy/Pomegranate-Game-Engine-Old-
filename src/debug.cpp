#include"debug.h"
Material debug_material;
std::vector<glm::vec3> debug_line_points;
glm::vec3 debug_color;
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
    double x1 = tea_check_number(T,0);
    double y1 = tea_check_number(T,1);
    double z1 = tea_check_number(T,2);
    debug_color = glm::vec3(x1,y1,z1);
    tea_push_null(T);
}
void debug_set_color(glm::vec3 color)
{
    debug_color = color;
}
void debug_draw_sphere(float x, float y, float z, float r) 
{
    int d = static_cast<int>(24 * r);
    for (int i = 0; i < d; ++i) {
        float angle1 = static_cast<float>(i) / d * 6.28319;
        float angle2 = static_cast<float>(i + 1) / d * 6.28319;

        float px1 = std::sin(angle1) * r;
        float py1 = std::cos(angle1) * r;

        float px2 = std::sin(angle2) * r;
        float py2 = std::cos(angle2) * r;

        debug_draw_line({px1 + x, y, py1 + z}, {px2 + x, y, py2 + z});
        debug_draw_line({px1 + x, py1 + y, z}, {px2 + x, py2 + y, z});
        debug_draw_line({x, px1 + y, py1 + z}, {x, px2 + y, py2 + z});
    }
}
void teascript_debug_draw_sphere(TeaState*T) 
{
    glm::vec3 p = tea_tools_check_vec3(T,0);
    double r = tea_check_number(T,1);
    int d = static_cast<int>(24 * r);
    for (int i = 0; i < d; ++i) {
        float angle1 = static_cast<float>(i) / d * 6.28319;
        float angle2 = static_cast<float>(i + 1) / d * 6.28319;

        float px1 = std::sin(angle1) * r;
        float py1 = std::cos(angle1) * r;

        float px2 = std::sin(angle2) * r;
        float py2 = std::cos(angle2) * r;

        debug_draw_line({px1 + p.x, p.y, py1 + p.z}, {px2 + p.x, p.y, py2 + p.z});
        debug_draw_line({px1 + p.x, py1 + p.y, p.z}, {px2 + p.x, py2 + p.y, p.z});
        debug_draw_line({p.x, px1 + p.y, py1 + p.z}, {p.x, px2 + p.y, py2 + p.z});
    }
    tea_push_null(T);
}
void teascript_debug_draw_line(TeaState*T)
{
    glm::vec3 a = tea_tools_check_vec3(T,0);
    glm::vec3 b = tea_tools_check_vec3(T,1);
    debug_line_points.push_back(a);
    debug_line_points.push_back(b);
    tea_push_null(T);
}
void teascript_debug_draw_point(TeaState*T)
{
    glm::vec3 a = tea_tools_check_vec3(T,0);
    debug_line_points.push_back(a);
    debug_line_points.push_back(a);
    tea_push_null(T);
}
void debug_draw_line(glm::vec3 a, glm::vec3 b)
{
    debug_line_points.push_back(a);
    debug_line_points.push_back(b);
}
void debug_draw_point(glm::vec3 a)
{
    debug_line_points.push_back(a);
    debug_line_points.push_back(a);
}
void teascript_debug_end_frame(TeaState*T)
{
    glUseProgram(debug_material.GL_shader_id);
    glm::mat4 projection = Camera3d::current->get_perspective_matrix(current_framebuffer_width,currrent_framebuffer_height);
    set_shader_matrix4_value(debug_material.GL_shader_id, "Projection", projection);
    set_shader_matrix4_value(debug_material.GL_shader_id, "View", Camera3d::current->get_view_matrix());
    set_shader_matrix4_value(debug_material.GL_shader_id, "Model", glm::mat4(1.0f));
    set_shader_vector4_value(debug_material.GL_shader_id, "Color", glm::vec4(debug_color.x,debug_color.y,debug_color.z,1.0f));
    glLineWidth(1);
    glBegin(GL_LINES);
    for (size_t i = 0; i < debug_line_points.size(); i += 2)
    {
        if(debug_line_points[i]!=debug_line_points[i+1])
        {
            glVertex3f(debug_line_points[i].x,debug_line_points[i].y,debug_line_points[i].z);
            glVertex3f(debug_line_points[i+1].x,debug_line_points[i+1].y,debug_line_points[i+1].z);
        }
    }
    glEnd();
    glUseProgram(debug_material.GL_shader_id);
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
void debug_end_frame()
{
    glUseProgram(debug_material.GL_shader_id);
    glm::mat4 projection = Camera3d::current->get_perspective_matrix(current_framebuffer_width,currrent_framebuffer_height);
    set_shader_matrix4_value(debug_material.GL_shader_id, "Projection", projection);
    set_shader_matrix4_value(debug_material.GL_shader_id, "View", Camera3d::current->get_view_matrix());
    set_shader_matrix4_value(debug_material.GL_shader_id, "Model", glm::mat4(1.0f));
    set_shader_vector4_value(debug_material.GL_shader_id, "Color", glm::vec4(debug_color.x,debug_color.y,debug_color.z,1.0f));
    glLineWidth(1);
    glBegin(GL_LINES);
    for (size_t i = 0; i < debug_line_points.size(); i += 2)
    {
        if(debug_line_points[i]!=debug_line_points[i+1])
        {
            glVertex3f(debug_line_points[i].x,debug_line_points[i].y,debug_line_points[i].z);
            glVertex3f(debug_line_points[i+1].x,debug_line_points[i+1].y,debug_line_points[i+1].z);
        }
    }
    glEnd();
    glUseProgram(debug_material.GL_shader_id);
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
    tea_pop(T,1);
}