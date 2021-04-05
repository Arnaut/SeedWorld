#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MIN_LENGTH 48 //min length is equal to the max(width,heigth) of a house or building
#define MAX_LENGTH 2*MIN_LENGTH

int nb_rand(int min, int max)
{
  int nb=0;
  srand(time(NULL));
  nb=(rand()%(max+1-min))+min; //generate a number between min and max include
  return nb;
}

void draw_road(int* map, int x, int r_size, int cols, int rows, int vertical)
{
  int y =x;
  while(((x>0) & (x<cols))& ((y>0) & (y<rows)))
    {
      map[x*cols+y]+=1;
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
      r_size--;
    }
}

void build_roads(int* map, int rows, int cols)
{
  int len=cols+rows;
  int x=nb_rand(len/2,len);
  int begin=x;
  int end=0;
  int nb_roads=(rows+cols)/20; //total numbers of sub roads
  int vertical=random()%2;
  
  if(vertical) //tracing the main road
    {
      draw_road(map, x, len/2, cols, rows, vertical);
    }
  else
    {
      draw_road(map, x, len/2, cols, rows, vertical);
    }
  
  while(nb_roads>0) //tracing all the secondary roads
    {
      begin=x;
      vertical=random()%2;
      len=nb_rand(MIN_LENGTH,MAX_LENGTH);
      end=x+len;
      if(vertical)
	{
	  draw_road(map, x,len, cols, rows,vertical);
	}
      else
	{
	  draw_road(map, x,len, cols, rows,vertical);
	}
      x=nb_rand(begin,end);
      nb_roads--;
    }
}
