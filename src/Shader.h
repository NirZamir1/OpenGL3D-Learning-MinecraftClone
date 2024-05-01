#pragma once
#include <string>
#include <unordered_map>
#include <ext.hpp>
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	const std::string m_FilePath;
	unsigned int m_ProgramID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();
	void Bind() const;// to remain with a simllar look to the vertex buffer and
	void UnBind() const;

	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform3f(const std::string& name, float v0, float v1, float v2);
	void SetUniform1f(const std::string& name, float v);
	void SetUniform1i(const std::string& name, int v);
	void SetUniformMatrix4fv(const std::string& name, glm::mat4 mat);


private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const char* source);
	unsigned int CreateShader(const char* vertextShader, const char* fragmentShader);
	int GetUniformLocation(const std::string& name);
};