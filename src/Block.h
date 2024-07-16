#pragma once
enum  BlockType
{
	air,grass,sand,stone
};
struct Block
{
	BlockType type = air;
};