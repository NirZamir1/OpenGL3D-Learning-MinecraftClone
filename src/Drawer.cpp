#include "Drawer.h"
Drawer::Drawer() :
    m_shape(ShapeGenerator::makeTexturedCube()), m_vb(m_shape.vertecies, m_shape.GetVerteciesBufferSize()),
    m_Ib(m_shape.indecies,m_shape.numIndecies),m_objShader("res/shaders/basic.shader"),
    m_lightSourceShader("res/shaders/lightSource.shader")
{
    //temporarly setting up lightsource manualy
    m_lightSource.LightColor = glm::vec4(0.8, 0.8, 1.0f, 1.0f);
    m_lightSource.LightPosition = glm::vec4(0.0f, 100.0f, 0.0f, 1.0f);
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);
    m_vaCube.AddBuffer(m_vb, layout);
    m_textures[0] = new Texture("res/textures/grass.png");
    m_textures[1] = new Texture("res/textures/sand.png");
    m_textures[2]=  new Texture("res/textures/stone.png");

}

void Drawer::drawChunks(chunkmap& chunks, Camera& camera)
{


    m_vaCube.Bind();
    m_Ib.Bind();
    float fovAngle = 90.0f;
    float nearPlane = 1.0f;
    float farPlane = 1000.0f;
    float range = farPlane - nearPlane;
    float A = (-farPlane - nearPlane) / -range;
    float B = 2.0f * farPlane * nearPlane / -range;
    float f = 1 / std::tan(glm::radians(fovAngle / 2));
    float aspect = 1 / ((float)camera.width() / camera.height());

    projectionMatrix = glm::mat4(aspect * f, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, A, 1.0f,
        0.0f, 0.0f, B, 0.0f);
    glm::mat4 vpMatrix = projectionMatrix * camera.getViewMatrix();
    m_objShader.Bind();
    m_objShader.SetUniform4f("lightColor", m_lightSource.LightColor);
    m_objShader.SetUniform4f("lightPos", m_lightSource.LightPosition);
    m_objShader.SetUniform3f("cameraPos", camera.getPosition());
    m_objShader.SetUniform1f("tex", 0);
    m_objShader.SetUniformMatrix4fv("vpMatrix", vpMatrix);
    for (auto& [key, val] : chunks)
    {
        glm::vec3 cameraChunkVec = glm::vec3(key.first - std::floorf(camera.getPosition().x / 16), 0, std::floorf(key.second - camera.getPosition().z / 16));
        bool isInView = inViewChecker(camera, key);
        if (isInView)
        {
            for (int i = 0; i < 3; i++)
            {
                m_textures[i]->Bind();
                val.BindChunkBlock(m_vaCube.getlayoutOfSet(),i+1);
                glDrawElementsInstanced(GL_TRIANGLES, m_shape.numIndecies, GL_UNSIGNED_SHORT, 0, val.getCount(i+1));
            }
        }
    }
}

bool Drawer::inViewChecker(Camera& camera, std::pair<int, int> chunkPos) const
{
    if (isBlockInView(camera, glm::vec3(chunkPos.first * 16, 0, chunkPos.second * 16)))
        return true;
    if (isBlockInView(camera, glm::vec3(chunkPos.first * 16 + 16, 0, chunkPos.second * 16)))
        return true;
    if (isBlockInView(camera, glm::vec3(chunkPos.first * 16 + 16, 0, chunkPos.second * 16 + 16)))
        return true;
    if (isBlockInView(camera, glm::vec3(chunkPos.first * 16 + 16, 0, chunkPos.second * 16 + 16)))
        return true;
    if (isBlockInView(camera, glm::vec3(chunkPos.first * 16, 255, chunkPos.second * 16)))
        return true;
    if (isBlockInView(camera, glm::vec3(chunkPos.first * 16 + 16, 255, chunkPos.second * 16)))
        return true;
    if (isBlockInView(camera, glm::vec3(chunkPos.first * 16 + 16, 255, chunkPos.second * 16 + 16)))
        return true;
    if (isBlockInView(camera, glm::vec3(chunkPos.first * 16 + 16, 255, chunkPos.second * 16 + 16)))
        return true;
    return false;
}

bool Drawer::isBlockInView(Camera& camera, glm::vec3 pos) const
{
    const float seeingFactor = 0;
    glm::vec3 blockDir = pos - camera.getPosition();
    float dotProduct = glm::dot(blockDir, camera.getLookVec()) / (glm::length(blockDir) * glm::length(camera.getLookVec()));
    if (dotProduct > seeingFactor)
        return true;
    return false;
}
