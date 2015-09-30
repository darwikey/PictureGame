#ifndef COLUMN_SOLVING_H
#define COLUMN_SOLVING_H

#include "global.h"

//-----------
// FUNCTIONS
//-----------

void turn_column(int f_column, picture* f_picture, block f_color);

int sum_column(int f_column, picture* f_picture);

int last_data_column(int f_column, picture* f_picture);

int column_is_solved(int f_column, picture* f_picture);

void check_edges_column(int f_column, picture* f_picture);

bool check_column_completed(int f_column, picture* f_picture);

bool check_column_enough_white(int f_column, picture* f_picture);

void find_intersection_column(int f_column, picture* f_picture);

void fill_column_white_cells(int f_column, picture* f_picture);

void fill_column_black_cells(int f_column, picture* f_picture);

void solve_column(int f_column, picture* f_picture);


#endif
