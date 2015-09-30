#ifndef GRID_LOADER_H
#define GRID_LOADER_H

#include "global.h"


//------------
// Functions
//------------

int analyse_data_input(char f_input[], picture* f_picture, bool f_is_column);

void init_picture(picture* f_picture);

void file_reading(char* f_name, picture* f_picture);


#endif
