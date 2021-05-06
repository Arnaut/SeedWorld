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
int* gen_img(float* mat, size_t rows, size_t cols, SDL_Surface* img);

#endif
