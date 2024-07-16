#pragma once
#include <fstream>
#include "ChunkStruct.h"
#include "unordered_map"
#include "Drawer.h"
#include "ChunkManager.h"
#include "math.h"
#include "iostream"	
#include "Types.h"
#include "Noise.h"
class World
{
public :
	World(std::string worldName = "World");
	void UpdateChunks(int playerX, int playerZ);//updates chunks according to view distance
	void RenderChunks(Drawer& draw, Camera& camera);

private:
	int m_viewDistance;
	int worldWith;
	chunkmap m_chunks;
	std::string worldName;
	int past_X;
	int past_Z;
	void SaveChunk(int x, int z);
	//saves chunk back to memory 
	void loadChunk(int x, int z);//gets chunks out of memory
	int ChunkOfSet(int x, int z);//caculates the offset of chunk in disk memory
};