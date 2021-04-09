#include <stdlib.h>
#include <time.h>
#include <stdio.h>


#define CITY 0
#define ROAD 1 
#define HOUSE1 6 
#define HOUSE2 5
#define HOUSE3 4
#define STRUCTURE 2
#define INTERSECTION 3
#define HOUSE_WIDTH1 6
#define HOUSE_LENGTH1 6
#define HOUSE_WIDTH2 5
#define HOUSE_LENGTH2 5
#define HOUSE_WIDTH3 4
#define HOUSE_LENGTH3 4
#define MAX_ROAD_LENGTH 8
#define MIN_ROAD_LENGTH 8

/*
int controlled_random(int lower, int upper)
{
	srand(time(NULL));
	return (rand() % (upper-lower+1)) +lower;
}


int* create_map(size_t len)
{
	int *res_map = malloc(sizeof(int)*len*len);
	
	for(int i=0; i<len; i++)
		for(int j=0; j<len; j++)
			res_map[i*len+j] = CITY;

	return res_map;
}


void create_road(int* map, size_t len)
{
	int roadNumber = len/20; //ratio largeur/20 ex: 3r secondaires pour 50px
	int firstRoad =rand()%2;
	
	if(firstRoad)
	{
		trace_road(map, (len/2)*len, (len/2)*len+len); //first horizontal line
	}
	else
	{
		trace_road(map, len/2, len*len +(len/2)); //first vertical line
	}

	while(roadNumber>0)
	{
		int inter = controlled_random(HOUSE_SIZE, len-HOUSE_SIZE);
		int rOrientation = rand()%2;
		int roadLenght = controlled_random(MIN_ROAD_LENGTH, MAX_ROAD_LENGTH);
		
		if(firstRoad) //if main road is horizontal
		{
			if(rOrientation) // oriented up
			{
				trace_road(map, (len/2)*len + inter, ((len/2)-roadLength)*len + inter);
			}
			else // oriented down
			{
				trace_road(map, (len/2)*len + inter, ((len/2)+roadLength)*len + inter);
			}
		}
		else // if main road is vertical
		{
			if(rOrientation) // oriented right
			{
				trace_road(map, (inter)*len + len/2, (inter)*len + (len/2) + roadLength);
			}
			else // oriented left
			{
				trace_road(map, (len/2)*len + inter, (inter)*len + (len/2) - roadLength);
			}		
		}
		roadNumber--;
	}
}
*/


void draw_house(int* map, size_t len, int x, int y)
{
	//scanning in four times: up-left, up-right, down-left, down-right
	size_t width;
	size_t length;

	int i;
	int j;

	int valid;

	//up-left:
	width = HOUSE_WIDTH1;
	length = HOUSE_LENGTH1;


	for(int k=0; k<3; k++) //test for each house size
	{
		if(x-HOUSE_WIDTH3<0 || y-HOUSE_LENGTH3<0) // if the tiniest house dosen't fit
		{
			valid = 0;
			break;
		}

		valid = 1;
		i = y-length-1;
		while(i<y)
		{
			if(i<0)
			{
				valid = 0;
				break;
			}

			j = x-width-1;
			if(j<0) 
			{
				valid = 0;
				break;
			}

			while(j<x && valid)
			{
				if(map[i*len+j] != CITY)
					valid = 0;
				j++;
			}
			i++;
		}

		if(!valid)
		{
			if(width == HOUSE_WIDTH1)
			{
				width = HOUSE_WIDTH2;
				length = HOUSE_LENGTH2;
				valid = 1;
			}
			if(width == HOUSE_WIDTH2)
			{
				width = HOUSE_WIDTH3;
				length = HOUSE_LENGTH3;
				valid = 1;
			}
			else // no area available for all sizes
				break;
		}
		if(valid) // a zone has been found
			break;

	}

	if(valid)
	{		
		printf("intersection: (%i,%i), house placed at: (%li,%li) ul\n", x, y, x-width, y-length);
		if(width == HOUSE_WIDTH1)
			map[(y-length)*len+x-width] = HOUSE1;
		else if(width == HOUSE_WIDTH2)
			map[(y-length)*len+x-width] = HOUSE2;
		else
			map[(y-length)*len+x-width] = HOUSE3;
	}

	//up-right:
	width = HOUSE_WIDTH1;
	length = HOUSE_LENGTH1;


	for(int k=0; k<3; k++)
	{
		if(x+HOUSE_WIDTH3>len || y-HOUSE_LENGTH3<0)
		{	
			valid = 0;
			break;
		}

		valid = 1;
		i = y-length-1;
		while(i<y)	
		{		
			if(i<0)
			{
				valid = 0;
				break;
			}

			j = x+1;

			while(j<x+width && j<len && valid)
			{
				if(map[i*len+j] != CITY)
					valid = 0;
				j++;
			}
			i++;
		}

		if(!valid)
		{
			if(width == HOUSE_WIDTH1)
			{
				width = HOUSE_WIDTH2;
				length = HOUSE_LENGTH2;
				valid = 1;
			}
			if(width == HOUSE_WIDTH2)
			{
				width = HOUSE_WIDTH3;
				length = HOUSE_LENGTH3;
				valid = 1;
			}
			else // no area available for all sizes
				break;
		}
		
		if(valid) // a zone has been found
			break;

	}

	if(valid)
	{
		printf("intersection:(%i,%i), house placed at: (%li,%li) ur\n", x, y, x+1, y-length);
		if(width == HOUSE_WIDTH1)
			map[(y-length)*len+x+1] = HOUSE1;
		else if(width == HOUSE_WIDTH2)
			map[(y-length)*len+x+1] = HOUSE2;
		else
			map[(y-length)*len+x+1] = HOUSE3;
	}
	
	//down-left:
	width = HOUSE_WIDTH1;
	length = HOUSE_LENGTH1;


	for(int k=0; k<3; k++)
	{
		if(x-HOUSE_WIDTH3<0 || y+HOUSE_LENGTH3>len)
		{
			valid = 0;
			break;
		}

		valid = 1;
		i = y+1;

		while(i<y+length && i<len)
		{
			j = x-width-1;
			if(j<0)
			{
				valid = 0;
				break;
			}

			while(j<x && valid)
			{
				if(map[i*len+j] != CITY)
					valid = 0;
				j++;
			}
			i++;
		}

		if(!valid)
		{
			if(width == HOUSE_WIDTH1)
			{
				width = HOUSE_WIDTH2;
				length = HOUSE_LENGTH2;
				valid = 1;
			}
			if(width == HOUSE_WIDTH2)
			{
				width = HOUSE_WIDTH3;
				length = HOUSE_LENGTH3;
				valid = 1;
			}
			else // no area available for all sizes
				break;
		}
		if(valid) // a zone has been found
			break;
	}

	if(valid)
	{		
		printf("intersection:(%i,%i), house placed at: (%li,%li) dl\n", x, y, x-width, y+1);
		if(width == HOUSE_WIDTH1)
			map[(y+1)*len+x-width] = HOUSE1;
		else if(width == HOUSE_WIDTH2)
			map[(y+1)*len+x-width] = HOUSE2;
		else
			map[(y+1)*len+x-width] = HOUSE3;
	}

	//down-right:
	width = HOUSE_WIDTH1;
	length = HOUSE_LENGTH1;


	for(int k=0; k<3; k++)
	{
		if(x+HOUSE_WIDTH3>len || y+HOUSE_LENGTH3>len)
		{
			valid = 0;
			break;
		}

		valid = 1;
	
		i = y;

		while(i<y+length && i<len)
		{
			j = x;
			while(j<x+width && j<len && valid)
			{
				if(map[i*len+j] != CITY)
					valid = 0;
				j++;
			}
			i++;
		}

		if(!valid)
		{
			if(width == HOUSE_WIDTH1)
			{
				width = HOUSE_WIDTH2;
				length = HOUSE_LENGTH2;
				valid = 1;
			}
			if(width == HOUSE_WIDTH2)
			{
				width = HOUSE_WIDTH3;
				length = HOUSE_LENGTH3;
				valid = 1;
			}
			else // no area available for all sizes
				break;
		}
		if(valid) // a zone has been found
			break;
	}

	if(valid)
	{
		printf("intersection :(%i,%i), house placed at: (%li,%li) dr\n", x, y, x+1, y+1);
		if(width == HOUSE_WIDTH1)
			map[(y+1)*len+x+1] = HOUSE1;
		else if(width == HOUSE_WIDTH2)
			map[(y+1)*len+x+1] = HOUSE2;
		else
			map[(y+1)*len+x+1] = HOUSE3;
	}

}


void find_inter(int* map, size_t len)
{
	for(size_t i =0; i<len;i++)
	{
		for(size_t j = 0; j<len; j++)
		{
			if(map[j*len+i] == INTERSECTION)
			{
				draw_house(map, len, i, j);
			}
		}
	}
}


void printmat(int* mat, int len1, int len2)
{
	for(int i=0; i<len2; i++)
	{
		for(int j=0; j<len1; j++)
		{
			printf("%i,", mat[i*len1+j]);
		}
		printf("\n");
	}
}


int main(int argc, int *argv[])
{
	int mat[] ={0,0,0,0,1,0,0,0,0,0,0,0,0,
				0,0,0,0,1,0,0,0,0,0,0,0,0,
				0,0,0,0,1,0,0,0,0,0,0,0,0,
				0,0,0,0,1,0,0,0,0,0,0,0,0,
				1,1,1,1,3,1,1,1,1,1,3,1,1,
				0,0,0,0,0,0,0,0,0,0,1,0,0,
				0,0,0,0,0,0,0,0,0,0,1,0,0,
				0,0,0,0,0,0,0,0,0,0,1,0,0,
				0,0,0,0,0,0,0,0,0,0,1,0,0,
				0,0,0,0,0,0,0,0,0,0,1,0,0,
				0,0,0,0,1,1,1,1,1,1,3,0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,0,
				0,0,0,0,0,0,0,0,0,0,0,0,0,

	};
	printmat(mat,13,13);
	printf("\n");
	find_inter(mat, 13);
	printf("\nresult:\n");
	printmat(mat,13,13);
}


/*
array[i][j] = array[i * cols + j]
-i is the row number of the cell we want to access.

-j is the column number of the cell we want to access.

-cols is the total number of columns.
*/
