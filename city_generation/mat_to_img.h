#ifndef MAT_TO_IMG
#define MAT_TO_IMG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operation.h"


void place_house(SDL_Surface *img, int x, int y, int htype, int wtype);

void placeSprite(SDL_Surface *dst, SDL_Surface *src, int C, int R);

void drawName(char *s, int len);

void createSpriteRGB(int* map, int rows, int cols, int wt);

#endif
