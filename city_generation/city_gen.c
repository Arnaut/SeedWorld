#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//needed for find_fields
#define NB_CITIES 5
//size of 1rst city
#define COLS1 2
#define ROWS1 2

//size of 2nd city
#define COLS2 5
#define ROWS2 3


//needed for build roads
#define MIN_LENGTH 50 //min length is equal to the max(width,heigth) of a house or building
#define MAX_LENGTH 4*MIN_LENGTH
#define INTERSECTION 4
#define NB_ROADS 20

//colors
#define YEL  "\x1B[33m"
#define CYA  "\x1B[36m"
#define NRM  "\x1B[0m"
#define GRE  "\x1B[32m"
#define BLE  "\x1B[34m"

int nb_rand(int min, int max)
{
  static int rand_seed=0;
  int c;
  if(min>max)
    {
      c=min;
      min=max;
      max=c;
    }
    if(!rand_seed)
    {
        srand(time(NULL));
        rand_seed=1;
    }
  return (rand()%(max-min+1))+min; //generate a number between min and max include
}

//================================== find the field======================================
int buildable(int* map, int x, int y, int cols,  int height, int width)
{
  int ok =1;
  int j;
  while(x<height && ok)
    {
      j=y;
      while(j<width && ok)
	{
	  if(!map[x*cols+j])//can not be constructible
	    {
	      ok=0;
	    }
	  j++;
	}
      x++;
    }
  return ok;
}
int* find_fields(int* map, int cols, int rows)
{
  int* position_x_y=calloc((NB_CITIES*4),sizeof(int));//table to save the position and size of a city that can be build
  int x=0;
  int y;
  int city1,city2;
  int nb_cities=NB_CITIES;
  int pick_it;
  int final_c;
  int final_r;
  int built=0;
  int i=0;
  while((x<rows)&&(nb_cities>0))
    {
      y=0;
      while((y<cols)&&(nb_cities>0))
	{
	  city1=buildable(map,x,y,cols,x+ROWS1,y+COLS1);
	  city2=buildable(map,x,y,cols,x+ROWS2,y+COLS2);
	  if(city1 && city2)//both city size are possible
	    {
	      pick_it=nb_rand(0,1);//pick a random one
	    }
	  else
	    {
	      if(city1)
		{
		  pick_it=1;
		}
	      else
		{
		  if(city2)
		    {
		      pick_it=0;
		    }
		  else
		    {
		      pick_it=-1;//no cities could fit
		    }
		}
	    }
	  if(pick_it>=0)//a city can be build
	    {
	      if(pick_it)//city1 will be build
		{
		  final_c=COLS1;
		  final_r=ROWS1;
		  map[x*cols+y]=2;
		}
	      else//city2 otherwise
		{
		  final_c=COLS2;
		  final_r=ROWS2;
		  map[x*cols+y]=3;
		}
	      position_x_y[i]=x; //saves the x position
	      position_x_y[i+1]=y; //saves the y position
	      position_x_y[i+2]=final_c; //saves the cols 
	      position_x_y[i+3]=final_r; //saves the rows
	      i+=4;
	      built=1;
	      nb_cities--;
	      y+=final_c*2;//space between cities
	    }
	  else
	    {
	      y++;
	    }
	}
      if(built)
	{
	  x+=final_r*2;//space between cities
	}
      else
	{
	  x++;
	}
    }
  for(int i=0; i<rows;i++)
    {
      for(int j=0; j<cols;j++)
	{
	  if(map[i*cols+j]==2|| map[i*cols+j]==3)
		{
		  printf("%s%i",YEL,map[i*cols+j]);
		  printf("%s",NRM);
		}
	      else
		{
		  if(map[i*cols+j])
		    {
		      printf("%s%i",GRE,map[i*cols+j]);
		      printf("%s",NRM);
		    }
		  else
		    {
		      printf("%s%i",BLE,map[i*cols+j]);
		      printf("%s",NRM);
		    }
		}
	}
      printf("\n");
    }
  printf("\n\n");
  return position_x_y;
}
//================================== build roads=======================================

int define_len(int position, int max, int direction)
{
  int len;
  if(direction)//left or top
    {
      len=nb_rand(position,MIN_LENGTH+1);
    }
  else//right or bot
    {
      len=nb_rand(MIN_LENGTH+1,max-position);
    }
  return len;
}

int define_begin(int position, int direction, int end)
{
  if(direction)//is directed top or left
    {
      if(position-(MIN_LENGTH+1)<end)//out of the road
	{
	  position=nb_rand(position,end);
	}
      else//on the road
	{
	  position=nb_rand(position-(MIN_LENGTH+1),end);
	}
    }
  else//the road is directed bot or right
    {
      if(position+(MIN_LENGTH+1)>end)//out of the road
	{
	  position=nb_rand(position,end);
	}
      else//on the road
	{
	  position=nb_rand(position+(MIN_LENGTH+1),end);
	}
    }
  return position;
}

int cons(int* map, int x, int y, int fixed1, int fixed2, int fixed_i, int fixed_j, int cols, int len)
{
  int ok=1;
  if(map[x*cols+y]==4)
    {
      ok=0;
    }
  else
    {
      if(map[x*cols+y])
	{
	  if ((!map[fixed1*cols+fixed_i])&&(!map[fixed2*cols+fixed_j]))
	    {
	      ok=0;
	    }
	  else
	    {
	      if(len<MIN_LENGTH)
		{
		  ok=0;
		}
	    }
	}
      else
	{
	  if((map[fixed1*cols+fixed_i]>=1)||(map[fixed2*cols+fixed_j]>=1))
	    {
	      if(len<MIN_LENGTH)
		{
		  ok=0;
		}
	      else
		{
		  if(map[x*cols+y]<1)
		    {
		      ok=0;
		    }
		}
	    }
	}
    }
  return ok;
}

int constructible(int*map, int x, int y, int fixed, int cols, int len, int i, int j,  int vertical)
{
  int ok=1;
  int min_len=MIN_LENGTH;
  while(ok && min_len>0)
    {
      if(vertical)
	{
	  ok=cons(map,x,y,fixed,fixed,i,j,cols,len);
	}
      else
	{
	  ok=cons(map,x,y,i,j,fixed,fixed,cols,len);
	}
      i--;
      j++;
      min_len--;
    }
  return ok;
}


int is_constructible(int*map,int x, int y, int len, int cols, int vertical, int direction)
{
  int ok=1;
  int current_len=0;
  if(map[x*cols+y])
    {
      ok=0;
    }
  while(ok && len>0)
    {
      if (vertical)//future road orientation
	{
	  ok=constructible(map, x,y, x, cols,current_len, (y-1), (y+1), vertical);//determine is the road is constructible h
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
	  ok=constructible(map, x,y,y, cols, current_len, (x-1), (x+1), vertical);//determine is the road is constructible h
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


int _dir(int position, int mid)
{
  int final_dir;
  if(position>mid)//if the starting point is nearest to the bot
    {
      final_dir=1;//road's direction : top
    }
  else
    {
      if(position<mid)//if the starting point is nearest to the top
	{
	  final_dir=0;//road's direction : bot
	}
      else
	{
	  final_dir=rand()%2;//random direction
	}
    }
  return final_dir;
}

int define_dir(int x, int y, int cols, int rows, int vertical)
{
  if(vertical)//the road will be vertical
    {
      return _dir(x,rows/2);
      
    }
  else//the road will be horizontal
    {
      return _dir(y,cols/2);
    }
}

int draw_road(int* map, int x, int y, int len, int cols, int rows, int vertical, int direction, int main_road)
{
  int firstx=x;
  int firsty=y;
  int end;
  while(((x>=0) && (x<rows))&& ((y>=0) && (y<cols))&&(len>=0))
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
	      x-=1;
	    }
	  else
	    {
	      x+=1;
	    }
	}
      else //road will be horizontal
	{
	  if(direction)//define road direction 1=left 0=right
	    {
	      y-=1;
	    }
	  else
	    {
	      y+=1;
	    }
	}
      len--;
    }
  if(((firstx>=0) && (firstx<rows))&& ((firsty>=0) && (firsty<cols)) && !main_road)
    {
      map[firstx*cols+firsty]=4;//begin of a subroad
    }
  if(vertical)
    {
      if(direction)//top
	{
	  end= x+1;
	}
      else//bot
	{
	  end=x-1;
	}
    }
  else
    {
      if(direction)//left
	{
	  end=y+1;
	}
      else//right
	{
	  end=y-1;
	}
    }
  return end;
}

void build_roads(int* map, int rows, int cols)
{
  int x=nb_rand(0,rows/2-1);
  int y=nb_rand(0,cols/2-1);
  int nb_roads=NB_ROADS; //sub roads' tot nb
  int vertical=rand()%2;//define road's orientation
  int direction=define_dir(x, y, cols, rows, vertical);//define the road's direction
  int len;
  int test_y;
  int test_x;
  int constructible;
  int end; //end of the road that was created
  
  if(vertical)//define len
    {
      len=define_len(y,(cols-1),direction);
    }
  else
    {
      len=define_len(x,(rows-1),direction);
    }
  end=draw_road(map, x, y, len, cols, rows, vertical, direction,1);//return the end of the road
  
  while(nb_roads>0) //tracing all the secondary roads
    {
      if(vertical)//current road is vertical
	{
	  x=define_begin(x,direction,end);
	}
      else //current road is horizontal
	{
	  y=define_begin(y,direction,end);
	}
      direction=define_dir(x, y, cols, rows, !vertical);//new road orientation will be opp of the current road
      if(vertical)//define len
	{
	  len=define_len(y,(cols-1),direction);
	}
      else
	{
	  len=define_len(x,(rows-1),direction);
	}
      
      test_y=y;
      test_x=x;
      if(vertical)//main road vertical
	{
	  if(direction)//future road direction : left
	    {
	      test_y-=1;
	    }
	  else//right
	    {
	      test_y+=1;
	    }
	}
      else//main road horizontal
	{
	  if(direction)//future road direction: top
	    {
	      test_x-=1;
	    }
	  else//bot
	    {
	      test_x+=1;
	    }
	}
      constructible=is_constructible(map,test_x,test_y,len,cols,!vertical,direction);
      if(constructible)
	{
	  end=draw_road(map,x,y,len,cols,rows,!vertical,direction,0);//creation of the new road road
	}
      else
	{
	  break;
	}
      //orientation of the future road
      nb_roads--;
      vertical=!vertical;
    }
  printf("====================draw the road======================\n");
  for(int i=0; i<rows;i++)
    {
      for(int j=0; j<cols;j++)
	{
	  if(map[i*cols+j]==4)
		{
		  printf("%s%i",CYA,map[i*cols+j]);
		  
		  printf("%s",NRM);
		}
	      else
		{
		  if(map[i*cols+j])
		    {
		      printf("%s1",YEL);
		      printf("%s",NRM);
		    }
		  else
		    {
		      printf("%i",map[i*cols+j]);
		    }
		}
	}
      printf("\n");
    }
  printf("\n\n");
}
