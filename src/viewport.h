class Viewport : public EditorWindow
{
public:
    GLuint texture;
    ImVec2 window_size;
    Viewport(GLuint texture);
    void draw();
};
#include"viewport.cpp"