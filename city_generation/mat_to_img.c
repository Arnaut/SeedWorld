#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operation.h"


#define CITY 0
#define ROAD 1
#define INTERSECTION 4

#define H1 7
#define H2 8
#define H3 9


void place_house(SDL_Surface *img, int x, int y, int htype, int wtype)
{
	Uint8 *r;
	Uint8 *g;
	Uint8 *b;
	
	Uint32 pixel;

	SDL_Surface *house;

	//house sprite loading

	if(wtpye ==0)
	{
		if(htype ==H1) 
			house = SDL_LoadBMP("images/elf1b.bmp");
		else if(htype ==H2) 
			house = SDL_LoadBMP("images/elf2b.bmp");
		else if(htype ==H3) 
			house = SDL_LoadBMP("images/elf3b.bmp");
	}
	else if(wtype == 1)
	{
		if(htype ==H1) 
			house = SDL_LoadBMP("images/fut1.bmp");
		else if(htype ==H2) 
			house = SDL_LoadBMP("images/fut2.bmp");
		else if(htype ==H3) 
			house = SDL_LoadBMP("images/fut3.bmp");
	}
	else
	{
		if(htype ==H1) 
			house = SDL_LoadBMP("images/med1.bmp");
		else if(htype ==H2) 
			house = SDL_LoadBMP("images/med2.bmp");
		else if(htype ==H3) 
			house = SDL_LoadBMP("images/med3.bmp");
	}


	for(int i=x; i<x+house->w; i++)
	{
		for(int j=y; j<y+house->h; j++)
		{
			Uint32 p = get_pixel(house, i-x, j-y);
 
			SDL_GetRGB(p, house->format, &r, &g, &b);
		
			pixel =SDL_MapRGB(img->format, r, g, b);

			put_pixel(img, i, j, pixel);
		}
	}
	SDL_FreeSurface(house);
}


void placeSprite(SDL_Surface *dst, SDL_Surface *src, int C, int R)
{
	Uint8 *r;
	Uint8 *g;
	Uint8 *b;

	
	Uint32 pixel;

	for(int i=C; i<C+src->w; i++)
	{
		for(int j=R; j<R+src->h; j++)
		{
			Uint32 p = get_pixel(src, i-C, j-R);
			
			if(p==1) // pastes the pixel only if it's not 255.0.255
				continue;

 
			SDL_GetRGB(p, src->format, &r, &g, &b);

			pixel =SDL_MapRGB(dst->format, r, g, b);
			 
			put_pixel(dst, i, j, pixel);
		}
	}
}


void drawName(char *s, int len)
{
	SDL_Surface *img;
	SDL_Surface *letter;

	Uint8 *r;
	Uint8 *g;
	Uint8 *b;
	Uint32 pixel;

	img = SDL_CreateRGBSurface(0, (7*len), 7, 32, 0, 0, 0, 0);
	for(int c=0; c<len; c++)
	{

		char tmp[] = "images/alphabet/*.bmp";
		tmp[16] = s[c];

		if(! (letter = SDL_LoadBMP(tmp)) )
		{
			printf("error loading letter bmp\n");
			return NULL;
		}

		for(int i =0+(c*7); i<(c*7)+7; i++)
		{
			for(int j=0; j<7; j++)
			{
				Uint32 p = get_pixel(letter, i-c*7, j);
				SDL_GetRGB(p, letter->format, &r, &g, &b);
				pixel = SDL_MapRGB(img->format, r, g, b);
				put_pixel(img, i, j, pixel);

			}
		}
	}
	printf("saved\n");
	SDL_SaveBMP(img, "name.bmp");

	SDL_FreeSurface(img);
	SDL_FreeSurface(letter);
}


void createSpriteRGB(int* map, int rows, int cols, int wt)
{
	SDL_Surface *img;

	img = SDL_CreateRGBSurface(0, rows, cols, 32, 0, 0, 0, 0);
	
	Uint32 pixel;

	for(int i = 0; i < cols; i++)
    {
		for(int j = 0; j < rows; j++)
        {
        	if(map[i * cols + j] == ROAD || map[i*cols+j] == INTERSECTION)
            {
              	pixel = SDL_MapRGB(img->format, 84, 84, 84);
            }
			
          	else if (map[i * cols + j] == CITY)
            {
              	pixel = SDL_MapRGB(img->format, 255, 0, 255); // set the empty tile to pink
            }

          	put_pixel(img, j, i, pixel);
        }
    }

	for(int i = 0; i < cols; i++)
    {
		for(int j = 0; j < rows; j++)
        {
        	if(map[i * cols + j] == H1)
            {
				place_house(img, j, i, H1, wt);
            }
			if(map[i * cols + j] == H2)
            {
				place_house(img, j, i, H2, wt);
            }
			if(map[i * cols + j] == H3)
            {
				place_house(img, j, i, H3, wt);
            }
		}
	}

	SDL_SaveBMP(img, "images/city.bmp");
	
	SDL_FreeSurface(img);
}
