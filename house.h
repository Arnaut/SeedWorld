#ifndef HOUSE
#define HOUSE


void placeHouse(int* map, int rows, int cols, int r, int c, int house_type, int house_width, int house_length);

int draw(int *map, int rows, int cols, int c, int r, int house_type, int house_width, int house_length);

void draw_house2(int *map, int rows, int cols, int c, int r);

void find_inter(int* map, int rows, int cols);

#endif
