#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "roads_gen.h"



#define CITY 0
#define ROAD 1 

#define INTERSECTION 4
#define OCCUPIED 5

#define H1 7 
#define H2 8
#define H3 9


void placeHouse(int* map, int rows, int cols, int r, int c, int house_type, int house_width, int house_length)
{
	for(int i = c; i< c+house_width; i++)
		for(int j = r; j< r+house_length; j++)
			map[j*cols+i] = OCCUPIED;
	map[r*cols+c] = house_type;

}


int draw(int *map, int rows, int cols, int c, int r, int house_type, int house_width, int house_length)
{
	for(int i=c; i<c+house_width && i<cols  ; i++)
	{
		for(int j=r; j<r+house_length && j<rows; j++)
		{
			if(map[j*cols+i] != CITY)
			{
				return 0;
			}
		}
	}
	placeHouse(map, rows, cols, r, c, house_type, house_width, house_length);
	return 1;
}


void draw_house2(int *map, int rows, int cols, int c, int r)
{
	//we desire to place house(s) around the intersection (c,r)


	int ht =nb_rand(7,9); //house type
	int hw =50; //house width
	int hl =50; //house length


	//up left: (c-hw,r-hl)
	if(c-hw>=0 && r-hl>=0) //if h1 fits
		draw(map,rows, cols, c-hw, r-hl, ht, hw, hl);

	//up right: (c+1,r-hl)
	if(c+1>=0 && c+1+hw<cols && r-hl>=0)
		draw(map,rows, cols, c+1, r-hl, ht, hw, hl);

	//down left: (c-hw,r+1)
	if(c-hw>=0 && r+1>=0 && r+1+hl<rows) //if the house fits
		draw(map,rows, cols, c-hw, r+1, ht, hw, hl);

	//down rigth: (c+1,r+1) 
	if(c+1>=0 && r+1>=0 && c+1+hw<cols && r+1+hl<rows) //if the house fits
		draw(map,rows, cols, c+1, r+1, ht, hw, hl);
}


void find_inter(int* map, int rows, int cols)
{
	for(int i =0; i<rows;i++)
	{
		for(int j = 0; j<cols; j++)
		{
			if(map[i*cols+j] == INTERSECTION)
			{
				draw_house2(map, rows, cols, j, i);

			}
		}
	}
}
