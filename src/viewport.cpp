//Functions
Viewport::Viewport(GLuint texture)
{
    this->texture = texture;
}
void Viewport::update()
{
    
}
void Viewport::draw()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if(ImGui::Begin((std::string("Viewport - WinID") + std::to_string(MyID)).c_str(),&open))
    {
        if(ImGui::IsWindowFocused())
        {
            glfwGetCursorPos(window,&editor_mouse_x,&editor_mouse_y);
            //Editor Update TODO: Move to its own script
            float speed = 10.0f;
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                world_camera.position += glm::vec3(0,0,-1)*glm::quat(world_camera.rotation)*0.016f*speed;
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                world_camera.position += glm::vec3(0,0,1)*glm::quat(world_camera.rotation)*0.016f*speed;
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                world_camera.position += glm::vec3(-1,0,0)*glm::quat(world_camera.rotation)*0.016f*speed;
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                world_camera.position += glm::vec3(1,0,0)*glm::quat(world_camera.rotation)*0.016f*speed;
            }
            if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
            {
                world_camera.position += glm::vec3(0,1,0)*glm::quat(world_camera.rotation)*0.016f*speed;
            }
            if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
            {
                world_camera.position += glm::vec3(0,-1,0)*glm::quat(world_camera.rotation)*0.016f*speed;
            }
            if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
            {  
                //TODO: Reimplement pitch
                float yaw = glm::radians((float)editor_mouse_x - (float)prev_editor_mouse_x)*0.5f;
                float pitch = glm::radians((float)editor_mouse_y - (float)prev_editor_mouse_y)*0.5f;
                world_camera.rotation = glm::vec3(0.0f,world_camera.rotation.y + yaw,0.0f);
            }
            prev_editor_mouse_x = editor_mouse_x;
            prev_editor_mouse_y = editor_mouse_y;
        }
        ImVec2 wsize = ImGui::GetWindowSize();
        ImGui::Image((ImTextureID)texture,wsize,ImVec2(0,1),ImVec2(1,0));
        ImVec2 size = ImGui::GetWindowSize();
        if(window_size.x!=size.x||window_size.y!=size.y)
        {
            window_size = size;
            std::cout << "Size changed: " << size.x << "/" << size.y << std::endl;
            make_frame_buffer((int)size.x,(int)size.y);
            this->texture = frameBufferData[0];
        }
        ImGui::End();
    }
    ImGui::PopStyleVar();
}
Camera3d Viewport::world_camera = Camera3d(90.0f,"Editor World Camera");