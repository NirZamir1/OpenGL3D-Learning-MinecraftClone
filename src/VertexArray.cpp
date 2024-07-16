#include "VertexArray.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
	GLCall(glGenVertexArrays(1, &m_RendererID));
	layoutOfSet = 0;
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}
void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}
void VertexArray::UnBind() const
{
	GLCall(glBindVertexArray(0));
}
int VertexArray::getlayoutOfSet() const
{
	return layoutOfSet;
}
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	
	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i+layoutOfSet, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
		offset += VertexBufferElement::GetSizeOfType(element.type) * element.count;
	}
	layoutOfSet += elements.size();
	UnBind();
}

