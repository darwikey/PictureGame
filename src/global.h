#ifndef GLOBAL_H
#define GLOBAL_H


//-----------------
// Include
//-----------------
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"


//-----------------
// Define
//-----------------
#define SIZE_BUFFER 1000


//-----------------
// Enumerate
//-----------------
typedef enum
{
    BLACK, WHITE, UNDEFINED
} block;


//-----------------
// Structure
//-----------------
typedef struct
{
    int** data_line;
    int** data_column;
    block** grid;
    int width_grid;
    int height_grid;
    int data_line_width;
    int data_column_height;
} picture;



#endif
