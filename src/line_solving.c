#include "line_solving.h"

/*
 * Fill a line with a defined color
 */
void turn_line(int f_line, picture* f_picture, block f_color)
{
    for (int i = 0; i < f_picture->width_grid; i++)
    {
        f_picture->grid[i][f_line] = f_color;
    }
}


/*
 * Return sum of line data taking into account spaces
 */
int sum_line(int f_line, picture* f_picture)
{
    int _sum = 0;
    for (int i = 0; i < f_picture->data_line_width; i++)
    {
        _sum += f_picture->data_line[i][f_line];
    }
    _sum += last_data_line(f_line, f_picture) ;
    return _sum;
}

/*
 * Return subscript of the last data
 */
int last_data_line(int f_line, picture* f_picture)
{
    for (int i = 0; i < f_picture->data_line_width - 1; i++)
    {
        // Check data is the last and line is not empty
        if (f_picture->data_line[i + 1][f_line] == 0 && f_picture->data_line[i][f_line] != 0)
        {
            return i;
        }
    }
    return f_picture->data_line_width - 1;
}

/*
 * Return 1 if line is solved
 * Return 0 if not
 */
int line_is_solved(int f_line, picture* f_picture)
{
    int i = 0;
    int _solved = 1;
    while (i < f_picture->width_grid && _solved == 1)
    {
        if (f_picture->grid[i][f_line] == UNDEFINED)
        {
            _solved = 0;
        }
    }
    return _solved;
}

void check_edges_line(int f_line, picture* f_picture)
{
    int _width_grid = f_picture->width_grid - 1;

    // Left edge
    if (f_picture->grid[0][f_line] == BLACK)
    {
        int i;
        for (i = 1; i < f_picture->data_line[0][f_line]; i++)
        {
            f_picture->grid[i][f_line] = BLACK;
        }
        f_picture->grid[i][f_line] = WHITE ;
    }

    // Right edge
    if (f_picture->grid[_width_grid][f_line] == BLACK)
    {
        int j;
        int _data_l =  f_picture->data_line[last_data_line(f_line, f_picture)][f_line];
        for (j = _width_grid; j > _width_grid - _data_l ; j--)
        {
            f_picture->grid[j][f_line] = BLACK;
        }
        f_picture->grid[j][f_line] = WHITE;
    }
}

/*
 * Return if cells are filled as in data
 */
bool check_line_completed(int f_line, picture* f_picture)
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
            if (f_picture->grid[j][f_line] != BLACK)
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

/*
 * Return if number of cells black or undefined match with data
 */
bool check_line_enough_white(int f_line, picture* f_picture)
{
    int _cells = 0;
    int _nb_data = 0;

    for (int i = 0; i < f_picture->data_line_width; i++)
    {
        _nb_data += f_picture->data_line[i][f_line];
    }

    // No data in column
    if (_nb_data == 0)
    {
        return false;
    }

    for (int j = 0; j < f_picture->width_grid; j++)
    {
        if (f_picture->grid[j][f_line] == UNDEFINED || f_picture->grid[j][f_line] == BLACK)
        {
            _cells ++;
        }
    }

    if (_cells == _nb_data)
    {
        return true;
    }
    else
    {
        return false;
    }
}


/*
 * move all the ranges of a line and check the intersection
 */
void find_intersection_line(int f_line, picture* f_picture)
{
    if (f_picture->data_line[0][f_line] == 0)
    {
        return;
    }

    int _nb_range = last_data_line(f_line, f_picture) + 1;

    int* _tab_shift = (int*) malloc(_nb_range * sizeof(int));
    int* _tab_intersection = (int*) malloc(f_picture->width_grid * sizeof(int));

    if (!_tab_shift || !_tab_intersection)
    {
        return;
    }

    for (int i = 0; i < _nb_range; i++)
    {
        _tab_shift[i] = 0;
    }
    for (int i = 0; i < f_picture->width_grid; i++)
    {
        _tab_intersection[i] = BLACK;
    }


    int _shift_max = f_picture->width_grid - sum_line(f_line, f_picture);


    while (_tab_shift[_nb_range - 1] <= _shift_max)
    {
        int _sum = 0;

        for (int i = 0; i < _nb_range - 1; i++)
        {
            if (_tab_shift[i] > _shift_max)
            {
                _tab_shift[i] = 0;
                _tab_shift[i + 1] ++;
            }

            _sum += _tab_shift[i];
        }

        // we can keep _tab_shift only if the sum of shift is less than shift_max
        if (_sum + _tab_shift[_nb_range - 1] > _shift_max)
        {
            // increment shift
            _tab_shift[0] ++;

            continue;
        }


        // intersect black boxes find with the previous
        int i = 0;
        for (int j = 0; j < _nb_range;)
        {
            int k;
            for (k = 0; k < _tab_shift[j]; k++)
            {
                _tab_intersection[i + k] = WHITE;
            }

            // move after spaces
            i += k;

            // move after black boxes
            i += f_picture->data_line[j][f_line];

            if (i < f_picture->width_grid)
            {
                _tab_intersection[i] = WHITE;
            }
            i++;

            j++;
        }

        for (; i < f_picture->width_grid; i++)
        {
            _tab_intersection[i] = WHITE;
        }

        // increment shift
        _tab_shift[0] ++;
    }


    // Copy the back cell find
    for (int i = 0; i < f_picture->width_grid; i++)
    {
        if (_tab_intersection[i] == BLACK)
        {
            f_picture->grid[i][f_line] = BLACK;
        }
    }


    free(_tab_shift);
    free(_tab_intersection);
}


void fill_line_white_cells(int f_line, picture* f_picture)
{
    for (int i = 0; i < f_picture->width_grid; i++)
    {
        if (f_picture->grid[i][f_line] == UNDEFINED)
        {
            f_picture->grid[i][f_line] = WHITE ;
        }
    }
}

void fill_line_black_cells(int f_line, picture* f_picture)
{
    for (int i = 0; i < f_picture->width_grid; i++)
    {
        if (f_picture->grid[i][f_line] == UNDEFINED)
        {
            f_picture->grid[i][f_line] = BLACK ;
        }
    }
}

/*
 * Solve a line
 */
void solve_line(int f_line, picture* f_picture)
{
    int _width_grid = f_picture->width_grid;

    // Full line
    if (f_picture->data_line[0][f_line] == _width_grid)
    {
        turn_line(f_line, f_picture, BLACK);
    }

    // Empty line
    else if (f_picture->data_line[0][f_line] == 0)
    {
        turn_line(f_line, f_picture, WHITE);
    }

    // Sum line match with width grid
    else if (sum_line(f_line, f_picture) == _width_grid)
    {
        int j = 0;
        int k;
        for (int i = 0; i < f_picture->data_line_width; i++)
        {
            k = 0;
            while (k < f_picture->data_line[i][f_line] && j < _width_grid)
            {
                f_picture->grid[j][f_line] = BLACK ;
                j++;
                k++;
            }
            if (j != _width_grid)
            {
                f_picture->grid[j][f_line] = WHITE ;
                j++;
            }
        }
    }
    else
    {
        for (int i = 0; i < f_picture->data_line_width; i++)
        {
            if (f_picture->data_line[i][f_line] > _width_grid / 2)
            {
                int _range = _width_grid - f_picture->data_line[i][f_line];
                for (int j = _range; j < f_picture->data_line[i][f_line]; j++)
                {
                    f_picture->grid[j][f_line] = BLACK;
                }
            }
        }
        check_edges_line(f_line, f_picture);

        if (check_line_completed(f_line, f_picture))
        {
            fill_line_white_cells(f_line, f_picture);
        }

        if (check_line_enough_white(f_line, f_picture))
        {
            fill_line_black_cells(f_line, f_picture);
        }

    }
}
