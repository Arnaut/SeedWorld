#include <stdlib.h>
#include <stdio.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


#define CITY 0
#define ROAD 1 

#define INTERSECTION 4
#define OCCUPIED 5

#define H1 7 
#define H2 8
#define H3 9


void place_house(int* map, int rows, int cols, int r, int c, int house_type, int house_width, int house_length)
{
	for(int i = c; i< c+house_width; i++)
		for(int j = r; j< r+house_length; j++)
			map[j*cols+i] = OCCUPIED;
	map[r*cols+c] = house_type;

	printf("house of type %i placed on (%i,%i)\n",house_type,c,r);
}


int draw(int *map, int rows, int cols, int c, int r, int house_type, int house_width, int house_length)
{
	for(int i=c; i<c+house_width && i<cols  ; i++)
	{
		for(int j=r; j<r+house_length && j<rows; j++)
		{
			if(map[j*cols+i] != CITY)
			{
				printf("unable to place a house on (%i,%i), tile (%i,%i) of type: %i\n",c,r,i,j, map[j*cols+i]);
				return 0;
			}
		}
	}
	place_house(map, rows, cols, r, c, house_type, house_width, house_length);
	return 1;
}


void draw_house2(int *map, int rows, int cols, int c, int r)
{
	//we desire to place house(s) around the intersection (c,r)

	int ht1 =H1; //house type
	int hw1 =50; //house width
	int hl1 =50; //house length

	int ht2 =H2;
	int hw2 =50;
	int hl2 =10;

	int ht3 =H3;
	int hw3 =50;
	int hl3 =50;


	//up left: (c-hw,r-hl)
	if(c-hw1>=0 && r-hl1>=0) //if h1 fits
		draw(map,rows, cols, c-hw1, r-hl1, ht1, hw1, hl1);

	if(c-hw2>=0 && r-hl2>=0) //if h2 fits
		draw(map,rows, cols, c-hw2, r-hl2, ht2, hw2, hl2);
	
	if(c-hw3>=0 && r-hl3>=0) //if h3 fits		
		draw(map,rows, cols, c-hw3, r-hl3, ht3, hw3, hl3);

	
	//up right: (c+1,r-hl)
	if(c+1>=0 && c+1+hw1<cols && r-hl1>=0)
		draw(map,rows, cols, c+1, r-hl1, ht1, hw1, hl1);

	if(c+1>=0 && c+1+hw2<cols && r-hl2>=0)
		draw(map,rows, cols, c+1, r-hl2, ht2, hw2, hl2);

	if(c+1>=0 && c+1+hw3<cols && r-hl3>=0)
		draw(map,rows, cols, c+1, r-hl3, ht3, hw3, hl3);


	//down left: (c-hw,r+1)
	if(c-hw1>=0 && r+1>=0 && r+1+hl1<rows) //if the house fits
		draw(map,rows, cols, c-hw1, r+1, ht1, hw1, hl1);

	if(c-hw2>=0 && r+1>=0 && r+1+hl2<rows) //if the house fits
		draw(map,rows, cols, c-hw2, r+1, ht2, hw2, hl2);

	if(c-hw3>=0 && r+1>=0 && r+1+hl3<rows) //if the house fits
		draw(map,rows, cols, c-hw3, r+1, ht3, hw3, hl3);


	//down rigth: (c+1,r+1) 
	if(c+1>=0 && r+1>=0 && c+1+hw1<cols && r+1+hl1<rows) //if the house fits
		draw(map,rows, cols, c+1, r+1, ht1, hw1, hl1);

	if(c+1>=0 && r+1>=0 && c+1+hw2<cols && r+1+hl2<rows) //if the house fits
		draw(map,rows, cols, c+1, r+1, ht2, hw2, hl2);

	if(c+1>=0 && r+1>=0 && c+1+hw3<cols && r+1+hl3<rows) //if the house fits
		draw(map,rows, cols, c+1, r+1, ht3, hw3, hl3);

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

				printf("inter find on (%i,%i)\n",j,i);
			}
		}
	}
}
