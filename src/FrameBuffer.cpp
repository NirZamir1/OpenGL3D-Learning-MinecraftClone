#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() :
    m_fbShader(0),m_Rbo(0),m_Texture(0),m_RendererID(0)
{
}
FrameBuffer::FrameBuffer(int width, int height,const char* shaderPath) :
    m_fbShader(0)
{
    m_fbShader = new Shader(shaderPath);
    GLCall(glGenFramebuffers(1, &m_RendererID));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID));

    glGenTextures(1, &m_Texture);
    GLCall(glBindTexture(GL_TEXTURE_2D, m_Texture));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Texture, 0));

    //setting up render buffer object
    glGenRenderbuffers(1, &m_Rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, m_Rbo);
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Rbo);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_RendererID);
    glDeleteTextures(1, &m_Texture);
    glDeleteRenderbuffers(1, &m_Rbo);
    delete m_fbShader;
}

void FrameBuffer::UpdateSize(int width, int height)
{
}

void FrameBuffer::Bind()
{
    m_fbShader->Bind();
    glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
}

void FrameBuffer::bindDeafult()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
