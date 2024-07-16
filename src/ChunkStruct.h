#pragma once
#include "Block.h"
#include "glm.hpp"
#include <vector>
#include "VertexBuffer.h"
struct Chunk
{
	static const int SIZE = 16;
	static const int ChunkSize = sizeof(Block) * SIZE * SIZE * SIZE;
	Block blocks[SIZE][256][SIZE];	
};
