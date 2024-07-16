#pragma once
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <vector>
#include"ChunkStruct.h"
#include "VertexBuffer.h"
class ChunkManger
{
private:
	VertexBuffer* chunkModelTransform[3];
	Chunk* chunk;
	std::vector<glm::mat4> matrixTransformations[3];
public:
	Chunk* getChunk() const;
	ChunkManger(Chunk* Chunk, std::pair<int,int> ChunkCords);
	ChunkManger();
	ChunkManger(ChunkManger& chunkManger);
	ChunkManger(ChunkManger&& chunkManger);
	inline int getCount(int blocktype) {
		return matrixTransformations[blocktype -1].size();
	}

	~ChunkManger();
	void UpdateChunk();
	void BindChunkBlock(int mememoryLayoutOfSet,int blocktype); //sets up the chunk for render
};