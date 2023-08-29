//Include everything

//Imgui
#include<imgui.h>
#include<backends/imgui_impl_glfw.h>
#include<backends/imgui_impl_opengl3.h>
#include<misc/cpp/imgui_stdlib.h>

#include"editor_styles.h"

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

//TODO: Make game_time into class
double game_time = 0.0;

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
    //Init GLFW
    if (!glfwInit())
    {
        return -1;
    }
    window = OpenWindow(1024, 768, "Pomegranate Editor");

    int w, h;
    glfwGetWindowSize(window,&w,&h); 
    
    //create the Frame Buffer
    make_frame_buffer(512,512);
    //Engine

    //Editor
    Camera3d world_camera = Camera3d(90.0f,"Editor World Camera");

    //TODO: Add world loading
    World world = World();

    //TODO: make asset manager load used assets
    AssetManager asset_manager = AssetManager();
    asset_manager.load_model("../res/models/Cube.fbx", "mesh_cube", aiProcess_Triangulate | aiProcess_FlipUVs);
    asset_manager.load_model("../res/models/Sphere.fbx", "mesh_sphere", aiProcess_Triangulate | aiProcess_FlipUVs);
    asset_manager.load_model("../res/models/Cylinder.fbx", "mesh_cylinder", aiProcess_Triangulate | aiProcess_FlipUVs);
    asset_manager.load_model("../res/models/Torus.fbx", "mesh_torus", aiProcess_Triangulate | aiProcess_FlipUVs);

    //Init basic material TODO: Load materials with asset_manager
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

    //TODO: add delta to GameTime class
    float delta = 0.016f;
    double editor_mouse_x = 0;
    double editor_mouse_y = 0;
    double prev_editor_mouse_x = editor_mouse_x;
    double prev_editor_mouse_y = editor_mouse_y;

    TeaState* T_Main = tea_open();
    //Add modules
    TeaModule_add_debug(T_Main);
    TeaModule_add_input(T_Main);
    TeaModule_add_pomegranate(T_Main);
    
    //Get functions
    tea_set_global(T_Main,"editor_draw");
    tea_push_null(T_Main);

    //Interpret
    tea_interpret(T_Main,"",readFileToString("../res/scripts/main.tea").c_str());

    //Editor loop
    while (!glfwWindowShouldClose(window))
    {
        //Poll
        glfwPollEvents();
        glfwGetCursorPos(window,&editor_mouse_x,&editor_mouse_y);

        //Editor Update TODO: Move to its own script
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
            //TODO: Reimplement pitch
            float yaw = glm::radians((float)editor_mouse_x - (float)prev_editor_mouse_x)*0.5f;
            float pitch = glm::radians((float)editor_mouse_y - (float)prev_editor_mouse_y)*0.5f;
            world_camera.rotation = glm::vec3(0.0f,world_camera.rotation.y + yaw,0.0f);
        }
        prev_editor_mouse_x = editor_mouse_x;
        prev_editor_mouse_y = editor_mouse_y;

        //Render viewport
        glViewport(0, 0, current_framebuffer_width, currrent_framebuffer_height);
        glBindFramebuffer(GL_FRAMEBUFFER,frameBufferData[1]);
        glClearColor(34.0f/255.0f, 35.0f/255.0f, 35.0f/255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Set editor camera as current
        world_camera.set_current();


        //Editor base debug
        debug_begin_frame();
        debug_set_color(glm::vec3(240, 246, 240)/255.0f);
        int grid_size = 1000; //Should probably shrink
        for (int y = -grid_size; y <= grid_size; y++)
        {
            debug_draw_line(glm::vec3(roundf(world_camera.position.x),0.0f,roundf(world_camera.position.z))+glm::vec3(-grid_size,0.0f,0.0f+y),glm::vec3(roundf(world_camera.position.x),0.0f,roundf(world_camera.position.z))+glm::vec3(grid_size,0.0f,0.0f+y));
            debug_draw_line(glm::vec3(roundf(world_camera.position.x),0.0f,roundf(world_camera.position.z))+glm::vec3(0.0f+y,0.0f,-grid_size),glm::vec3(roundf(world_camera.position.x),0.0f,roundf(world_camera.position.z))+glm::vec3(0.0f+y,0.0f,grid_size));
        }
        debug_end_frame();

        //TODO: Implement proper world system
        world.set_current();
        world.draw(INT_MAX);
        
        //Call the T_MAIN editor draw function
        tea_get_global(T_Main,"editor_draw");
        tea_call(T_Main,0);
        
        //TODO: Move editor UI to its own script

        //ImGUI
        glBindFramebuffer(GL_FRAMEBUFFER, 0);   
        glClearColor(0.06f, 0.06f, 0.06f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //New frame
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
    //Close main
    tea_close(T_Main);
    //Delete material programs
    glDeleteProgram(mat.GL_shader_id);
    glDeleteProgram(debug_material.GL_shader_id);
    //Destroy window
    glfwDestroyWindow(window);
    //Terminate
    glfwTerminate();
    return 0;
}