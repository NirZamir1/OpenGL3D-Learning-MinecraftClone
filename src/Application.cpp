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

int width(GLFWwindow* window);
int height(GLFWwindow* window);
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
    window = glfwCreateWindow(800, 800, "OMG CUBE", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSwapInterval(1);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    float quad[] = {
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
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width(window), height(window), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbTexture, 0));
    
    //setting up render buffer object
    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width(window), height(window)));
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));

    Texture tex("res/textures/grass.png");
    ShapeData<VertexTex> shape = ShapeGenerator::makeTexturedCube();
    VertexArray vaCube;
    VertexBuffer vb(shape.vertecies,shape.GetVerteciesBufferSize());
    IndexBuffer ib(shape.indecies,shape.numIndecies);
    VertexBufferLayout layout;
    Camera camera;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    vaCube.AddBuffer(vb, layout);
    vaCube.Bind();
    ib.Bind();
    Shader objShader("res/shaders/basic.shader");
    Shader lightsourceShader("res/shaders/lightSource.shader");
    objShader.Bind();
    tex.Bind();
    float nearPlane = 1.0f;
    float farPlane = 100.0f;
    float range = farPlane - nearPlane;
    float A = (-farPlane - nearPlane) / -range;
    float B = 2.0f * farPlane * nearPlane / -range;
    float angle = 0.0f;
    
    glm::vec4 lightColor = glm::vec4(0.5f, 0.5f, 1.0f,1.0f);

    //setting up mouse movement
    double cX, cY; 
    ProcessInputs(window,&camera, &cX, &cY);
    double lX = cX, lY = cY;
    double deltaX;
    double deltaY;

    while (!glfwWindowShouldClose(window))
    {   
        
        deltaX = cX - lX;
        deltaY = cY - lY;
        XAngle = -0.1 * deltaY;
        YAngle = -0.1 * deltaX;
        camera.rotatePitch(XAngle);
        camera.rotateYaw(YAngle);

        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        vaCube.Bind();

        float f = 1 /std::tan(glm::radians(45.0f));
        glm::mat4 view = camera.getViewMatrix();
        float aspect = 1/((float)width(window) / height(window));
        glm::mat4 projection = glm::mat4(aspect * f,  0.0f,  0.0f, 0.0f,
                                         0.0f,        f,     0.0f, 0.0f,
                                         0.0f,        0.0f,  A, 1.0f,
                                         0.0f,        0.0f,  B, 0.0f);  
        //lightsource purple
        lightsourceShader.Bind();
        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.2f, 0.2f, 0.2f));
        glm::mat4 rotateOrigin = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        glm::mat4 translateOrigin = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 0.0f, 0.0f));
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle +=1), glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 modellight =  translate * rotate * translateOrigin * rotateOrigin* scale;
        glm::mat4 mvpMatrix = projection * view * modellight;
        lightsourceShader.SetUniform4f("lightColor", lightColor);
        lightsourceShader.SetUniformMatrix4fv("mvpMatrix", mvpMatrix);
        GLCall(glDrawElements(GL_TRIANGLES, shape.numIndecies, GL_UNSIGNED_SHORT, 0));

        //grass cube
        tex.Bind();
        rotate = glm::rotate(glm::mat4(1.0f), glm::radians( 0.0f), glm::vec3(0.0f,1.0f, 0.0f));
        translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));
        glm::mat4 model = translate * rotate;
        objShader.Bind();
        objShader.SetUniform4f("lightColor", lightColor);
        objShader.SetUniform3f("cameraPos",camera.getPosition());
        objShader.SetUniform4f("lightPos", modellight*glm::vec4(1.0f,1.0f,1.0f,1.0f));
        objShader.SetUniformMatrix4fv("mMatrix", model);
        mvpMatrix = projection * view * model;
        objShader.SetUniform1f("tex", 0);
        objShader.SetUniformMatrix4fv("mvpMatrix", mvpMatrix);
        glViewport(0, 0, width(window), height(window));
        GLCall(glDrawElements(GL_TRIANGLES,shape.numIndecies, GL_UNSIGNED_SHORT, 0)); 
        
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        vaQuad.Bind();
        glBindTexture(GL_TEXTURE_2D, fbTexture);
        fbShader.Bind();
        fbShader.SetUniform1f("tex", 0);
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
        

        
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
int width(GLFWwindow* window)
{
    int width;
    glfwGetFramebufferSize(window, &width, 0);
    return width;
}
int height(GLFWwindow* window)
{
    int height;
    glfwGetFramebufferSize(window, 0, &height);
    return height;
}
