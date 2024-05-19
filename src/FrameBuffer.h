#include"Renderer.h"
#include"Shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#pragma once
class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(int width, int height, const char* shaderPath);
	~FrameBuffer();
	void UpdateSize(int width, int height);
	void Bind();
	void bindDeafult();
private:
	Shader* m_fbShader;
	unsigned int m_RendererID;
	unsigned int m_Rbo;
	unsigned int m_Texture;
};