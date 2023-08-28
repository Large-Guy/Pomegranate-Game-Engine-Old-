#ifndef WINDOWS_H
#define WINDOWS_H
#include"GLFW/glfw3.h"
#include"../lib/glad/glad.h"
#include"iostream"
extern unsigned int* frameBufferData;
extern int current_framebuffer_width;
extern int currrent_framebuffer_height;
extern GLFWwindow* window;
GLFWwindow* OpenWindow(int width, int height, const char* Name);
void make_frame_buffer(int w, int h);
#endif