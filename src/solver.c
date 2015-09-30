#include "solver.h"


/*
 * Recursive function
 */
bool is_valid(picture* f_picture, int f_line, int f_column)
{
    // we have reached the end of the grid
    if (f_line >= f_picture->height_grid)
    {
        return true;
    }


    // next position
    int _next_line = f_line;
    int _next_column = f_column + 1;
    if (_next_column >= f_picture->width_grid)
    {
        _next_column = 0;
        _next_line ++;
    }


    // if the block has been already determined
    if (f_picture->grid[f_column][f_line] != UNDEFINED)
    {
        return is_valid(f_picture, _next_line, _next_column);
    }


    // possible value for the block
    for (int _value = 0; _value <= 1; _value++)
    {
        f_picture->grid[f_column][f_line] = _value;

        if (is_line_valid(f_picture, f_line) && is_column_valid(f_picture, f_column))
        {
            if (is_valid(f_picture, _next_line, _next_column))
            {
                return true;
            }
        }

    }

    // No solution found
    f_picture->grid[f_column][f_line] = UNDEFINED;
    return false;
}


bool is_line_valid(picture* f_picture, int f_line)
{
    int j = 0;
    int _block_in_data = 0;

    for (int i = 0; i < f_picture->data_line_width; i++)
    {
        int _count = f_picture->data_line[i][f_line];

        if (_count <= 0)
        {
            break;
        }

        _block_in_data += _count;

        for (; j < f_picture->width_grid; j++)
        {
            if (f_picture->grid[j][f_line] == WHITE)
            {
                _count = f_picture->data_line[i][f_line];
            }
            else
            {
                _count --;

            }

            if (_count == 0)
            {
                j += 2;
                break;
            }

        }

        if (_count != 0)
        {
            return false;
        }

    }

    int _block_in_grid = 0;
    for (int i = 0; i < f_picture->width_grid; i++)
    {
        if (f_picture->grid[i][f_line] == BLACK)
        {
            _block_in_grid ++;
        }
    }

    if (_block_in_grid > _block_in_data)
    {
        return false;
    }
    else
    {
        return true;
    }
}


bool is_column_valid(picture* f_picture, int f_column)
{
    int j = 0;
    int _block_in_data = 0;

    for (int i = 0; i < f_picture->data_column_height; i++)
    {
        int _count = f_picture->data_column[f_column][i];

        if (_count <= 0)
        {
            break;
        }

        _block_in_data += _count;

        for (; j < f_picture->height_grid; j++)
        {
            if (f_picture->grid[f_column][j] == WHITE)
            {
                _count = f_picture->data_column[f_column][i];
            }
            else
            {
                _count --;

            }

            if (_count == 0)
            {
                j += 2;
                break;
            }

        }

        if (_count != 0)
        {
            return false;
        }

    }

    int _block_in_grid = 0;
    for (int i = 0; i < f_picture->height_grid; i++)
    {
        if (f_picture->grid[f_column][i] == BLACK)
        {
            _block_in_grid ++;
        }
    }

    if (_block_in_grid > _block_in_data)
    {
        return false;
    }
    else
    {
        return true;
    }
}
