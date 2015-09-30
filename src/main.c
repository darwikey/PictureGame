#include "global.h"
#include "display.h"
#include "line_solving.h"
#include "column_solving.h"
#include "solver.h"
#include "grid_loader.h"
#include "picture_loader.h"


int main(int argc, char* argv[])
{
    // Init
    display_init();


    // Init
    picture _picture;
    if (argc < 2)
    {
        file_reading("rc/grid/pomme.txt", &_picture);
    }
    else
    {
        // Argument 1 is a text
        if (strstr(argv[1], ".txt") != NULL)
        {
            file_reading(argv[1], &_picture);
        }

        // Argument is a picture
        else if (strstr(argv[1], ".bmp") != NULL)
        {
            load_picture(argv[1], &_picture);
        }
    }

    // solving with intersection
    for (int j = 0; j < _picture.height_grid; j++)
    {
        find_intersection_line(j, &_picture);
    }

    for (int i = 0; i < _picture.width_grid; i++)
    {
        find_intersection_column(i, &_picture);
    }



    for (int k = 0; k < 10; k++)
    {
        for (int j = 0; j < _picture.width_grid; j++)
        {
            solve_column(j, &_picture);
        }

        for (int i = 0; i < _picture.height_grid; i++)
        {
            solve_line(i, &_picture);
        }
    }



    is_valid(&_picture, 0, 0);

    display_picture(&_picture);


    SDL_Quit();
    TTF_Quit();
    return EXIT_SUCCESS;

}

