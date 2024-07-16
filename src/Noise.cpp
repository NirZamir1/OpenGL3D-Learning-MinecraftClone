#include "Noise.h"

Noise::Noise(unsigned int seed) :
    seed(seed)
{
    int p[256];
    for (int i = 0; i < 256; i++)
    {
        p[i] = i;
    }
    std::mt19937 g(seed);
    std::shuffle(std::begin(p), std::end(p), g);

    for (int i = 0; i < 512; i++)
    {
        permutations[i] = p[i % 256];
    }
}

float Noise::PerlinNoise3d(float x, float y, float z)
{
    int xi = (int)x & 255;
    int yi = (int)y & 255;
    int zi = (int)z & 255;

    //inner cords
    float xf = x - (float)xi;
    float yf = y - (float)yi;
    float zf = z - (float)zi;

    float u = fade(xf);
    float v = fade(yf);
    float k = fade(zf);
    int aaa, aba, aab, abb, baa, bba, bab, bbb; // hash for each corner
    aaa = permutations[permutations[permutations[xi] + yi] + zi];
    aba = permutations[permutations[permutations[xi] + yi + 1] + zi];
    aab = permutations[permutations[permutations[xi] + yi] + zi + 1];
    abb = permutations[permutations[permutations[xi] + yi + 1] + zi + 1];
    baa = permutations[permutations[permutations[xi + 1] + yi] + zi];
    bba = permutations[permutations[permutations[xi + 1] + yi + 1] + zi];
    bab = permutations[permutations[permutations[xi + 1] + yi] + zi + 1];
    bbb = permutations[permutations[permutations[xi + 1] + yi + 1] + zi + 1];

    float x1, x2, y1, y2;
    x1 = lerp(grad(aaa, xf, yf, zf), grad(baa, xf - 1, yf, zf), u);
    x2 = lerp(grad(aba, xf, yf - 1, zf), grad(bba, xf - 1, yf - 1, zf), u);
    y1 = lerp(x1, x2, v);
    x1 = lerp(grad(aab, xf, yf, zf - 1), grad(bab, xf - 1, yf, zf - 1), u);
    x2 = lerp(grad(abb, xf, yf - 1, zf - 1), grad(bbb, xf - 1, yf - 1, zf - 1), u);
    y2 = lerp(x1, x2, v);
    return (lerp(y1, y2, k) + 1) / 2; // from [-1,1] - > [0,1]

}

float Noise::PerlinNoise2d(float x, float y)
{
    return PerlinNoise3d(x, y, 0.2);
}

float Noise::grad(int hash, float x, float y, float z)
{
    switch (hash & 0xF)
    {
    case 0x0: return  x + y;
    case 0x1: return -x + y;
    case 0x2: return  x - y;
    case 0x3: return -x - y;
    case 0x4: return  x + z;
    case 0x5: return -x + z;
    case 0x6: return  x - z;
    case 0x7: return -x - z;
    case 0x8: return  y + z;
    case 0x9: return -y + z;
    case 0xA: return  y - z;
    case 0xB: return -y - z;
    case 0xC: return  y + x;
    case 0xD: return -y + z;
    case 0xE: return  y - x;
    case 0xF: return -y - z;
    default: return 0; // never happens
    }
}
