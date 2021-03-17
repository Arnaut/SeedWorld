// Author: arnaut.leyre
// date: 13.03.2021.

#ifndef MAIN_C_PERLIN_H
#define MAIN_C_PERLIN_H
typedef struct Map
{
    float* data;     // Pixel Lists.
    int width;
    int height;
} Map;

struct Map GenerateMap(int width, int height);
float* InitSeedArray(int width, int height);
void printMap(struct Map map);
void PerlinNoise(int width, int height,int octaves);
#endif //MAIN_C_PERLIN_H
