#include "grid_loader.h"


/*
 * Analyse data input
 * return 1 if success
 */
int analyse_data_input(char f_input[], picture* f_picture, bool f_is_column)
{

    char _tmp_str [10] = {0};
    int _index_data_1 = 0;
    int _index_data_2 = 0;


    for (int i = 0; f_input[i] != 0; i++)
    {
        // Element is a number
        if (f_input[i] >= '0' && f_input[i] <= '9')
        {
            // Copy of the number
            for (int j = 0; j < 9; j++)
            {
                _tmp_str[j] = f_input[i + j];
            }
            _tmp_str[9] = 0;

            int _number = atoi(_tmp_str);
            //printf("%d\n", _number);

            if (f_is_column)
            {
                f_picture->data_column[_index_data_1][_index_data_2] = _number;
                _index_data_2 ++;

            }
            else
            {
                f_picture->data_line[_index_data_2][_index_data_1] = _number;
                _index_data_2 ++;
            }

            // Next position for numbers with 2 digits
            if (_number >= 10 && _number < 100)
            {
                i ++;
            }

        }
        else if (f_input[i] == ' ')
        {

        }
        else if (f_input[i] == ';')
        {

            _index_data_1 ++;
            _index_data_2 = 0;
        }
        else
        {
            //printf("error incorrect syntax\n");
            return 0;
        }
    }

    return 1;
}

/*
 * initialise and allocate the grids
 */
void init_picture(picture* f_picture)
{
    // init some variables
    f_picture->data_line = NULL;
    f_picture->data_column = NULL;
    f_picture->grid = NULL;


    // Find size data
    f_picture->data_line_width = 1 + f_picture->width_grid / 2;
    f_picture->data_column_height = 1 + f_picture->height_grid / 2;


    // Allocation grid
    f_picture->grid = (block**) malloc(f_picture->width_grid * sizeof(block*));

    if (f_picture->grid == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < f_picture->width_grid; i++)
    {
        f_picture->grid[i] = (block*) malloc(f_picture->height_grid * sizeof(block));

        if (f_picture->grid[i] == NULL)
        {
            exit(EXIT_FAILURE);
        }

        // init grid
        for (int j = 0; j < f_picture->height_grid; j++)
        {
            f_picture->grid[i][j] = UNDEFINED;
        }
    }

    // Allocation data line
    f_picture->data_line = (int**) malloc(f_picture->data_line_width * sizeof(int*));

    if (f_picture->data_line == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < f_picture->data_line_width; i++)
    {
        f_picture->data_line[i] = (int*) malloc(f_picture->height_grid * sizeof(int));

        if (f_picture->data_line[i] == NULL)
        {
            exit(EXIT_FAILURE);
        }

        // init data line
        for (int j = 0; j < f_picture->height_grid; j++)
        {
            f_picture->data_line[i][j] = 0;
        }
    }

    // Allocation data column
    f_picture->data_column = (int**) malloc(f_picture->width_grid * sizeof(int*));

    if (f_picture->data_column == NULL)
    {
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < f_picture->width_grid; i++)
    {
        f_picture->data_column[i] = (int*) malloc(f_picture->data_column_height * sizeof(int));

        if (f_picture->data_column[i] == NULL)
        {
            exit(EXIT_FAILURE);
        }

        // init data column
        for (int j = 0; j < f_picture->data_column_height; j++)
        {
            f_picture->data_column[i][j] = 0;
        }
    }
}


void file_reading(char* f_name, picture* f_picture)
{
    int TAILLE_MAX = 1000;
    FILE* _file = NULL;
    _file = fopen(f_name, "r");

    char _line[TAILLE_MAX];
    char _column[TAILLE_MAX];

    int _width = 0;
    int _height = 0;

    if (_file != NULL)
    {
        fscanf(_file, "%d %d\n", &_height, &_width);
        f_picture->width_grid = _width;
        f_picture->height_grid = _height;

        init_picture(f_picture);

        // Get data for columns and lines
        fgets(_line, TAILLE_MAX, _file);
        analyse_data_input(_line, f_picture, false);

        fgets(_column, TAILLE_MAX, _file);
        analyse_data_input(_column, f_picture, true);


        fclose(_file);
    }
}

