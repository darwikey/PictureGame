
#ifndef LINE_SOLVING_H
#define LINE_SOLVING_H

#include "global.h"

//-----------
// FUNCTIONS
//-----------

void turn_line(int f_line, picture* f_picture, block f_color);

int sum_line(int f_line, picture* f_picture);

int last_data_line(int f_line, picture* f_picture);

int line_is_solved(int f_line, picture* f_picture);

void check_edges_line(int f_line, picture* f_picture);

bool check_line_completed(int f_line, picture* f_picture);

bool check_line_enough_white(int f_line, picture* f_picture);

void find_intersection_line(int f_line, picture* f_picture);

void fill_line_white_cells(int f_line, picture* f_picture);

void fill_line_black_cells(int f_line, picture* f_picture);

void solve_line(int f_line, picture* f_picture);


#endif
