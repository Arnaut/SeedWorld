#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "city_gen.h"



#define ROWS1 200
#define COLS1 200
int map1[400]={0};
/* 
#define ROWS2 2100
#define COLS2 1900
int map2[4000]={0};
  
#define ROWS3 1900
#define COLS3 2100
int map3[4000]={0};
*/
int main()
{
  //build_roads(map1,ROWS1,COLS1);
  //build_roads(map2,ROWS2,COLS2);
  //build_roads(map3,ROWS3,COLS3);
  printf("===========MAP1===========\n");
  for(size_t i=0;i<COLS1;i++)
    {
      for(size_t j=0; j<ROWS1; j++)
	{
	  printf("%i",map1[i*COLS1+j]);
	}
	    printf("\n");
    }
  /*
   printf("===========MAP2===========");
   for(size_t i=0;i<COLS2;i++)
     {
       for(size_t j=0; j<ROWS2; j++)
	 {
	   printf("%i",map2[i*COLS2+j]);
	 }
       printf("\n");
     }
   printf("===========MAP3===========");
   for(size_t i=0;i<COLS3;i++)
     {
       for(size_t j=0; j<ROWS3; j++)
	 {
	   printf("%i",map3[i*COLS3+j]);
	 }
       printf("\n");
     }
  */
   return 0;
}
