#ifndef CITY_GEN
#define CITY_GEN

int nb_rand(int min, int max);
void draw_road(int* map, int x, int r_size, int cols, int rows, int vertical);
void build_roads(int* map, int rows, int cols);

#endif
