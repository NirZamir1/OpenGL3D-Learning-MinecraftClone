#pragma once
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
class VertexArray
{
private:
	unsigned int m_RendererID;
	unsigned int layoutOfSet;
public:
	VertexArray();
	~VertexArray();
	void Bind() const;
	void UnBind() const;
	int getlayoutOfSet() const;
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};