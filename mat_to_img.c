#include "mat_to_img.h"


#define CITY 0
#define ROAD 1
#define INTERSECTION 4

#define H1 7
#define H2 8
#define H3 9


void place_house(SDL_Surface *img, int x, int y, int htype, int wtype)
{
	printf("x=%i  y=%i\n",x,y);
	
	Uint8 r=0,g=0,b=0;

	Uint32 pixel;

	SDL_Surface *house =NULL;

	//house sprite loading

	if(wtype ==1)
	{
		if(htype ==H1) 
			house = SDL_LoadBMP("images/elf1b.bmp");
		else if(htype ==H2) 
			house = SDL_LoadBMP("images/elf2b.bmp");
		else if(htype ==H3) 
			house = SDL_LoadBMP("images/elf3b.bmp");
	}
	else if(wtype == 3)
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
	printf("C=%i  R=%i\n",C,R);	

	Uint8 r1=0,g1=0,b1=0;
	
	Uint32 pixel;

	for(int i=C; i<C+src->w; i++)
	{
		for(int j=R; j<R+src->h; j++)
		{
			Uint32 p = get_pixel(src, i-C, j-R);

			SDL_GetRGB(p, src->format, &r1,&g1,&b1);
			
			if(!(r1==255 && g1==0 && b1==255)) // pastes the pixel only if it's not 255.0.255
			{
				pixel =SDL_MapRGB(dst->format, &r1, &g1, &b1);
			 
				put_pixel(dst, i, j, pixel);
			}
		}
	}
}


void drawName(char *s, int len)
{
	SDL_Surface *img;
	SDL_Surface *letter;

	char *r=NULL;
	char *g=NULL;
	char *b=NULL;
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
	printf("in RGB\n");
	SDL_Surface *img;

	img = SDL_CreateRGBSurface(0, cols, rows, 32, 0, 0, 0, 0);
	
	Uint32 pixel;

	for(int i = 0; i < cols; i++)
    {
		for(int j = 0; j < rows; j++)
        {
			//printf("map (%i,%i)=%i\n",i,j,map[j * cols + i]);
        	if(map[j * cols + i] == ROAD || map[j*cols+i] == INTERSECTION)
            {
              	pixel = SDL_MapRGB(img->format, 84, 84, 84);
            }
			
          	else
            {
              	pixel = SDL_MapRGB(img->format, 255, 0, 255); // set the empty tile to pink
            }

          	put_pixel(img, i, j, pixel);
        }
    }

	for(int i = 0; i < cols; i++)
    {
		for(int j = 0; j < rows; j++)
        {
        	if(map[j * cols + i] == H1)
            {
				place_house(img, i, j, H1, wt);
            }
			if(map[j * cols + i] == H2)
            {
				place_house(img, i, j, H2, wt);
            }
			if(map[j * cols + i] == H3)
            {
				place_house(img, i, j, H3, wt);
            }
		}
	}

	SDL_SaveBMP(img, "images/city.bmp");
	
	SDL_FreeSurface(img);
}
