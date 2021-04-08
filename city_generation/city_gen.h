#ifndef CITY_GEN
#define CITY_GEN

int nb_rand(int min, int max);
int define_dir(int x, int y, int cols, int rows, int vertical);
int draw_road(int* map, int x, int y, int r_size, int cols, int rows, int vertical, int direction);
void build_roads(int* map, int rows, int cols);

#endif
