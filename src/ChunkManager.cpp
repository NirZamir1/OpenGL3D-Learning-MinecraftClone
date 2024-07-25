#pragma once
#include "ChunkManager.h"



ChunkManger::ChunkManger(Chunk* chunk, std::pair<int, int> ChunkCords)
{
	this->chunk = chunk;	
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				bool isSeable = true;
				if (i > 0 && j > 0 && k >> 0 && i < 15 && k < 15 && j < 255)
				{
					isSeable = (chunk->blocks[i - 1][j][k].type == BlockType::air || chunk->blocks[i + 1][j][k].type == BlockType::air ||
						chunk->blocks[i][j - 1][k].type == BlockType::air || chunk->blocks[i][j + 1][k].type == BlockType::air ||
						chunk->blocks[i][j][k - 1].type == BlockType::air || chunk->blocks[i][j][k + 1].type == BlockType::air);
				}
				if (chunk->blocks[i][j][k].type != BlockType::air && isSeable)
				{
					matrixTransformations[chunk->blocks[i][j][k].type-1].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(i + ChunkCords.first * 16, j, k + ChunkCords.second * 16)));
				}
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		chunkModelTransform[i] = new VertexBuffer(matrixTransformations[i].data(), matrixTransformations[i].size() * sizeof(glm::mat4));
	}
}

ChunkManger::ChunkManger() :
	chunk(0)
{
}
ChunkManger::ChunkManger(ChunkManger& chunkManger)
{
	chunk = (Chunk*)malloc(sizeof(Chunk));
	*chunk = *(chunkManger.chunk);
	for (int i = 0; i < 3; i++)
	{
		matrixTransformations[i] = std::move(chunkManger.matrixTransformations[i]);
		chunkModelTransform[i] = new VertexBuffer(matrixTransformations[i].data(), matrixTransformations[i].size() * sizeof(glm::mat4));
	}
	
}
ChunkManger::ChunkManger(ChunkManger&& chunkManger)
{
	chunk = (Chunk*)malloc(sizeof(Chunk));
	*chunk = *(chunkManger.chunk);
	for (int i = 0; i < 3; i++)
	{
		matrixTransformations[i] = std::move(chunkManger.matrixTransformations[i]);
		chunkModelTransform[i] = new VertexBuffer(matrixTransformations[i].data(), matrixTransformations[i].size() * sizeof(glm::mat4));
	}
}

ChunkManger::~ChunkManger()
{
	for (int i = 0; i < 3; i++)
	{
		delete chunkModelTransform[i];
	}
	free(chunk);
}

void ChunkManger::UpdateChunk()
{
	//does nothing at the moment, just in case i will want to be able to change chunk data;
}
void ChunkManger::BindChunkBlock(int memoryLayoutOfSet,int blocktype)
{
	chunkModelTransform[blocktype-1]->Bind();
	for (int i = 0; i < 4; i++)
	{
		GLCall(glVertexAttribPointer(i + memoryLayoutOfSet, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * 4 * i)));
		GLCall(glEnableVertexAttribArray(i + memoryLayoutOfSet));
		GLCall(glVertexAttribDivisor(i + memoryLayoutOfSet, 1));
	}
	

}
void ChunkManger::UnBindChunkBlock(int memoryLayoutOfSet, int blocktype)
	{
		chunkModelTransform[blocktype - 1]->UnBind();
		for (int i = 0; i < 4; i++)
		{
			GLCall(glDisableVertexAttribArray(i + memoryLayoutOfSet));
		}
}
Chunk* ChunkManger::getChunk() const
{
	return chunk;
}