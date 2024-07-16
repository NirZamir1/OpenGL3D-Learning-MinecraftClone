#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h";
#include "VertexArray.h";
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "VertexStruct.h"
#include "ShapeData.h";
#include "ShapeGenerator.h";
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "IndexBuffer.h"
#include "Texture.h"
#include <math.h>
#include "Camera.h"
#include"Drawer.h"
#include "World.h"

void ProcessInputs(GLFWwindow* w,Camera* camera, double* _xpos, double* _ypos);
void printMat4(const glm::mat4& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
float X = 0;
float Y = 0;
float Z = 0;
float XAngle = 0;
float YAngle = 0;
int main()
{
    
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Minecraft Clone", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSwapInterval(0);
   
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    /* float quad[] = {
        1.0f, 1.0f ,1.0f,1.0f,//top left 
        1.0f,-1.0f ,1.0f,0.0f,//bottom left 
       -1.0f,-1.0f, 0.0f,0.0f,//bottom right 

       -1.0f, 1.0f, 0.0f,1.0f,//top right 
        1.0f, 1.0f ,1.0f,1.0f,//top left 
       -1.0f,-1.0f, 0.0f,0.0f,//bottom right 
    };
    VertexArray vaQuad;
    VertexBuffer vbQuad(quad,sizeof(float)*24);
    VertexBufferLayout blQuad;
    blQuad.Push<float>(2);
    blQuad.Push<float>(2);
    vaQuad.AddBuffer(vbQuad, blQuad);
    Shader fbShader("res/shaders/fbShader.shader");
    
   
    //setting up framebuffer
    unsigned int fbo;
    GLCall(glGenFramebuffers(1, &fbo));
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, fbo));
    
    unsigned int fbTexture;
    glGenTextures(1, &fbTexture);
    GLCall(glBindTexture(GL_TEXTURE_2D, fbTexture));
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 800, 800, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbTexture, 0));
    
    //setting up render buffer object
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 800));
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));*/
    
    Camera camera(window);
    Drawer drawer;
    World world("funny");

    //setting up mouse movement
    double cX, cY; 
    ProcessInputs(window,&camera, &cX, &cY);
    double lX = cX, lY = cY;
    double deltaX;
    double deltaY;
    /*
    Shader objShader("res/shaders/test.shader");
    ShapeData<Vertex> triangle = ShapeGenerator::makeTriangle();
    VertexBuffer vb(triangle.vertecies,triangle.GetVerteciesBufferSize());
    IndexBuffer in(triangle.indecies, triangle.numIndecies);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    VertexArray va;
    float offsets[] = { 0.0,0.5, 0.9,1.3 };
    VertexBuffer offsetBuffer((void*)offsets,sizeof(offsets));
    va.AddBuffer(vb, layout); 
    va.Bind();
    offsetBuffer.Bind();
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0,0);
    glEnableVertexAttribArray(2);
    glVertexAttribDivisor(2, 1);
    in.Bind();
    objShader.Bind();
    */
    

    while (!glfwWindowShouldClose(window))
    {   
        
        deltaX = cX - lX;
        deltaY = cY - lY;
        XAngle = -0.1 * deltaY;
        YAngle = -0.1 * deltaX;
        camera.rotatePitch(XAngle);
        camera.rotateYaw(YAngle);
        
        /*
        //updating second framebuffer to windowsize
        GLCall(glBindTexture(GL_TEXTURE_2D, fbTexture));
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, camera.width(), camera.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, camera.width(),camera.height()));
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);*/


        glEnable(GL_DEPTH_TEST);
        glClearColor(0.4f, 0.8f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, camera.width(), camera.height());
        world.UpdateChunks(camera.getPosition().x, camera.getPosition().z);
        world.RenderChunks(drawer, camera);

        //processing inputs
        ProcessInputs(window,&camera,&cX,&cY);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
void ProcessInputs(GLFWwindow* w ,Camera* camera,double* _xpos, double* _ypos)
{
    double ypos, xpos;
    float add = 0.1;
    if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
        camera->moveForward(1);
    if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
        camera->moveForward(-1);
    if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
        camera->moveRight(-1);
    if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
        camera->moveRight(1);
    if (glfwGetKey(w, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera->moveUp(1);
    if (glfwGetKey(w, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera->moveUp(-1);
    glfwGetCursorPos(w, &xpos, &ypos);
    //std::cout << xpos << "," << ypos << std::endl;
    *_xpos = xpos;
    *_ypos = ypos;
}

//mr helper