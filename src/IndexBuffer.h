#pragma once
#include "Renderer.h"
class IndexBuffer
{
public:
	IndexBuffer(const unsigned short* data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void UnBind() const;
	inline unsigned int GetCount() const { return m_Count; }
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
};

