//Imgui
#include<imgui.h>
#include<backends/imgui_impl_glfw.h>
#include<backends/imgui_impl_opengl3.h>
#include<misc/cpp/imgui_stdlib.h>

#include <iostream>
#include "../lib/glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include<tuple>
#include <map>
#include<memory>


#include "glm.hpp"
#include "ext.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//Engine stuff
#include "import.h"
#include "shaders.h"
#include "windows.h"
#include"color.h"
#include"input.h"

//teascript
#include"tea.hpp"
#include"tea_tools.h"
#include"pomegranate_lib.h"

//Entities
#include "entity.h"
//Debug
#include "entities_types.h"
#include"debug.h"

//Worlds
#include "world.h"

//Editor windows
#include"editor_window.h"
#include"hierarchy.h"
#include"inspector.h"
#include"viewport.h"
#include"console.h"
#include"world_edit.h"

double game_time = 0.0;

void printMat4(glm::mat4 matrix)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void dark_editor_style()
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_Text]                   = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    style.Colors[ImGuiCol_WindowBg]               = ImVec4(0.06f, 0.06f, 0.06f, 1.0f);
    style.Colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
    style.Colors[ImGuiCol_Border]                 = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    style.Colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_FrameBg]                = ImVec4(0.44f, 0.44f, 0.44f, 0.60f);
    style.Colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.57f, 0.57f, 0.57f, 0.70f);
    style.Colors[ImGuiCol_FrameBgActive]          = ImVec4(0.76f, 0.76f, 0.76f, 0.80f);
    style.Colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
    style.Colors[ImGuiCol_TitleBgActive]          = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.60f);
    style.Colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
    style.Colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    style.Colors[ImGuiCol_CheckMark]              = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
    style.Colors[ImGuiCol_SliderGrab]             = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
    style.Colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
    style.Colors[ImGuiCol_Button]                 = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
    style.Colors[ImGuiCol_ButtonHovered]          = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
    style.Colors[ImGuiCol_ButtonActive]           = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
    style.Colors[ImGuiCol_Header]                 = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
    style.Colors[ImGuiCol_HeaderHovered]          = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
    style.Colors[ImGuiCol_HeaderActive]           = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
    style.Colors[ImGuiCol_Separator]              = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
    style.Colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
    style.Colors[ImGuiCol_SeparatorActive]        = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
    style.Colors[ImGuiCol_ResizeGrip]             = ImVec4(0.13f, 0.75f, 0.55f, 0.40f);
    style.Colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.13f, 0.75f, 0.75f, 0.60f);
    style.Colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
    style.Colors[ImGuiCol_Tab]                    = ImVec4(0.13f, 0.75f, 0.55f, 0.80f);
    style.Colors[ImGuiCol_TabHovered]             = ImVec4(0.13f, 0.75f, 0.75f, 0.80f);
    style.Colors[ImGuiCol_TabActive]              = ImVec4(0.13f, 0.75f, 1.00f, 0.80f);
    style.Colors[ImGuiCol_TabUnfocused]           = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
    style.Colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.36f, 0.36f, 0.36f, 0.54f);
    style.Colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    style.Colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    style.Colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    style.Colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    style.Colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.07f);
    style.Colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    style.Colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    style.Colors[ImGuiCol_NavHighlight]           = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style.Colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    style.Colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    style.Colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
}

std::string readFileToString(const std::string& file_path) 
{
    std::ifstream input_file(file_path);

    if (!input_file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return ""; // Return an empty string to indicate an error
    }

    std::string file_contents(
        (std::istreambuf_iterator<char>(input_file)),
        (std::istreambuf_iterator<char>())
    );

    input_file.close();

    return file_contents;
}

int main(int, char **)
{

    if (!glfwInit())
    {
        return -1;
    }
    window = OpenWindow(1024, 768, "Pomegranate Editor");

    int w, h;
    glfwGetWindowSize(window,&w,&h); 
    
    //Frame Buffer
    make_frame_buffer(512,512);
    //Init engine stuff

    Camera3d world_camera = Camera3d(90.0f,"Editor World Camera");

    World world = World();

    AssetManager asset_manager = AssetManager();
    asset_manager.load_model("../res/models/Cube.fbx", "mesh_cube", aiProcess_Triangulate | aiProcess_FlipUVs);
    asset_manager.load_model("../res/models/Sphere.fbx", "mesh_sphere", aiProcess_Triangulate | aiProcess_FlipUVs);
    asset_manager.load_model("../res/models/Cylinder.fbx", "mesh_cylinder", aiProcess_Triangulate | aiProcess_FlipUVs);
    asset_manager.load_model("../res/models/Torus.fbx", "mesh_torus", aiProcess_Triangulate | aiProcess_FlipUVs);

    Material mat = Material("../src/shaders/basic");
    debug_material = Material("../src/shaders/debug");

    //Windows
    std::vector<std::shared_ptr<EditorWindow>> Windows = std::vector<std::shared_ptr<EditorWindow>>();

    //Create basic editor windows
    Windows.push_back(std::make_shared<Viewport>(frameBufferData[0]));
    Windows.push_back(std::make_shared<Hierarchy>());
    Windows.push_back(std::make_shared<Inspector>());
    Windows.push_back(std::make_shared<Console>());
    
    //Editor entities
    std::vector<std::tuple<std::string,const Entity&>> EntityTypes = std::vector<std::tuple<std::string,const Entity&>>();
    
    //ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigWindowsMoveFromTitleBarOnly = true;
    dark_editor_style();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330");

    float delta = 0.016f;
    double editor_mouse_x = 0;
    double editor_mouse_y = 0;
    double prev_editor_mouse_x = editor_mouse_x;
    double prev_editor_mouse_y = editor_mouse_y;

    //TeaState* T_Pomegranate = tea_open();
    //tea_interpret(T_Pomegranate,"",readFileToString("../res/scripts/pomegranate.tea").c_str());
    TeaState* T_Main = tea_open();
    TeaModule_add_debug(T_Main);
    TeaModule_add_input(T_Main);
    TeaModule_add_pomegranate(T_Main);
    tea_set_global(T_Main,"editor_draw");
    tea_push_null(T_Main);
    
    tea_interpret(T_Main,"",readFileToString("../res/scripts/main.tea").c_str());
    while (!glfwWindowShouldClose(window))
    {
        //Poll
        glfwPollEvents();
        glfwGetCursorPos(window,&editor_mouse_x,&editor_mouse_y);
        //Editor Update
        float speed = 3.0f;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            world_camera.position += glm::vec3(0,0,-1)*glm::quat(world_camera.rotation)*delta*speed;
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            world_camera.position += glm::vec3(0,0,1)*glm::quat(world_camera.rotation)*delta*speed;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            world_camera.position += glm::vec3(-1,0,0)*glm::quat(world_camera.rotation)*delta*speed;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            world_camera.position += glm::vec3(1,0,0)*glm::quat(world_camera.rotation)*delta*speed;
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            world_camera.position += glm::vec3(0,1,0)*glm::quat(world_camera.rotation)*delta*speed;
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            world_camera.position += glm::vec3(0,-1,0)*glm::quat(world_camera.rotation)*delta*speed;
        }
        if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        {
            float yaw = glm::radians((float)editor_mouse_x - (float)prev_editor_mouse_x)*0.5f;
            float pitch = glm::radians((float)editor_mouse_y - (float)prev_editor_mouse_y)*0.5f;

            

            world_camera.rotation = glm::vec3(0.0f,world_camera.rotation.y + yaw,0.0f);
        }
        prev_editor_mouse_x = editor_mouse_x;
        prev_editor_mouse_y = editor_mouse_y;
        //Render
        glViewport(0, 0, current_framebuffer_width, currrent_framebuffer_height);
        glBindFramebuffer(GL_FRAMEBUFFER,frameBufferData[1]);
        glClearColor(34.0f/255.0f, 35.0f/255.0f, 35.0f/255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Editor debug
        debug_begin_frame();
        debug_set_color(glm::vec3(240, 246, 240)/255.0f);
        int grid_size = 1000;
        for (int y = -grid_size; y <= grid_size; y++)
        {
            debug_draw_line(glm::vec3(roundf(world_camera.position.x),0.0f,roundf(world_camera.position.z))+glm::vec3(-grid_size,0.0f,0.0f+y),glm::vec3(roundf(world_camera.position.x),0.0f,roundf(world_camera.position.z))+glm::vec3(grid_size,0.0f,0.0f+y));
            debug_draw_line(glm::vec3(roundf(world_camera.position.x),0.0f,roundf(world_camera.position.z))+glm::vec3(0.0f+y,0.0f,-grid_size),glm::vec3(roundf(world_camera.position.x),0.0f,roundf(world_camera.position.z))+glm::vec3(0.0f+y,0.0f,grid_size));
        }
        debug_end_frame();
        world_camera.set_current();
        world.set_current();
        world.draw(INT_MAX);
        
        tea_get_global(T_Main,"editor_draw");
        tea_call(T_Main,0);
        
        //ImGUI
        glBindFramebuffer(GL_FRAMEBUFFER, 0);   
        glClearColor(0.06f, 0.06f, 0.06f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //Editor UI
        for (long unsigned int i = 0; i < Windows.size(); i++)
        {
            Windows[i]->draw();
            if(Windows[i]->open == false)
            {
                Windows.erase(Windows.begin() + i);
                i--;
            }
        }

        if(ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::BeginMenu("New"))
                {
                    if(ImGui::MenuItem("New World"))
                    {
                       std::cout << "TODO: Implment worlds" << std::endl;
                    }
                    editor_new_entity(&asset_manager,&mat,World::current);
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Run"))
                {
                    if(ImGui::MenuItem("Debug"))
                    {
                       std::cout << "TODO: Implment debug" << std::endl;
                    }
                    if(ImGui::MenuItem("Release"))
                    {
                       std::cout << "TODO: Implment release" << std::endl;
                    }
                    if(ImGui::MenuItem("Export"))
                    {
                       std::cout << "TODO: Implment export" << std::endl;
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
          if (ImGui::BeginMenu("Window"))
          {
             if(ImGui::MenuItem("Viewport"))
             {
                std::shared_ptr<Viewport> win = std::make_shared<Viewport>(frameBufferData[0]);
                Windows.push_back(win);
             }
             if(ImGui::MenuItem("Hierarchy"))
             {
                std::shared_ptr<Hierarchy> win = std::make_shared<Hierarchy>();
                Windows.push_back(win);
             }
             if(ImGui::MenuItem("Inspector"))
             {
                std::shared_ptr<Inspector> win = std::make_shared<Inspector>();
                Windows.push_back(win);
             }
             if(ImGui::MenuItem("Console"))
             {
                std::shared_ptr<Console> win = std::make_shared<Console>();
                Windows.push_back(win);
             }
             ImGui::EndMenu();
           }

           ImGui::EndMainMenuBar();
        }

        //Render ImGUI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        //Swap buffers, poll events, game time, etc
        glfwSwapBuffers(window);
        game_time += 0.02;
    }
    tea_close(T_Main);
    //tea_close(T_Pomegranate);
    glDeleteProgram(mat.GL_shader_id);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}