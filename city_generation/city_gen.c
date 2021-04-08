#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MIN_LENGTH 6 //min length is equal to the max(width,heigth) of a house or building
#define MAX_LENGTH 4*MIN_LENGTH
#define NB_ROADS 20


int nb_rand(int min, int max)
{
  int nb=0;
  int c;
  if(min>max)
    {
      c=min;
      min=max;
      max=c;
    }
  srand(time(NULL));
  nb=(rand()%(max+1-min))+min; //generate a number between min and max include
  return nb;
}

int define_dir(int x, int y, int cols, int rows, int vertical)
{
  printf("=================define dir=================\n");
  int final_dir;
  if(vertical)//the road will be vertical
    {
      printf("verti = %i\n",vertical);
      if(x-MIN_LENGTH>0&&x+MIN_LENGTH<rows)//if the road has the possibility to go up and down
	{
	  final_dir=rand()%2;//random direction
	  printf("all possible\n");
	}
      else
	{
	  if(x-MIN_LENGTH<0)//road is out of the map if it goes top
	    {
	      final_dir=0;//road's direction : bot
	      printf("bot\n");
	    }
	  else
	    {
	      final_dir=1;//road's direction: top
	      printf("top\n");
	    }
	}
    }
  else//the road will be horizontal
    {
      if(y-MIN_LENGTH>0&&y+MIN_LENGTH<cols)//if the road has the possibility to go left and right
	{
	  final_dir=rand()%2;//the road direction will be left or right
	  printf("all possible\n");
	}
      else
	{
	  if(y-MIN_LENGTH<0)//road is out of the map if it goes left
	    {
	      final_dir=0;//road's direction : right
	      printf("right\n");
	    }
	  else
	    {
	      final_dir=1;//road's direction: left
	      printf("left\n");
	    }
	}
    }
  return final_dir;
}

int draw_road(int* map, int x, int y, int r_size, int cols, int rows, int vertical, int direction)
{
  int firstx=x;
  int firsty=y;
  int end;
  while(((x>=0) && (x<rows))&& ((y>=0) && (y<cols))&&(r_size>0))
    { 
      map[x*cols+y]=1;
      if(vertical) //road will be vertical
	{
	  if(direction) //define road direction 1= top, 0=bot
	    {
	      x--;
	    }
	  else
	    {
	      x++;
	    }
	}
      else //road will be horizontal
	{
	  if(direction)//define road direction 1=left 0=right
	    {
	      y--;
	    }
	  else
	    {
	      y++;
	    }
	}
      r_size--;
    }
  if(((firstx>=0) && (firstx<rows))&& ((firsty>=0) && (firsty<cols)))
    {
      map[firstx*cols+firsty]=6;//detects an intersection
    }
  if(vertical)
    {
      if(x<0)
	{
	  end=0;
	}
      else
	{
	  if(x>=rows)
	    {
	      end=rows-1;
	    }
	  else
	    {
	      end=x;
	    }
	}
    }
  else
    {
       if(y<0)
	{
	  end=0;
	}
      else
	{
	  if(y>=cols)
	    {
	      end=cols-1;
	    }
	  else
	    {
	      end=y;
	    }
	}
    }
  return end;
}

void build_roads(int* map, int rows, int cols)
{
  int x=nb_rand(0,rows/2-1);
  int y=nb_rand(0,cols/2-1);
  int len=nb_rand(cols*rows/2,cols*rows)-1;;//lroad's length
  int nb_roads=NB_ROADS; //sub roads' tot nb
  int vertical=rand()%2;//define road's orientation
  printf("main road vertical= %i\n",vertical);
  int direction=define_dir(x, y, cols, rows, vertical);//define the road's direction
  printf("direction main road = %i\n",direction);
    
  printf("x=%i\n",x);
  printf("y=%i\n",y);
  int end; //end of the road that was created


  printf("nb tot road=%i\n",nb_roads);
  end=draw_road(map, x, y, len/2, cols, rows, vertical, direction);//return the end of the road
  printf("end main road= %i\n",end);
  printf("MAIN ROAD\n");
       for(int i=0; i<cols;i++)
	{
	  for(int j=0; j<rows;j++)
	    {
	      printf("%i",map[i*cols+j]);
	    }
	  printf("\n");
	  }
       printf("\n\n");
  while(nb_roads>0) //tracing all the secondary roads
    {
      printf("=============nb_roads: %i================\n",nb_roads);
      printf("x = %i\n",x);
      printf("y= %i\n",y);
      len=nb_rand(MIN_LENGTH,MAX_LENGTH)-1;
      printf("length road=%i\n",len);
      if(vertical)//current road is vertical
	{
	  if(direction)//is directed top
	    {
	      printf("direction of main road = top\n");
	      if(x-MIN_LENGTH<end)//out of the road
		{
		  printf("waleur de x entre %i et %i\n",x , end);
		  x=nb_rand(x,end);
		}
	      else//on the road
		{
		  printf("waleur de x entre %i et %i\n",x-MIN_LENGTH , end);
		  x=nb_rand(x-MIN_LENGTH,end);
		}
	    }
	  else//the road is directed bot
	    {
	      printf("direction of the main road = bot\n");
	      if(x+MIN_LENGTH>end)//out of the road
		{
		  printf("waleur de x entre %i et %i\n",x , end);
		  x=nb_rand(x,end);
		}
	      else//on the road
		{
		  printf("waleur de x entre %i et %i\n",x+MIN_LENGTH , end);
		  x=nb_rand(x+MIN_LENGTH,end);
		}
	    }
	}
      else //current road is horizontal
	{
	   if(direction)//is directed left
	    {
	      printf("direction of the main road = left\n");
	      if(y-MIN_LENGTH<end)//out of the road
		{
		  printf("waleur de y entre %i et %i\n",y , end);
		  y=nb_rand(y,end);
		}
	      else//on the road
		{
		  printf("waleur de y entre %i et %i\n",y-MIN_LENGTH , end);
		  y=nb_rand(y-MIN_LENGTH,end);
		}
	    }
	   else//is directed right
	    {
	      printf("direction of the main road = right\n");
	       if(y+MIN_LENGTH>end)//out of the road
		{
		  printf("waleur de y entre %i et %i\n",y , end);
		  y=nb_rand(y,end);
		}
	      else//on the road
		{
		  printf("waleur de y entre %i et %i\n",y+MIN_LENGTH , end);
		  y=nb_rand(y+MIN_LENGTH,end);
		}
	    }
	}
      printf("x=%i\n",x);
      printf("y=%i\n",y);
      direction=define_dir(x, y, cols, rows, !vertical);//new road orientation will be opp of the current road
      end=draw_road(map,x,y,len,cols,rows,!vertical,direction);//creation of the new road road
      printf("end = %i\n",end);

      //orientation of hte future road
      printf("future road will be verti=%i",vertical);
      nb_roads--;
      vertical=!vertical;
      printf("\n\n");
      printf("====================draw the road======================\n");
      for(int i=0; i<cols;i++)
	{
	  for(int j=0; j<rows;j++)
	    {
	      printf("%i",map[i*cols+j]);
	    }
		printf("\n");
	  }
    }
}
