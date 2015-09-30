#include "column_solving.h"

/*
 * Fill a column with a defined color
 */
void turn_column(int f_column, picture* f_picture, block f_color)
{
    for (int i = 0; i < f_picture->height_grid; i++)
    {
        f_picture->grid[f_column][i] = f_color;
    }
}


/*
 * Return sum of column  data taking into account spaces
 */
int sum_column(int f_column, picture* f_picture)
{
    int _sum = 0;
    for (int i = 0; i < f_picture->data_column_height; i++)
    {
        _sum += f_picture->data_column[f_column][i];
    }
    _sum += last_data_column(f_column, f_picture) ;
    return _sum;
}

/*
 * Return subscript of the last data
 */
int last_data_column(int f_column, picture* f_picture)
{
    for (int i = 0; i < f_picture->data_column_height - 1; i++)
    {
        // Check data is the last and column is not empty
        if (f_picture->data_column[f_column][i + 1] == 0 && f_picture->data_column[f_column][i] != 0)
        {
            return i;
        }
    }
    return f_picture->data_column_height - 1;
}

/*
 * Return 1 if column is solved
 * Return 0 if not
 */
int column_is_solved(int f_column, picture* f_picture)
{
    int i = 0;
    int solved = 1;
    while (i < f_picture->height_grid && solved == 1)
    {
        if (f_picture->grid[f_column][i] == UNDEFINED)
        {
            solved = 0;
        }
    }
    return solved;
}

void check_edges_column(int f_column, picture* f_picture)
{
    int _height_grid = f_picture->height_grid - 1;

    // Top  edge
    if (f_picture->grid[f_column][0] == BLACK)
    {
        int i;
        for (i = 1; i < f_picture->data_column[f_column][0]; i++)
        {
            f_picture->grid[f_column][i] = BLACK;
        }
        f_picture->grid[f_column][i] = WHITE ;
    }

    // Bottom edge
    if (f_picture->grid[f_column][_height_grid] == BLACK)
    {
        int j;
        int _data_l =  f_picture->data_column[f_column][last_data_column(f_column, f_picture)];
        for (j = _height_grid - 1; j > _height_grid - _data_l ; j--)
        {
            f_picture->grid[f_column][j] = BLACK;
        }
        f_picture->grid[f_column][j] = WHITE;
    }
}

/*
 * Return if cells in a column are filled as written in data
 */
bool check_column_completed(int f_column, picture* f_picture)
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
            if (f_picture->grid[f_column][j] != BLACK)
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


/*
 * Return if number of cells black or undefined match with data
 */
bool check_column_enough_white(int f_column, picture* f_picture)
{
    int _cells = 0;
    int _nb_data = 0;

    for (int i = 0; i < f_picture->data_column_height; i++)
    {
        _nb_data += f_picture->data_column[f_column][i];
    }

    // No data in column
    if (_nb_data == 0)
    {
        return false;
    }

    for (int j = 0; j < f_picture->height_grid; j++)
    {
        if (f_picture->grid[f_column][j] == UNDEFINED || f_picture->grid[f_column][j] == BLACK)
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
 * move all the ranges of a column and check the intersection
 */
void find_intersection_column(int f_column, picture* f_picture)
{
    if (f_picture->data_column[f_column][0] == 0)
    {
        return;
    }

    int _nb_range = last_data_column(f_column, f_picture) + 1;

    int* _tab_shift = (int*) malloc(_nb_range * sizeof(int));
    int* _tab_intersection = (int*) malloc(f_picture->height_grid * sizeof(int));

    if (!_tab_shift || !_tab_intersection)
    {
        return;
    }

    for (int i = 0; i < _nb_range; i++)
    {
        _tab_shift[i] = 0;
    }
    for (int i = 0; i < f_picture->height_grid; i++)
    {
        _tab_intersection[i] = BLACK;
    }


    int _shift_max = f_picture->height_grid - sum_column(f_column, f_picture);


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
            i += f_picture->data_column[f_column][j];

            if (i < f_picture->height_grid)
            {
                _tab_intersection[i] = WHITE;
            }
            i++;

            j++;
        }

        for (; i < f_picture->height_grid; i++)
        {
            _tab_intersection[i] = WHITE;
        }

        // increment shift
        _tab_shift[0] ++;
    }


    // Copy the back cell find
    for (int i = 0; i < f_picture->height_grid; i++)
    {
        if (_tab_intersection[i] == BLACK)
        {
            f_picture->grid[f_column][i] = BLACK;
        }
    }


    free(_tab_shift);
    free(_tab_intersection);
}


/*
 * Fill a column with white cells
 */
void fill_column_white_cells(int f_column, picture* f_picture)
{
    for (int i = 0; i < f_picture->height_grid; i++)
    {
        if (f_picture->grid[f_column][i] == UNDEFINED)
        {
            f_picture->grid[f_column][i] = WHITE;
        }
    }
}

/*
 * Fill a column with black cells
 */
void fill_column_black_cells(int f_column, picture* f_picture)
{
    for (int i = 0; i < f_picture->height_grid; i++)
    {
        if (f_picture->grid[f_column][i] == UNDEFINED)
        {
            f_picture->grid[f_column][i] = BLACK;
        }
    }
}


/*
 * Solve a column
 */
void solve_column(int f_column, picture* f_picture)
{
    int _height_grid = f_picture->height_grid;

    // Full column
    if (f_picture->data_column[f_column][0] == _height_grid)
    {
        turn_column(f_column, f_picture, BLACK);
    }

    // Empty column
    else if (f_picture->data_column[f_column][0] == 0)
    {
        turn_column(f_column, f_picture, WHITE);
    }

    // Sum column match with width grid
    else if (sum_column(f_column, f_picture) == _height_grid)
    {
        int j = 0;
        int k;
        for (int i = 0; i < f_picture->data_column_height; i++)
        {
            k = 0;
            while (k < f_picture->data_column[f_column][i] && j < _height_grid)
            {
                f_picture->grid[f_column][j] = BLACK ;
                j++;
                k++;
            }
            if (j != _height_grid)
            {
                f_picture->grid[f_column][j] = WHITE ;
                j++;
            }
        }
    }
    else
    {
        for (int i = 0; i < f_picture->data_column_height; i++)
        {
            if (f_picture->data_column[f_column][i] > _height_grid / 2)
            {
                int _range = _height_grid - f_picture->data_column[f_column][i];
                for (int j = _range; j < f_picture->data_column[f_column][i]; j++)
                {
                    f_picture->grid[f_column][j] = BLACK;
                }
            }
        }
        check_edges_column(f_column, f_picture);

        if (check_column_completed(f_column, f_picture))
        {
            fill_column_white_cells(f_column, f_picture);
        }

        if (check_column_enough_white(f_column, f_picture))
        {
            fill_column_black_cells(f_column, f_picture);
        }
    }
}
