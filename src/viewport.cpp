Viewport::Viewport(GLuint texture)
{
    this->texture = texture;
}
void Viewport::draw()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin((std::string("Viewport - WinID") + std::to_string(MyID)).c_str(),&open);
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
    ImGui::PopStyleVar();
}