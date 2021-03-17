// Author: arnaut.leyre
// date: 13.03.2021.

#include "Perlin.h"
#include <stdio.h>
#include <stdlib.h>

struct Map GenerateMap(int width, int height){
    Map map =
            {
                    .data = malloc((height*width)*sizeof(float)),
                    .width = width,
                    .height = height,
            };
    for (int h = 0; h < map.height; ++h)
    {
        for (int w = 0; w < map.width; ++w)
        {
            map.data[h*height+w] = 0;
        }
    }
    return map;
}

float* InitSeedArray(int width, int height)
{
    float* Seed = malloc((height*width)*sizeof(float));
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            Seed[h*height+w] = (float)rand()/(float)RAND_MAX;
        }
    }
    return Seed;
}

void printMap(struct Map map){
    for (int h = 0; h < map.height; ++h)
    {
        for (int w = 0; w < map.width; ++w)
        {
            printf("|%f|",map.data[h*map.height+w]);
        }
        printf("\n");
    }
}

/*void Noise2D (Map map,int octaves,float *Seed)
{
    for (int h = 0; h < map.height; ++h)
    {
        for (int w = 0; w < map.width; ++w)
        {
            float fNoise = 0.0f;
            for (int o = 0; o < octaves; o++)
            {

            }
        }
    }
}*/


void PerlinNoise(int width, int height,int octaves) {
    Map map = GenerateMap(width,height);
    float* Seed = InitSeedArray(width,height);
    printMap(map);
    free(map.data);
}
