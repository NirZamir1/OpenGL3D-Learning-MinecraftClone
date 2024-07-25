#include "World.h"

template<class T1, class T2>
std::size_t pair_hash::operator()(const std::pair<T1, T2>& p) const {
	auto hash1 = std::hash<T1>{}(p.first);
	auto hash2 = std::hash<T2>{}(p.second);
	// combine the two hash values, bit shifting so order matters
	return hash1 ^ (hash2 << 1);
}

World::World(std::string worldName,unsigned int seed)
	:m_viewDistance(10),
	worldWith(32),
	past_X(-1),
	past_Z(-1),
	worldName(worldName+ ".world")
{
	Noise noise(seed);
	std::fstream infile(this->worldName ,std::fstream::in);
	if (!infile)
	{
		//generate new world file
		std::fstream ofstream(this->worldName, std::fstream::out | std::fstream::binary);
		for (int i = 0; i < worldWith; i++)
		{
			for (int j = 0; j < worldWith; j++)
			{
				Chunk* chunk = new Chunk();
				/*
				for (int x = 0; x < 16; x++)
				{
					for (int z = 0; z < 16; z++)
					{
						int y = std::powf(noise.PerlinNoise2d((float)(x + i * 16) / 100, (float)(z + j * 16) / 100),4) * 100;
						if (y < 30)
							chunk->blocks[x][y][z].type = sand;
						else
							chunk->blocks[x][y][z].type = grass;
					}
				}*/
				for (int x = 0; x < 16; x++)
				{
					for (int z = 0; z < 16; z++)
					{
						int ylimit = std::powf(noise.PerlinNoise2d((float)(x + i * 16) / 100, (float)(z + j * 16) / 100), 4) * 100;
						for (int y = 0; y <= ylimit; y++)
						{
							float val = std::powf(noise.PerlinNoise3d((float)(x+i*16) / 50, (float)y / 50, (float)(z+j*16) / 50),0.7);
						//	std::cout << val << std::endl;
							if (val < 0.7 && y >= ylimit - 1)
							{
								chunk->blocks[x][y][z].type = grass;
							}
							else if (val < 0.7 && y < ylimit-1)
							{
								chunk->blocks[x][y][z].type = stone;
							}
							else if (y <= 1 || (val < 0.45 && y < ylimit))
							{
								chunk->blocks[x][y][z].type = sand;
							}
						}
					}
				}
				ofstream.seekg(ChunkOfSet(i-worldWith/2,j-worldWith/2));
				ofstream.write((const char*)chunk, sizeof(Chunk));
				delete chunk;
			}
		}
		ofstream.close();

		//testing if worked
		/*
		std::fstream ifstream(this->worldName, std::fstream::in | std::fstream::binary);
		for (int i = 0; i < worldWith; i++)
		{
			for (int j = 0; j < worldWith; j++)
			{
				ifstream.seekp(ChunkOfSet(i - worldWith/2, j - worldWith/2));
				Chunk* chunk = new Chunk();
				ifstream.read((char*)chunk, sizeof(Chunk));
				for (int x = 0; x < 16; x++)
				{
					for (int z = 0; z < 16; z++)
					{
						std::cout << chunk->blocks[x][0][z].type << ", ";
					}
					std::cout << std::endl;
				}
				delete chunk;
			}
		}
		ifstream.close();
		*/
	}
}
int World::ChunkOfSet(int x, int z)
{
	//row major oredering

	x += worldWith/2;
	z += worldWith/2;
	int preSizePos = (x * worldWith + z);
	//world runs between 0 and worldwidth on both axes (world with in chunks)
	if ( x < 0 || x > worldWith -1 || z < 0 || z > worldWith -1)
		return -1;
	else
		return (preSizePos * sizeof(Chunk));
}
void World::loadChunk(int x, int z)
{
	//loads a chunk from memory to m_Chunks

	std::fstream ifstream(this->worldName, std::fstream::in | std::fstream::binary);
	int pos = ChunkOfSet(x, z);
	if (pos != -1)
	{	
		Chunk* chunk = (Chunk*)malloc(sizeof(Chunk)); //allocating memory for the chunk;
		ifstream.seekg(pos);
		ifstream.read((char*)chunk, sizeof(Chunk));
		auto key = std::make_pair(x, z);
		m_chunks.insert(std::make_pair(std::make_pair(x,z), ChunkManger(chunk, { x,z })));
	}
}

void World::UpdateChunks(int playerX, int playerZ)
{ /**/
	//updates chunks around x,z in viewing distance
	int pchunkX = floor((float) playerX / 16);
	int pchunkZ = floor((float) playerZ / 16);

	if (pchunkX == past_X && pchunkZ == past_Z) //checking if changed chunks
		return;

	for (auto it = m_chunks.begin(); it  != m_chunks.end();)
	{	
		auto [x,z] = it->first;
		if (abs(pchunkX - x) >= m_viewDistance || abs(pchunkZ - z) >= m_viewDistance)
		{
			it = m_chunks.erase(it);
			if (it == m_chunks.end())
				break;
		}
		else
			it++;
	}
	int  mX = pchunkX + m_viewDistance;
	int mZ = pchunkZ + m_viewDistance;
	int counter = 0;
	for (int iX = pchunkX - m_viewDistance+1; iX < mX; iX++)
	{
		for (int jZ = pchunkZ - m_viewDistance + 1; jZ < mZ; jZ++)
		{
			if (m_chunks.find({ iX,jZ }) == m_chunks.end())
			{
				loadChunk(iX, jZ);
			}
		}
	}
	past_X = pchunkX;
	past_Z = pchunkZ;
}

void World::SaveChunk(int x, int z)
{   //save chunks to memory
	std::fstream ofstream(this->worldName, std::fstream::out | std::fstream::binary);
	ofstream.seekp(ChunkOfSet(x, z));
	ofstream.write((const char*) m_chunks[{x,z}].getChunk(), sizeof(Chunk));
}

void World::RenderWorld(Drawer& draw,Camera& camera)
{
    draw.drawLightSource(camera);
	draw.drawChunks(m_chunks, camera);

}