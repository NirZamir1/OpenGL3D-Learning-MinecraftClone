#pragma once
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
class Noise
{
public:
	Noise(unsigned int seed);
	float PerlinNoise3d(float x, float y, float z);
	float PerlinNoise2d(float x, float y);
private:
	int permutations[512];
	unsigned int seed;
	inline float lerp(float a, float b, float t)
	{
		return a + t * (b - a);
	}
	inline float fade(float t)
	{
		return t * t * t * (t * (t * 6 - 15) + 10);
	}
	float grad(int hash, float x, float y, float z);
};