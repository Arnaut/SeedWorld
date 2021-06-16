//Author : Leo Tripier

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "pixel_operations.h"


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
int* gen_img(float* mat, size_t rows, size_t cols, SDL_Surface* img,float min, float max, float* threshold, char* file)
{
  init_sdl();
  Uint32 pixel;

  //Uint8 r, g, b;
  (void)min;
  (void)max;
  int* mat_next = malloc(rows * cols * sizeof(int));

  //img = load_image("to_test.png");

  for(size_t i = 0;i < cols; i++)
    {
      for(size_t j = 0; j < rows; j++)
        {
          if(*(mat + (i * cols + j)) <= *threshold)
            {
              pixel = SDL_MapRGB(img->format, 255, 0, 0);
              *(mat_next + (i*cols + j)) = 0;
              //ocean
            }
          else
            {
              if (*(mat + (i * cols + j)) <= *(threshold + 1))
                {
                  pixel = SDL_MapRGB(img->format, 0, 255, 0);
                  *(mat_next + (i*cols + j)) = 1;
                  //ground
                }
              else
                {
                  pixel = SDL_MapRGB(img->format, 0, 0, 255);
                  *(mat_next + (i*cols + j)) = 2;
                  //mountain
                }
            }

          put_pixel(img, i, j, pixel);
        }
    }

  //display_image(img);

  SDL_SaveBMP(img,file);
  //wait_for_keypressed();

  return mat_next;
}

//Leo Tripier
float* seuil(size_t height, size_t width,float* mat, int ocean, int plains, int mountains)
{

  (void)mountains;

  float* ret = malloc(sizeof(float) * 2);
  long hist[100];
  float a;
  float sum = 0.0;
  for(size_t k = 0;k < 100;k++)
    {
      hist[k] = 0;
    }
  for(size_t i = 0; i < width; i++)
    {
      for(size_t j = 0; j < height; j++)
        {
          a = *(mat + (i * width + j)) * 100;
          hist[(size_t)a] += 1;
        }
    }
  float socean = (float)ocean/100.0;
  float splains = (float)plains/100.0 + socean;
  int ok = 0;

  *ret = 0;
  *(ret + 1) = 0;
  for(size_t l = 0; l < 100 && !ok; l++)
    {
      sum += (float)hist[l];

      if((float)(sum / (height * width)) >= socean && *ret == 0)
        {
          *ret = (float)(l /100.0);
        }
      else if((float)(sum / (height * width)) >= splains && *(ret + 1) == 0)
        {
          *(ret + 1) = (float)(l / 100.0);
          ok = 1;
        }
    }

  return ret;
}

//Leo Tripier
int* gen_biome(int* relief, float* temperature, size_t height, size_t width, SDL_Surface* img,float* threshold,char* file )
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
              if(temp < *threshold)
                {
                  *(biomes + (i * width + j)) = 0;
                  pixel = SDL_MapRGB(img->format, 0, 0, 221);//ocean froid
                }
              else if(temp < *(threshold + 1))
                {
                  *(biomes + (i * width + j)) = 0;
                  pixel = SDL_MapRGB(img->format, 20, 20, 227);//ocean
                }
              else
                {
                  *(biomes + (i * width + j)) = 0;
                  pixel = SDL_MapRGB(img->format, 43, 250, 250);//ocean chaud
                }
            }
          else if(rel == 1)
            {
              if(temp < *threshold)
                {
                  *(biomes + (i * width + j)) = 1;
                  pixel = SDL_MapRGB(img->format, 88, 41, 0);//terre froide
                }
              else if(temp < *(threshold + 1))
                {
                  *(biomes + (i * width + j)) = 1;
                  pixel = SDL_MapRGB(img->format, 52, 189, 60);//terre
                }
              else
                {
                  *(biomes + (i * width + j)) = 1;
                  pixel = SDL_MapRGB(img->format, 224, 205, 169);//désert
                }
            }
          else
            {
              if(temp < *threshold)
                {
                  *(biomes + (i * width + j)) = 0;
                  pixel = SDL_MapRGB(img->format, 255, 250, 250);//montagnes gelées
                }
              else if(temp < *(threshold + 1))
                {
                  *(biomes + (i * width + j)) = 0;
                  pixel = SDL_MapRGB(img->format, 80, 80, 80);//montagnes
                }
              else
                {
                  *(biomes + (i * width + j)) = 0;
                  pixel = SDL_MapRGB(img->format, 195, 10, 30);//volcans
                }
            }

          put_pixel(img, i, j, pixel);
        }
    }


  SDL_SaveBMP(img,file);
  return biomes;
}
