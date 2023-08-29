//TODO: Change this to be consistent with other H files
class Viewport : public EditorWindow
{
public:
    GLuint texture;
    ImVec2 window_size;
    Viewport(GLuint texture);
    void draw();
};
#include"viewport.cpp"