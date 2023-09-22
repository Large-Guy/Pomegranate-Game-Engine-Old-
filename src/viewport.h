//TODO: Change this to be consistent with other H files
class Viewport : public EditorWindow
{
public:
    GLuint texture;
    ImVec2 window_size;
    double editor_mouse_x = 0;
    double editor_mouse_y = 0;
    double prev_editor_mouse_x = editor_mouse_x;
    double prev_editor_mouse_y = editor_mouse_y;
    static Camera3d world_camera;
    Viewport(GLuint texture);
    void draw();
    void update();
};

#include "viewport.cpp"