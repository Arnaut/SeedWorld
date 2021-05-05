// Author: arnaut.leyre
// date: 13.03.2021.

#include "Perlin.h"
#include "gen.h"
#include <stdio.h>
#include <stdlib.h>

struct Map GenerateMap(int height, int width){
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
            map.data[h*width+w] = 0;
        }
    }
    return map;
}

float* InitSeedArray(int height, int width)
{
    float* Seed = malloc((height*width)*sizeof(float));
    for (int h = 0; h < height; ++h)
    {
        for (int w = 0; w < width; ++w)
        {
            Seed[h*width+w] = (float)rand()/(float)RAND_MAX;
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

void Noise2D (Map map,int octaves,float biais,float *Seed)
{
    for (int x = 0; x < map.width; ++x)
    {
        for (int y = 0; y < map.height; ++y)
        {
            float Noise = 0;
	    float Scale = 1;
	    float ScaleSum = 0;
            for (int o = 0; o < octaves; o++)
            {
	      ScaleSum += Scale;
	      int Pitch = map.width >> o;
	      int SampleX1 = (x / Pitch) * Pitch;
	      int SampleY1 = (y / Pitch) * Pitch;
	      int SampleX2 = (SampleX1 + Pitch) % map.width;
	      int SampleY2 = (SampleY1 + Pitch) % map.width;

	      float BlendX = (float)(x - SampleX1) / (float)Pitch;
	      float BlendY = (float)(y - SampleY1) / (float)Pitch;

	      float SampleT = (1 - BlendX) * Seed[SampleY1 * map.width + SampleX1] + BlendX * Seed[SampleY1 * map.width + SampleX2];
	      float SampleB = (1 - BlendX) * Seed[SampleY2 * map.width + SampleX1] + BlendX * Seed[SampleY2 * map.width + SampleX2];

	      Noise += (BlendY * (SampleB - SampleT) + SampleT) * Scale;
	      Scale = Scale / biais;

            }
	    map.data[y * map.width + x] = Noise / ScaleSum;
        }
    }
}


void PerlinNoise(int height, int width,int octaves,float biais) {
    Map map = GenerateMap(height,width);
    float* Seed = InitSeedArray(height,width);
    Noise2D(map,octaves,biais,Seed);
    free(Seed);
    SDL_Surface* img = load_image("tested.bmp");
    gen_img(map.data,map.height,map.width,img);
    //printMap(map);
    free(map.data);
    
}
