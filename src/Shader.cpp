#include "Shader.h"
#include<iostream>
#include<fstream>
#include <sstream>
#include "Renderer.h"
#include<unordered_map>
Shader::Shader(const std::string& filepath):
    m_ProgramID(0), m_FilePath(filepath)
{
    auto shaders = ParseShader(filepath);
    m_ProgramID = CreateShader(shaders.VertexSource.c_str(), shaders.FragmentSource.c_str());
}

Shader::~Shader()
{
    glDeleteProgram(m_ProgramID);
}

void Shader::Bind() const
{
    glUseProgram(m_ProgramID);
}

void Shader::UnBind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}
void Shader::SetUniform4f(const std::string& name, glm::vec4 vec)
{
    glUniform4f(GetUniformLocation(name), vec[0],vec[1],vec[2],vec[3]);
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}
void Shader::SetUniform3f(const std::string& name, glm::vec3 vec)
{
    glUniform3f(GetUniformLocation(name), vec[0], vec[1], vec[2]);
}
void Shader::SetUniform1i(const std::string& name, int v)
{
    glUniform1i(GetUniformLocation(name), v);
}
void Shader::SetUniform1f(const std::string& name, float v)
{
    glUniform1f(GetUniformLocation(name), v);
}
void Shader::SetUniformMatrix4fv(const std::string& name, glm::mat4 mat)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

unsigned int Shader::CreateShader(const char* vertextShader, const char* fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertextShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    int isLinked;

    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE)
    {
        int length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char* log = (char*)alloca(length);
        glGetProgramInfoLog(program, 1024, 0, log);
        std::cout << "There was an error while linking. \n" << log << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Program Linked Succesfuly!" << std::endl;
    }
    return program;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);
    enum  class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (std::getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = ShaderType::VERTEX;
            }
            else if (line.find("shader") != std::string::npos)
            {
                type = ShaderType::FRAGMENT;
            }
        }
        else
        {
            if (type != ShaderType::NONE)
                ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };
}
unsigned int Shader::CompileShader(unsigned int type, const char* source)
{
    unsigned int id = glCreateShader(type);
    glShaderSource(id, 1,&source, 0);
    glCompileShader(id);

    //error checking
    int isGood;
    glGetShaderiv(id, GL_COMPILE_STATUS, &isGood);
    if (isGood == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* log = (char*)alloca(length);
        glGetShaderInfoLog(id, 1024, 0, log);
        std::cout << "Error in Compilation" << "\n" << log << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Shader Compiled Succesfuly!" << std::endl;
    }

    return id;
}
 int Shader::GetUniformLocation(const std::string& name) 
{ 
    int location;
    if (m_UniformLocationCache.count(name) != 0)
        return m_UniformLocationCache[name];
    else
    {
        location = glGetUniformLocation(m_ProgramID, name.c_str());
        m_UniformLocationCache[name] = location;
    }
   if (location == -1)
       std::cout << "Warning, shader:" << name << " does not exist!" << std::endl;
   return location;
}
