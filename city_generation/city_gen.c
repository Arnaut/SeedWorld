#include "roads_gen.h"
#include "name_gen.h"
#include "mat_to_img.h"
#include "pixel_operation.h"
#include "house.h"

void build_city(int* w_map, SDL_Surface* img,int w_rows,int w_cols,int type)
{
    int* x_y_position= find_fields(w_map,w_rows,w_cols);//position of the different cities
    int* map;
    int cols=0;
    int rows=0;
    int x=0;
    int y=0;
    while(i!=NULL)
    {
        x=x_y_position[i];
        y=x_y_position[i+1];
        cols=x_y_position[i+2];
        rows=x_y_position[i+3];
        map=calloc(cols*rows,sizeof(int));
        build_roads(map,rows,cols);
        find_inter(map, rows, cols);
        int len=0;
        char* city_name=name_gen(type,&len);
        drawName(city_name, len);
        createSpriteRGB(map,rows,cols,type);
        SDL_Surface* src=SDL_LoadBMP("images/city.bmp");
        placeSprite(img,src,x,y);
        src=SDL_LoadBMP("name.bmp");
        placeSprite(img,src,x,y-7);
        SDL_FreeSurface(src);
        i+=4;
    }
}