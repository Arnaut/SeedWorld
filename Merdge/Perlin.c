// Author: arnaut.leyre
// date: 13.03.2021.

#include "Perlin.h"
#include "gen.h"
#include <stdio.h>
#include <stdlib.h>

//Arnaut Leyre
struct Map GenerateMap(int height, int width){
    Map map =
            {
                    .data = malloc((height*width)*sizeof(float)),
                    .width = width,
                    .height = height,
                    .max = (float)0.0,
                    .min = (float)1.0,
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

//Arnaut Leyre
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

//Arnaut Leyre
void Noise2D (Map map,int octaves,float biais,float *Seed)
{
  float temp;
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
            temp = Noise / ScaleSum;

            if(temp < map.min)
              {
                map.min = temp;
              }
            else if(temp > map.max)
              {
                map.max = temp;
              }
            map.data[y * map.width + x] = temp;
        }
    }
}

//Arnaut Leyre
void PerlinNoise(int height, int width,int octaves,float biais, int m, int l, int s, int w, int t, int c,int w_types, int on) {
    Map map_height = GenerateMap(height,width);
    Map map_temp = GenerateMap(height,width);

    float* Seed = InitSeedArray(height,width);
    float* Seed2 = InitSeedArray(height,width);

    Noise2D(map_height,octaves,biais,Seed);
    Noise2D(map_temp,octaves,biais,Seed2);

    free(Seed);
    free(Seed2);

    char* buff;
    asprintf(&buff,"%i-%i.bmp",width,height);

    SDL_Surface* img = load_image(buff);
    float* threshold = seuil(height, width,map_height.data,s,l,m);
    int* relief = gen_img(map_height.data,map_height.height,map_height.width,img,map_height.min,map_height.max,threshold,buff);
    float* threshold_temp = seuil(height, width,map_temp.data,c,t,w);
    int* biomes = gen_biome(relief,map_temp.data,height,width,img,threshold_temp,buff);

    if(on == 1)
      {
	(void)w_types;
      }
    free(biomes);
    free(map_height.data);
    free(map_temp.data);
}
