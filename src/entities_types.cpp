#include"entities_types.h"
glm::mat4 Camera3d::create_perspective_matrix(float fov, float aspectRatio, float near, float far) 
{
    return glm::perspective(glm::radians(fov),aspectRatio,near,far);
}
Camera3d::Camera3d(float FOV, std::string name)
{
    this->name = name;
    Camera3d::current = this;
    this->FOV = FOV;
    perspective_matrix_cache = glm::mat4();
    add_property("FOV",&this->FOV,PROPERTY_FLOAT);
}
void Camera3d::set_current()
{
    Camera3d::current = this;
}
glm::mat4 Camera3d::get_perspective_matrix(int w, int h)
{
    return create_perspective_matrix(FOV,(float)w/(float)h,0.01f,500.0f);
}
glm::mat4 Camera3d::get_view_matrix()
{
    glm::vec3 forward = glm::vec3(0, 0, -1.0f)*(glm::quat(rotation));
    glm::vec3 cameraTarget = position + forward;
    return glm::lookAt(position, cameraTarget, glm::vec3(0,1.0f,0));
}
void Camera3d::draw(float delta)
{
    glm::vec3 forward = glm::vec3(0, 0, -1.0f)*glm::quat(rotation);
    debug_begin_frame();
    debug_draw_line(position,position + forward);
    debug_end_frame();
}
Camera3d* Camera3d::current = nullptr;

MeshRenderer::MeshRenderer(aiMesh* mesh, Material* material, std::string name)
{
    this->name = name;
    this->mesh = mesh;
    this->color = Color();
    //Extract verts
    std::vector<float> verts = std::vector<float>();
    std::vector<float> normals = std::vector<float>();
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        verts.push_back(mesh->mVertices[i].x);
        verts.push_back(mesh->mVertices[i].y);
        verts.push_back(mesh->mVertices[i].z);
        normals.push_back(mesh->mNormals[i].x);
        normals.push_back(mesh->mNormals[i].y);
        normals.push_back(mesh->mNormals[i].z);
    }
    std::cout << "Vertex Count: " << verts.size() << std::endl;
    std::cout << "Normal Count: " << normals.size() << std::endl;
    //Extract ind
    std::vector<unsigned int> indie = std::vector<unsigned int>();
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        indie.push_back(mesh->mFaces[i].mIndices[0]);
        indie.push_back(mesh->mFaces[i].mIndices[1]);
        indie.push_back(mesh->mFaces[i].mIndices[2]);
    }
    this->IndicesCount = indie.size();
    this->VerticesCount = verts.size();
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(float), verts.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indie.size() * sizeof(unsigned int), indie.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Normal vectors attribute
    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
    this->material = material;
    add_property("Mesh",&mesh_asset_path,PROPERTY_ASSET);
    add_property("Material",&material_asset_path,PROPERTY_ASSET);
    add_property("Color",&color,PROPERTY_COLOR);
}
void MeshRenderer::draw(float delta)
{
    glUseProgram(material->GL_shader_id);
    glBindAttribLocation(material->GL_shader_id, 0, "aPos");
    glBindAttribLocation(material->GL_shader_id, 1, "aNor");
    glm::mat4 projection = Camera3d::current->get_perspective_matrix(current_framebuffer_width,currrent_framebuffer_height);
    set_shader_matrix4_value(material->GL_shader_id, "Projection", projection);
    set_shader_matrix4_value(material->GL_shader_id, "View", Camera3d::current->get_view_matrix());
    set_shader_matrix4_value(material->GL_shader_id, "Model", get_model_matrix());
    set_shader_vector4_value(material->GL_shader_id, "Color", glm::vec4(color.data[0],color.data[1],color.data[2],color.data[3]));
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawElements(GL_TRIANGLES, IndicesCount, GL_UNSIGNED_INT, 0);
}