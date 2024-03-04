#include "IndexBuffer.h"
IndexBuffer::IndexBuffer(const unsigned short* data, unsigned int count)
    :m_Count(count)
{
    ASSERT(sizeof(unsigned short) == sizeof(GLushort)); 
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned short), data, GL_STATIC_DRAW));
    UnBind();
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1,&m_RendererID))
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
