#pragma once

#include <iostream>

#include "GLFW/glfw3.h"
#include "../lib/glad/glad.h"

//Variables
extern unsigned int* frameBufferData;
extern int current_framebuffer_width;
extern int currrent_framebuffer_height;
extern GLFWwindow* window;

//Functions
GLFWwindow* OpenWindow(int width, int height, const char* Name);
void make_frame_buffer(int w, int h);