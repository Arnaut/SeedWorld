#ifndef CITY_GEN
#define CITY_GEN

//get a random number between min and max;
int nb_rand(int min, int max);

//define the direction of a road based on its orientation
int define_dir(int x, int y, int cols, int rows, int vertical);

//draw the road
int draw_road(int* map, int x, int y, int r_size, int cols, int rows, int vertical, int direction);

//main fonction build all the roads of our future city
void build_roads(int* map, int rows, int cols);

//test if a future is possible to build
int is_constructible(int*map,int x, int y, int len, int cols,  int vertical, int direction);

//test if there is no other road near the future one
int constructible(int*map, int x, int y,int fixed, int cols, int len, int i, int j, int vertical);

//test if there is no other road next to our starting point
int not_on(int*map,int x, int y, int cols, int vertical, int direction);

//define the length of a road
int define_len(int position, int max, int direction);

//define the starting point of a road
int define_begin(int position, int direction, int end);
#endif
