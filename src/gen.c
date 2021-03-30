#include <err.h>
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

int* gen_img(float* mat, size_t rows, size_t cols, SDL_Surface* img)
{
  init_sdl();
  Uint32 pixel;

  //Uint8 r, g, b;

  int* mat_next = malloc(rows * cols * sizeof(int));

  //img = load_image("to_test.png");

  for(size_t i = 0;i < cols; i++)
    {
      for(size_t j = 0; j < rows; j++)
        {
          if(*(mat + (i * cols + j)) < (float)1.0)
            {
              pixel = SDL_MapRGB(img->format, 46, 139, 87);
              *(mat_next + (i*cols + j)) = 0;
              //ocean
            }
          else if (*(mat + (i * cols + j)) < (float)2.0)
            {
              pixel = SDL_MapRGB(img->format, 224, 205, 169);
              *(mat_next + (i*cols + j)) = 1;
              //sand
            }
          else
            {
              pixel = SDL_MapRGB(img->format, 124, 252, 0);
              *(mat_next + (i*cols + j)) = 2;
              //ground
            }

          put_pixel(img, i, j, pixel);
        }
    }

  display_image(img);

  wait_for_keypressed();
  
  //SDL_Quit;
  return mat_next;
}
