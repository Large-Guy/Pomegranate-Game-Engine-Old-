#include"shaders.h"
unsigned int make_module(const std::string& filepath, unsigned int module_type)
{
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while(std::getline(file,line))
    {
        bufferedLines << line << "\n";
    }
    std::string shaderSource = bufferedLines.str();
    const char* shaderSrc = shaderSource.c_str();
    bufferedLines.str("");
    file.close();

    unsigned int shaderMod = glCreateShader(module_type);
    glShaderSource(shaderMod,1,&shaderSrc, NULL);
    glCompileShader(shaderMod);

    int success;
    glGetShaderiv(shaderMod,GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shaderMod,1024,NULL,errorLog);
        std::cout << "Shader module compilation error:" << errorLog << std::endl;
    }
    return shaderMod;
}
unsigned int make_shader(const std::string& vertex_filepath, const std::string& fragment_filepath)
{
    std::vector<unsigned int> modules;
    modules.push_back(make_module(vertex_filepath,GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath,GL_FRAGMENT_SHADER));
    unsigned int shader = glCreateProgram();
    for (unsigned int shaderMod : modules)
    {
        glAttachShader(shader,shaderMod);
    }
    glLinkProgram(shader);

    int success;
    glGetProgramiv(shader,GL_COMPILE_STATUS, &success);
    if(!success)
    {
        char errorLog[1024];
        glGetShaderInfoLog(shader,1024,NULL,errorLog);
        std::cout << "Shader module compilation error:" << errorLog << std::endl;
    }

    for(unsigned int shaderModule : modules)
    {
        glDeleteShader(shaderModule);
    }
    return shader;
}

void set_shader_vector4_value(GLuint shaderProgram, const char* name,glm::vec4 value)
{
    GLint loc = glGetUniformLocation(shaderProgram,name);
    if (loc != -1) {
        glUniform4fv(loc, 1, glm::value_ptr(value));
    }
}
void set_shader_matrix4_value(GLuint shaderProgram, const char* name,glm::mat4 value)
{
    GLint loc = glGetUniformLocation(shaderProgram,name);
    if (loc != -1) {
        glUniformMatrix4fv(loc, 1,false, glm::value_ptr(value));
    }
}
Material::Material(std::string shader_path)
{
    GL_shader_id = make_shader(shader_path + std::string("_vertex.glsl"), shader_path + std::string("_fragment.glsl"));
}
Material::Material():GL_shader_id(0){}