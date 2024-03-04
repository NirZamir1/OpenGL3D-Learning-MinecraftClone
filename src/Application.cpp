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
int width(GLFWwindow* window);
int height(GLFWwindow* window);
int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "OMG CUBE", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();
    glEnable(GL_DEPTH_TEST);
    ShapeData shape = ShapeGenerator::makeCube();
    VertexArray va;
    VertexBuffer vb(shape.vertecies,shape.GetVerteciesBufferSize());
    IndexBuffer ib(shape.indecies,shape.numIndecies);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    va.AddBuffer(vb, layout);
    va.Bind();
    ib.Bind();
    Shader shader("res/shaders/basics.shader");
    shader.Bind();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */ 
        glViewport(0, 0, width(window), height(window));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 ModelTransformMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f),45.0f, glm::vec3(1.0f, 1.0f, 0.0f));
        glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(60.0f), (float)width(window) / height(window), 0.1f, 10.0f);
        glm::mat4  mvpMatrix = ProjectionMatrix * ModelTransformMatrix * rotationMatrix;
        shader.SetUniformMatrix4fv("mvpMatrix", mvpMatrix);
        GLCall(glDrawElements(GL_TRIANGLES, shape.numIndecies, GL_UNSIGNED_SHORT, 0));
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
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