// Author: arnaut.leyre
// date: 13.03.2021.

#ifndef MAIN_C_PERLIN_H
#define MAIN_C_PERLIN_H
typedef struct Map
{
  float* data;     // Pixel Lists.
  int height;
  int width;
  float max;
  float min;
} Map;

struct Map GenerateMap(int height, int width);
float* InitSeedArray(int height, int width);
void printMap(struct Map map);
void Noise2D (Map map,int octaves,float biais,float *Seed);
void PerlinNoise(int height, int width,int octaves,float biais);
#endif //MAIN_C_PERLIN_H
