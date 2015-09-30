#ifndef DISPLAY_H
#define DISPLAY_H

#include "global.h"


//-----------------
// Fonctions
//-----------------

void display_init();

void display_picture(picture* f_picture);

void display_block(SDL_Surface* f_box, SDL_Rect* f_position, block f_block);

void display_difficulty(picture* f_picture);


//-----------------
// Global variable
//-----------------

SDL_Surface* display_screen;
TTF_Font* display_font;



#endif
