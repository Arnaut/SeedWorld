#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MIN_LENGTH 6 //min length is equal to the max(width,heigth) of a house or building
#define MAX_LENGTH 4*MIN_LENGTH
#define INTERSECTION 4
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

int constructible(int*map, int fixed, int cols, int len, int i, int j, int max_pos, int vertical)
{
  int ok=1;
  int min_len=MIN_LENGTH;
  while(ok && min_len>0)
    {
      if(i-MIN_LENGTH>=0)
	{
	  if(vertical)
	    {
	      if(map[fixed*cols+i]==1 && len<MIN_LENGTH)
		{
		  ok=0;
		}
	    }
	  else
	    {
	      if(map[i*cols+fixed]==1 && len<MIN_LENGTH)
		{
		  ok=0;
		}
	    }
	}
      if(j+MIN_LENGTH<max_pos)
	{
	  if (vertical)
	    {
	      if(map[fixed*cols+j]==1 && len<MIN_LENGTH)
		{
		  ok=0;
		}
	    }
	  else
	    {
	      if(map[j*cols+fixed]==1 && len<MIN_LENGTH)
		{
		  ok=0;
		}
	    }
	}
      i--;
      j++;
      min_len--;
    }
  return ok;
}


int is_constructible(int*map,int x, int y, int len, int cols, int rows, int vertical, int direction)
{
  int ok=1;
  int current_len=0;
  while(ok && len>0)
    {
      if (vertical)//future road orientation
	{
	  ok=constructible(map, x, cols,current_len, (y-1), (y+1), cols, vertical);//determine is the road is constructible h
	  if(direction)//top
	    {
	      x--;
	    }
	  else
	    {
	      x++;
	    }
	}
      else
	{
	  ok=constructible(map, y, cols, current_len, (x-1), (x+1), rows, vertical);//determine is the road is constructible h
	  if(direction)//left
	    {
	      y--;
	    }
	  else
	    {
	      y++;
	    }
	}
      current_len++;
      len--;
    }
  return len==0;
}



int define_dir(int x, int y, int cols, int rows, int vertical)
{
  printf("=================define dir=================\n");
  int final_dir;
  int mid;
  if(vertical)//the road will be vertical
    {
      mid=rows/2;
      printf("verti = %i\n",vertical);
      if(x>mid)//if the starting point is nearest to the bot
	{
	  final_dir=1;//road's direction : top
	  printf("top\n");
	}
      else
	{
	  if(x<mid)//if the starting point is nearest to the top
	    {
	      final_dir=0;//road's direction : bot
	      printf("bot\n");
	    }
	  else
	    {
	      final_dir=rand()%2;//random direction
	      printf("all possible\n");
	    }
	}
    }
  else//the road will be horizontal
    {
      mid=cols/2;
      if(y>mid)
	{
	  final_dir=1;
	  printf("left\n");
	}
      else
	{
	  if(y<mid)
	    {
	      final_dir=0;//road's direction : right
	      printf("right\n");
	    }
	  else
	    {
	      final_dir=rand()%2;//the road direction will be left or right
	      printf("all possible\n");
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
      if(map[x*cols+y])
	{
	  map[x*cols+y]=INTERSECTION;
	}
      else
	{
	  map[x*cols+y]=1;
	}
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
      map[firstx*cols+firsty]=2;//begin of a road
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
  printf("====================draw the road======================\n");
  for(int i=0; i<cols;i++)
    {
      for(int j=0; j<rows;j++)
	{
	  printf("%i",map[i*cols+j]);
	}
      printf("\n");
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
      printf("=============sub_roads: %i================\n",nb_roads);
      printf("x = %i\n",x);
      printf("y= %i\n",y);
      if(vertical)//current road is vertical
	{
	  if(direction)//is directed top
	    {
	      printf("direction of main road = top\n");
	      if(x-MIN_LENGTH<end)//out of the road
		{
		  printf("valeur de x entre %i et %i\n",x , end);
		  x=nb_rand(x,end);
		}
	      else//on the road
		{
		  printf("waleur de x entre %i et %i\n",x-MIN_LENGTH , end);
		  x=nb_rand(x-MIN_LENGTH,end);
		}
	       len=nb_rand(MIN_LENGTH,end);
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
	       len=nb_rand(MIN_LENGTH,end);
	    }
	}
      else //current road is horizontal
	{
	   if(direction)//is directed left
	    {
	      printf("direction of the main road = left\n");
	      if(y-MIN_LENGTH<end)//out of the road
		{
		  printf("valeur de y entre %i et %i\n",y , end);
		  y=nb_rand(y,end);
		}
	      else//on the road
		{
		  printf("valeur de y entre %i et %i\n",y-MIN_LENGTH , end);
		  y=nb_rand(y-MIN_LENGTH,end);
		}
	       len=nb_rand(MIN_LENGTH,end);
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
	       len=nb_rand(MIN_LENGTH,MAX_LENGTH);//len of the future road if main road is horizontal
	    }
	}
      printf("new x=%i\n",x);
      printf("new y=%i\n",y);
      direction=define_dir(x, y, cols, rows, !vertical);//new road orientation will be opp of the current road
      printf("length road=%i\n",len);
      int test_y=y;
      int test_x=x;
      int swap;
      if(vertical)//main road vertical
	{
	  printf("new road is horizontal\n");
	  if(direction)//future road direction : left
	    {
	      test_y-=1;
	    }
	  else//right
	    {
	      test_y+=1;
	    }
	  swap=map[test_x*cols+test_y];
	  map[test_x*cols+test_y]=3;      
	  printf("====================placement for testing======================\n");
	  for(int i=0; i<cols;i++)
	    {
	      for(int j=0; j<rows;j++)
		{
	      printf("%i",map[i*cols+j]);
		}
	      printf("\n");
	    }
	  map[test_x*cols+test_y]=swap;
	}
      else//main road horizontal
	{
	  printf("new road will be vertical\n");
	  if(direction)//future road direction: top
	    {
	      test_x-=1;
	    }
	  else//bot
	    {
	      test_x+=1;
	    }
	  swap=map[test_x*cols+test_y];
	  map[test_x*cols+test_y]=3;      
	  printf("====================placement for testing======================\n");
	  for(int i=0; i<cols;i++)
	    {
	      for(int j=0; j<rows;j++)
		{
		  printf("%i",map[i*cols+j]);
		}
	      printf("\n");
	    }
	  map[test_x*cols+test_y]=swap;
	}
      
      printf("test_x = %i\n",test_x);
      printf("test_y = %i\n",test_y);
      
      int constructible=is_constructible(map,test_x,test_y,(len-1),cols,rows,!vertical,direction);
      if(constructible)
	{
	  printf("my future road is constructible\n");
	  end=draw_road(map,x,y,(len+1),cols,rows,!vertical,direction);//creation of the new road road
	}
      else
	{
	  //int found= find_way(map,x,y,end,cols,rows,!vertical,direction
	  break;
	}
      printf("end = %i\n",end);

      //orientation of hte future road
      printf("future road will be verti=%i",vertical);
      nb_roads--;
      vertical=!vertical;
      printf("\n\n");
    }
}