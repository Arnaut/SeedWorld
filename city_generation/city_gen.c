#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define MIN_LENGTH 6 //min length is equal to the max(width,heigth) of a house or building
#define MAX_LENGTH 4*MIN_LENGTH
#define INTERSECTION 4
#define NB_ROADS 20


#define KYEL  "\x1B[33m"
#define KCYN  "\x1B[36m"
#define KNRM  "\x1B[0m"


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

int define_len(int position, int max, int direction)
{
  int len;
  if(direction)//left or top
    {
      printf("left or top\n");
      printf("position=%i\n",position);
      printf("road value between %i and %i\n",position,MIN_LENGTH+1);
      len=nb_rand(position,MIN_LENGTH+1);
    }
  else//right or bot
    {
      printf("right or bot\n");
      printf("road value between %i and %i\n",max-position,MIN_LENGTH+1);
      len=nb_rand(MIN_LENGTH+1,max-position);
    }
  return len;
}

int define_begin(int position, int direction, int end)
{
  if(direction)//is directed top or left
    {
      printf("direction of main road = top\n");
      if(position-(MIN_LENGTH+1)<end)//out of the road
	{
	  printf("valeur de x entre %i et %i\n",position , end);
	  position=nb_rand(position,end);
	}
      else//on the road
	{
	  printf("waleur de x entre %i et %i\n",position-(MIN_LENGTH+1), end);
	  position=nb_rand(position-(MIN_LENGTH+1),end);
	}
    }
  else//the road is directed bot or right
    {
      printf("direction of the main road = bot\n");
      if(position+(MIN_LENGTH+1)>end)//out of the road
	{
	  printf("waleur de x entre %i et %i\n",position , end);
	  position=nb_rand(position,end);
	}
      else//on the road
	{
	  printf("waleur de x entre %i et %i\n",position+(MIN_LENGTH+1), end);
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
      printf("top\n");
    }
  else
    {
      if(position<mid)//if the starting point is nearest to the top
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
  return final_dir;
}

int define_dir(int x, int y, int cols, int rows, int vertical)
{
  printf("=================define dir=================\n");
  if(vertical)//the road will be vertical
    {
      printf("verti = %i\n",vertical);
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
  printf("====================draw the road======================\n");
  for(int i=0; i<cols;i++)
    {
      for(int j=0; j<rows;j++)
	{
	  if(map[i*cols+j]==4)
		{
		  printf("%s4",KCYN);
		  printf("%s",KNRM);
		}
	      else
		{
		  if(map[i*cols+j])
		    {
		      printf("%s1",KYEL);
		      printf("%s",KNRM);
		    }
		  else
		    {
		      printf("%i",map[i*cols+j]);
		    }
		}
	}
      printf("\n");
    }
  printf("end = %i\n",end);
  printf("=================== end draw road =====================\n");
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
  int end; //end of the road that was created
  
  if(vertical)//define len
    {
      len=define_len(y,(cols-1),direction);
    }
  else
    {
      len=define_len(x,(rows-1),direction);
    }
  printf("main road vertical= %i\n",vertical);
  printf("direction main road = %i\n",direction);
  printf("len =%i\n",len);
  printf("x=%i\n",x);
  printf("y=%i\n",y);
  printf("nb tot road=%i\n",nb_roads);
  end=draw_road(map, x, y, len, cols, rows, vertical, direction,1);//return the end of the road
  printf("end main road= %i\n",end);
  
  while(nb_roads>0) //tracing all the secondary roads
    {
      printf("============= new_road:%i ================\n",nb_roads);
      printf("x = %i\n",x);
      printf("y= %i\n",y);
      if(vertical)//current road is vertical
	{
	  x=define_begin(x,direction,end);
	}
      else //current road is horizontal
	{
	  y=define_begin(y,direction,end);
	}
      printf("new x=%i\n",x);
      printf("new y=%i\n",y);
      direction=define_dir(x, y, cols, rows, !vertical);//new road orientation will be opp of the current road
      printf("================ direction defined ===================\n");
      if(vertical)//define len
	{
	  len=define_len(y,(cols-1),direction);
	}
      else
	{
	  len=define_len(x,(rows-1),direction);
	}
      
      int test_y=y;
      int test_x=x;
      int swap;
      if(vertical)//main road vertical
	{
	  printf("new road is horizontal\n");
	  if(direction)//future road direction : left
	    {
	      printf("I will be left\n");
	      test_y-=1;
	    }
	  else//right
	    {
	      printf("I will be right\n");
	      test_y+=1;
	    }
	}
      else//main road horizontal
	{
	  printf("new road will be vertical\n");
	  if(direction)//future road direction: top
	    {
	      printf("I will be top\n");
	      test_x-=1;
	    }
	  else//bot
	    {
	      printf("i will be bot\n");
	      test_x+=1;
	    }
	}
      swap=map[test_x*cols+test_y];
      map[test_x*cols+test_y]=3;      
      printf("====================placement for testing======================\n");
      for(int i=0; i<cols;i++)
	{
	  for(int j=0; j<rows;j++)
	    {
	      if(map[i*cols+j]==3)
		{
		  printf("%s3",KYEL);
		  printf("%s",KNRM);
		}
	      else
		{
		  if(map[i*cols+j])
		    {
		      printf("%s1",KCYN);
		      printf("%s",KNRM);
		    }
		  else
		    {
		      printf("%i",map[i*cols+j]);
		    }
		}
	    }
	  printf("\n");
	}
      map[test_x*cols+test_y]=swap;
      printf(" begin x = %i\n",x);
      printf("begin y= %i\n",y);
      printf("test_x = %i\n",test_x);
      printf("test_y = %i\n",test_y);
      printf("len = %i\n",len);

      int constructible=is_constructible(map,test_x,test_y,len,cols,!vertical,direction);
      if(constructible)
	{
	  printf("my future road is constructible\n");
	  printf("final x =%i\n",x);
	  printf("final y =%i\n",y);
	  printf("len =%i\n",len);
	  printf("end= %i\n", end);
	      end=draw_road(map,x,y,len,cols,rows,!vertical,direction,0);//creation of the new road road
	}
      else
	{
	  break;
	}
      //orientation of the future road
      printf("future road will be verti=%i",vertical);
      nb_roads--;
      vertical=!vertical;
      printf("\n\n");
    }
}
