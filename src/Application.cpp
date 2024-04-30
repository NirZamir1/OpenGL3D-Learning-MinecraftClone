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
#define DegToRad(x)  ((x*3.14159265f)/180.0f)
int width(GLFWwindow* window);
int height(GLFWwindow* window);
void printMat4(const glm::mat4& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(500, 300, "OMG CUBE", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    Texture tex("res/textures/grass.png");
    ShapeData<VertexTex> shape = ShapeGenerator::makeTexturedCube();
    VertexArray va;
    VertexBuffer vb(shape.vertecies,shape.GetVerteciesBufferSize());
    IndexBuffer ib(shape.indecies,shape.numIndecies);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    va.Bind();
    ib.Bind();
    Shader shader("res/shaders/basics.shader");
    shader.Bind();
    tex.Bind();
    float nearPlane = 1.0f;
    float farPlane = 8.0f;

    float range = farPlane - nearPlane;
    
    float A = (-farPlane - nearPlane) / -range;
    float B = 2.0f * farPlane * nearPlane / -range;

    float angle = 0.0f;
    while (!glfwWindowShouldClose(window))
    {   
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float f = 1 /std::tan(glm::radians(30.0f));
        float aspect = 1/((float)width(window) / height(window));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(angle+= 0.5f), glm::vec3(1.0f,1.0f, 1.0f));
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 6.0f));
        glm::mat4 projection = glm::mat4(aspect * f,  0.0f,  0.0f, 0.0f,
                                         0.0f,        f,     0.0f, 0.0f,
                                         0.0f,        0.0f,  A, 1.0f,
                                         0.0f,        0.0f,  B, 0.0f);
        glm::mat4 mvpMatrix = projection * translate * rotate;
        shader.SetUniform1f("tex", 0);
        shader.SetUniformMatrix4fv("mvpMatrix", mvpMatrix);
        glViewport(0, 0, width(window), height(window));
        GLCall(glDrawElements(GL_TRIANGLES,shape.numIndecies, GL_UNSIGNED_SHORT, 0));
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