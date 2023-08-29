#ifndef EDITOR_WINDOW_H
#define EDITOR_WINDOW_H

class EditorWindow
{
public:
    static int WindowID;
    int MyID;
    bool open;

    EditorWindow();

    virtual void update();
    virtual void draw();
};

#endif