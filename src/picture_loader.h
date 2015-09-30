#ifndef PICTURE_LOADER_H
#define PICTURE_LOADER_H

#include "global.h"


//------------
// Functions
//------------


Uint32 get_pixel(SDL_Surface* f_surface, int f_x, int f_y);

block color_pixel(Uint32 f_pixel, SDL_Surface* f_surface);

void load_picture(char* f_name, picture* f_picture);

void get_data_grid(block** f_pixels, picture* f_picture);

void get_data_line(block** f_pixels, int f_line, picture* f_picture);

void get_data_column(block** f_pixels, int f_column, picture* f_picture);


#endif
