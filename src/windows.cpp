#include"windows.h"
unsigned int* frameBufferData;
int current_framebuffer_width;
int currrent_framebuffer_height;
GLFWwindow* window;
GLFWwindow* OpenWindow(int width, int height, const char* Name)
{
    GLFWwindow* window;
    window = glfwCreateWindow(width,height,Name, NULL, NULL);
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Couldn't load openGL" << std::endl;
        glfwTerminate();
        return NULL;
    }
    return window;
}
void make_frame_buffer(int w, int h)
{
    current_framebuffer_width = w;
    currrent_framebuffer_height = h;
    unsigned int FBO;
    glGenFramebuffers(1,&FBO);
    glBindFramebuffer(GL_FRAMEBUFFER,FBO);


    unsigned int framebufferTexture;
    glGenTextures(1,&framebufferTexture);
    glBindTexture(GL_TEXTURE_2D, framebufferTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w,h,0,GL_RGB,GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D, framebufferTexture,0);


    auto fboStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(fboStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Frame buffer error: " << fboStatus << std::endl;
    }

    //Depth sorting
    unsigned int depthBuffer;
    glEnable(GL_DEPTH_TEST);
    // Allocate memory for the depth buffer
    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, w, h);

    // Attach the depth buffer to the framebuffer
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    delete[] frameBufferData;
    frameBufferData = new unsigned int[2];
    frameBufferData[0] = framebufferTexture;
    frameBufferData[1] = FBO;
}