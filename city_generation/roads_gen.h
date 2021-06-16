#ifndef ROADS_GEN
#define ROADS_GEN

//generates random number between min and max
int nb_rand(int min, int max);

//======================FIND FIELD=========================
//find a position where a city can be build
int* find_fields(int* map, int cols, int rows);

//=====================BUILD ROADS========================
//main fonction build all the roads of our future city
void build_roads(int* map, int rows, int cols);

#endif
