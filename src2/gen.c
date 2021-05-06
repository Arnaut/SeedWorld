//Author : Leo Tripier

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"
#include "pixel_operations.c"

void init_sdl()
{
  // Init only the video part.
  // If it fails, die with an error message.
  if(SDL_Init(SDL_INIT_VIDEO) == -1)
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
}

SDL_Surface* load_image(char *path)
{
  SDL_Surface *img;

  // Load an image using SDL_image with format detection.
  // If it fails, die with an error message.
  img = IMG_Load(path);
  if (!img)
    errx(3, "can't load %s: %s", path, IMG_GetError());

  return img;
}

SDL_Surface* display_image(SDL_Surface *img)
{
  SDL_Surface *screen;

  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if (screen == NULL)
    {
      // error management
      errx(1, "Couldn't set %dx%d video mode: %s\n",
           img->w, img->h, SDL_GetError());
    }

  // Blit onto the screen surface
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());

  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);

  // return the screen for further uses
  return screen;
}

void wait_for_keypressed()
{
  SDL_Event event;

  // Wait for a key to be down.
  do
    {
      SDL_PollEvent(&event);
    } while(event.type != SDL_KEYDOWN);

  // Wait for a key to be up.
  do
    {
      SDL_PollEvent(&event);
    } while(event.type != SDL_KEYUP);
}

/*double ecart_type(size_t width, size_t height, float min, float max)
{
  
}*/

//Leo Tripier
int* gen_img(float* mat, size_t rows, size_t cols, SDL_Surface* img, float ocean_ratio, float min, float max)
{
  init_sdl();
  Uint32 pixel;

  //Uint8 r, g, b;

  (void)ocean_ratio;
  (void)min;
  (void)max;
  int* mat_next = malloc(rows * cols * sizeof(int));

  //img = load_image("to_test.png");

  for(size_t i = 0;i < cols; i++)
    {
      for(size_t j = 0; j < rows; j++)
        {
          if(*(mat + (i * cols + j)) < (float)0.33/*(float)((max - min) * ocean_ratio + min)*/)
            {
              pixel = SDL_MapRGB(img->format, 9, 28, 87);
              *(mat_next + (i*cols + j)) = 0;
              //ocean
            }
          else
            {
              if (*(mat + (i * cols + j)) < (float)0.66 /*(float)((max - min) * (ocean_ratio + 0.33) + min)*/)
                {
                  pixel = SDL_MapRGB(img->format, 58, 153, 68);
                  *(mat_next + (i*cols + j)) = 1;
                  //ground
                }
              else
                {
                  pixel = SDL_MapRGB(img->format, 175, 175, 175);
                  *(mat_next + (i*cols + j)) = 2;
                  //mountain
                }
            }

          put_pixel(img, i, j, pixel);
        }
    }

  //display_image(img);

  SDL_SaveBMP(img,"tested.bmp");
  //wait_for_keypressed();

  return mat_next;
}

//Leo Tripier
int* gen_biome(int* relief, float* temperature, size_t height, size_t width, SDL_Surface* img)
{
  init_sdl();
  Uint32 pixel;
  int rel;
  float temp;

  int* biomes = malloc(height * width * sizeof(int));

  for(size_t i = 0; i < width; i++)
    {
      for(size_t j = 0; j < height; j++)
        {
          rel = *(relief + (i * width + j));
          temp = *(temperature + (i * width + j));
          if(rel == 0)
            {
              if(temp < 0.34)
                {
                  *(biomes + (i * width + j)) = 1;
                  pixel = SDL_MapRGB(img->format, 221, 79, 4);
                }
              else if(temp < 0.67)
                {
                  *(biomes + (i * width + j)) = 2;
                  pixel = SDL_MapRGB(img->format, 221, 181, 4);
                }
              else
                {
                  *(biomes + (i * width + j)) = 3;
                  pixel = SDL_MapRGB(img->format, 63, 221, 4);
                }
            }
          else if(rel == 1)
            {
              if(temp < 0.34)
                {
                  *(biomes + (i * width + j)) = 4;
                  pixel = SDL_MapRGB(img->format, 4, 221, 165);
                }
              else if(temp < 0.67)
                {
                  *(biomes + (i * width + j)) = 5;
                  pixel = SDL_MapRGB(img->format, 4, 99, 221);
                }
              else
                {
                  *(biomes + (i * width + j)) = 6;
                  pixel = SDL_MapRGB(img->format, 122, 84, 180);
                }
            }
          else
            {
              if(temp < 0.34)
                {
                  *(biomes + (i * width + j)) = 7;
                  pixel = SDL_MapRGB(img->format, 239, 16, 181);
                }
              else if(temp < 0.67)
                {
                  *(biomes + (i * width + j)) = 8;
                  pixel = SDL_MapRGB(img->format, 6, 0, 1);
                }
              else
                {
                  *(biomes + (i * width + j)) = 9;
                  pixel = SDL_MapRGB(img->format, 245, 239, 240);
                }
            }

          put_pixel(img, i, j, pixel);
        }
    }

  display_image(img);
  wait_for_keypressed();

  return biomes;
}
