#include "display.h"
#include "line_solving.h"
#include "column_solving.h"

/*
 * Initialialise SDL and SDL TTF
 */
void display_init()
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    // Screen
    display_screen = SDL_SetVideoMode(1024, 900, 32, SDL_HWSURFACE);

    SDL_WM_SetCaption("Picture", NULL);

    // Font
    display_font = TTF_OpenFont("rc/arial.ttf", 14);
    if (display_font == NULL)
    {
        printf("error : not able to find arial.ttf");
        exit(EXIT_FAILURE);
    }

}



/*
 * Display the grid and the associate datas
 */
void display_picture(picture* f_picture)
{
    bool _done = false;
    SDL_Event _event;

    SDL_Surface* _box = SDL_CreateRGBSurface(SDL_HWSURFACE, 20, 20, 32, 0, 0, 0, 0);


    while (! _done)
    {
        // Event of the window
        SDL_WaitEvent(&_event);
        switch (_event.type)
        {
            case SDL_QUIT:
                _done = true;
        }


        // Background
        SDL_FillRect(display_screen, NULL, SDL_MapRGB(display_screen->format, 0, 185, 255));

        // Display grid
        for (int x = 0; x < f_picture->width_grid; x++)
        {
            for (int y = 0; y < f_picture->height_grid; y++)
            {
                SDL_Rect _position;
                _position.x = 200 + 22 * x;
                _position.y = 200 + 22 * y;

                display_block(_box, &_position, f_picture->grid[x][y]);
            }
        }

        // Display data line
        char _string [10];
        SDL_Color _color = {255, 255, 255, 255};
        for (int x = 0; x < f_picture->data_line_width; x++)
        {
            for (int y = 0; y < f_picture->height_grid; y++)
            {
                // don't print 0
                if (f_picture->data_line[x][y] == 0)
                {
                    continue;
                }

                SDL_Rect _position;
                _position.x = 182 - 22 * last_data_line(y, f_picture) + 22 * x;
                _position.y = 200 + 22 * y;

                snprintf(_string, 10, "%d", f_picture->data_line[x][y]);

                SDL_Surface* _text = TTF_RenderText_Blended(display_font, _string, _color);
                SDL_BlitSurface(_text, NULL, display_screen, &_position);

                SDL_FreeSurface(_text);
            }
        }


        // Display data column
        for (int x = 0; x < f_picture->width_grid; x++)
        {
            for (int y = 0; y < f_picture->data_column_height; y++)
            {
                // don't print 0
                if (f_picture->data_column[x][y] == 0)
                {
                    continue;
                }

                SDL_Rect _position;
                _position.x = 200 + 22 * x;
                _position.y = 180 - 22 * last_data_column(x, f_picture) + 22 * y;

                snprintf(_string, 10, "%d", f_picture->data_column[x][y]);

                SDL_Surface* _text = TTF_RenderText_Blended(display_font, _string, _color);
                SDL_BlitSurface(_text, NULL, display_screen, &_position);

                SDL_FreeSurface(_text);
            }
        }

        //Display difficulty
        display_difficulty(f_picture);

        SDL_Flip(display_screen);

    }

}


/*
 * Draw a block on the screen
 * f_box is the surface to draw
 * f_block is the state of the square in the grid
 */
void display_block(SDL_Surface* f_box, SDL_Rect* f_position, block f_block)
{

    switch (f_block)
    {
        case WHITE:
            SDL_FillRect(f_box, NULL, SDL_MapRGB(display_screen->format, 255, 255, 255));
            break;

        case BLACK:
            SDL_FillRect(f_box, NULL, SDL_MapRGB(display_screen->format, 0, 0, 0));
            break;

        default:
        case UNDEFINED:
            SDL_FillRect(f_box, NULL, SDL_MapRGB(display_screen->format, 128, 128, 128));
            break;
    }


    SDL_BlitSurface(f_box, NULL, display_screen, f_position);

}


/*
 * Display grid's difficulty
 */
void display_difficulty(picture* f_picture)
{
    // Count number of blocks in grid
    int _nb_data = 0;
    for (int i = 0; i < f_picture->data_line_width; i++)
    {
        for (int j = 0; j < f_picture->height_grid; j++)
        {
            _nb_data += f_picture->data_line[i][j];
        }
    }

    SDL_Color _color = {255, 255, 255, 255};

    // Position for display difficulty
    SDL_Rect _position;
    _position.x = 700 ;
    _position.y = 10;

    float _size_grid = f_picture->width_grid * f_picture->height_grid ;
    float _difficulty = (float)_nb_data / _size_grid;

    char _string[10];

    if (_difficulty >= 0.60)
    {
        snprintf(_string, 10, "Facile");
    }
    else if (_difficulty >= 0.40)
    {
        snprintf(_string, 10, "Moyen");
    }
    else
    {
        snprintf(_string, 10, "Difficile");
    }

    // Display difficulty
    SDL_Surface* _text = TTF_RenderText_Blended(display_font, _string, _color);
    SDL_BlitSurface(_text, NULL, display_screen, &_position);
    SDL_FreeSurface(_text);
}
