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

int width(GLFWwindow* window);
int height(GLFWwindow* window);
void ProcessInputs(GLFWwindow* w, double* _xpos, double* _ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, key_callback);
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
    float farPlane = 100.0f;
    float range = farPlane - nearPlane;
    float A = (-farPlane - nearPlane) / -range;
    float B = 2.0f * farPlane * nearPlane / -range;
    float angle = 0.0f;

    //setting up mouse movement
    double cX, cY; 
    ProcessInputs(window, &cX, &cY);
    double lX = cX, lY = cY;
    double deltaX;
    double deltaY;

    while (!glfwWindowShouldClose(window))
    {   
        deltaX = cX - lX;
        deltaY = cY - lY;
        XAngle = -0.1 * deltaY;
        YAngle = -0.1 * deltaX;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float f = 1 /std::tan(glm::radians(45.0f));
        float aspect = 1/((float)width(window) / height(window));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians( 0.0f), glm::vec3(0.0f,1.0f, 0.0f));
        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat4 viewT = glm::translate(glm::mat4(1.0f), glm::vec3(-X, -Y, -Z));
        glm::mat4 viewR = glm::rotate(glm::mat4(1.0f), glm::radians(YAngle), glm::vec3(0.0f, 1.0f, 0.0f));
        viewR = glm::rotate(viewR, glm::radians(XAngle), glm::vec3(1.0f, 0.0f, 0.0f));
        glm::mat4 model = translate * rotate;
        glm::mat4 view = viewR * viewT;
        glm::mat4 projection = glm::mat4(aspect * f,  0.0f,  0.0f, 0.0f,
                                         0.0f,        f,     0.0f, 0.0f,
                                         0.0f,        0.0f,  A, 1.0f,
                                         0.0f,        0.0f,  B, 0.0f);
        shader.SetUniform3f("cameraPos", X, Y, Z);
        shader.SetUniform3f("lightPos", 0.0f, 0.0f, -5.0f);
        shader.SetUniformMatrix4fv("mMatrix", model);
        glm::mat4 mvpMatrix = projection * view * model;
        shader.SetUniform1f("tex", 0);
        shader.SetUniformMatrix4fv("mvpMatrix", mvpMatrix);
        glViewport(0, 0, width(window), height(window));
        GLCall(glDrawElements(GL_TRIANGLES,shape.numIndecies, GL_UNSIGNED_SHORT, 0));
        //processing inputs
        ProcessInputs(window,&cX,&cY);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void ProcessInputs(GLFWwindow* w,double* _xpos, double* _ypos)
{
    double ypos, xpos;
    if (glfwGetKey(w, GLFW_KEY_W) == GLFW_PRESS)
        std::cout << "move forward" << std::endl;
    if (glfwGetKey(w, GLFW_KEY_S) == GLFW_PRESS)
        std::cout << "move backward" << std::endl;
    if (glfwGetKey(w, GLFW_KEY_A) == GLFW_PRESS)
        std::cout << "move left" << std::endl;
    if (glfwGetKey(w, GLFW_KEY_D) == GLFW_PRESS)
        std::cout << "move right" << std::endl;
    if (glfwGetKey(w, GLFW_KEY_SPACE) == GLFW_PRESS)
        std::cout << "move up" << std::endl;
    if (glfwGetKey(w, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        std::cout << "move down" << std::endl;
    glfwGetCursorPos(w, &xpos, &ypos);
    std::cout << xpos << "," << ypos << std::endl;
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
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    float add = 0.5f;
    float addA = 1.0f;
    /*if (action == GLFW_RELEASE)
        keyCache[key] = false;*/
   if (action == GLFW_PRESS || action == GLFW_REPEAT )
    {
        switch (key)
        {
        case  GLFW_KEY_W :
        {
            Z += add;
            break;
        }
        case GLFW_KEY_S:
        {
            Z -= add;
            break;

        }
        case GLFW_KEY_A:
        {
            X -= add;
            break;

        }
        case GLFW_KEY_D:
        {
            X += add;
            break;
        }
        case GLFW_KEY_SPACE:
        {
            Y += add;
            break;

        }
        case GLFW_KEY_LEFT_SHIFT:
        {
            Y -= add;
            break;
        }
        case GLFW_KEY_LEFT:
        {
            YAngle += addA;
            break;
        }
        case GLFW_KEY_RIGHT:
        {
            YAngle -= addA;
            break;
        }
        case GLFW_KEY_UP:
        {
            XAngle += addA;
            break;
        }
        case GLFW_KEY_DOWN:
        {
            XAngle -= addA;
            break;
        }
        default:
            break;
        }
    }
        
    
}