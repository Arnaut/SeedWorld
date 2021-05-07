#ifndef CITY_GEN
#define CITY_GEN

//======================FIND FIELD=========================
//find a position where a city can be build
int* find_fields(int* map, int cols, int rows);

//=====================BUILD ROADS========================
//main fonction build all the roads of our future city
void build_roads(int* map, int rows, int cols);

#endif
