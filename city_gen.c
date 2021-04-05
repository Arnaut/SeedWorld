#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MIN_LENGTH=48; //min length is equal to the max(width,heigth) of a house or building
#define MAX_LENGTH=2*MIN_LENGTH;

int nb_rand(int min, int max)
{
  int nb=0;
  srand(time(NULL));
  nb=(rand()%(max+1-min))+min;
  return nb;
}

void draw_road(int* map, int x, int r_size, int cols, int rows, int vertical)
{
  int y =x;
  while(x>0 & x<cols & y>0 & y<rows & y>0)
    {
      *(map[x*cols+y])+=1;
      if(vertical) //if the main road is vertical then the sub roads will be horizontal
	{
	  if(rand()%2) //define road direction 1= left, 0=right
	    {
	      y--;
	    }
	  else
	    {
	      y++;
	    }
	}
      else //if the main road is horizontal
	{
	  if(rand()%2)
	    {
	      x--;
	    }
	  else
	    {
	      x++;
	    }
	}
      size--;
    }
}

void build_roads(int* map, int rows, int cols)
{
  int x=nb_rand(;
  int r_size= nb_rand(cols-(cols/4), cols);
  int nb_roads=(cols+row)/20; //total numbers of sub roads
  int vertical=random()%2;
  
  if(vertical) //tracing the main road
    {
      draw_road(map, cols/2, r_size, vertical);
    }
  else
    {
      draw_road(map, cols/2, r_size, vertical);
    }
  
  while(nb_roads>0) //tracing all the secondary roads
    {
      vertical=random()%2;
      if(vertical)
	{
	  draw_road(map, MIN_LENGTH, MAX_LENGTH, vertical);
	}
      else
	{
	  draw_road(map, MIN_LENGTH, MAX_LENGTH, vertical);
	}
      nb_roads--;
    }
}
