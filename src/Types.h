#pragma once
#include<unordered_map>
#include "ChunkManager.h"
struct pair_hash
{
	template<class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2>& p) const;
};
typedef std::unordered_map<std::pair<int, int>, ChunkManger, pair_hash> chunkmap;