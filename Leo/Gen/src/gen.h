#ifndef GEN_H
#define GEN_H

#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include "pixel_operations.h"

void init_sdl();
SDL_Surface* load_image(char *path);
SDL_Surface* display_image(SDL_Surface *img);
void wait_for_keypressed();
int* gen_img(float* mat, size_t rows, size_t cols, SDL_Surface* img, float min, float max, float* threshold);
float* seuil(size_t height,size_t width,float* mat, int ocean, int plains, int mountains);
int* gen_biome(int* relief, float* temperature, size_t height, size_t width, SDL_Surface* img,float* threshold);

#endif
