#pragma once
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"
#include "Block.h"
#include "Shader.h"
#include "LightSource.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "ShapeData.h"
#include "VertexStruct.h"
#include "ShapeGenerator.h"
#include "IndexBuffer.h"
#include "ChunkManager.h"
#include "types.h"
class Drawer
{
public:
	Drawer();
	void drawChunks(chunkmap& chunks,Camera& camera);
	void drawLightSource(Camera& camera);

private:
	ShapeData<VertexTex> m_shape;
	VertexBuffer m_vb;
	IndexBuffer m_Ib;
	VertexArray m_vaCube;
	Texture* m_textures[3];
	Shader m_objShader;
	Shader m_lightSourceShader;
	LightSource m_lightSource;
	glm::mat4 projectionMatrix;
	bool inViewChecker(Camera& camera,std::pair<int,int> chunkPos) const;
	bool isBlockInView(Camera& camera, glm::vec3 pos) const;
};