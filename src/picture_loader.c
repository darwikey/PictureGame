#include "picture_loader.h"
#include "grid_loader.h"


/*
 * Get color of pixel at position (x,y) from a surface
 *
 * Return : color of pixel
 */
Uint32 get_pixel(SDL_Surface* f_surface, int f_x, int f_y)
{
    int _nb_octets_pixel = f_surface->format->BytesPerPixel;

    Uint8* _address_pixel = (Uint8*)f_surface->pixels + f_y * f_surface->pitch + f_x * _nb_octets_pixel;

    switch (_nb_octets_pixel)
    {
        case 1:
            return *_address_pixel;

        case 2:
            return *(Uint16*)_address_pixel;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                return _address_pixel[0] << 16 | _address_pixel[1] << 8 | _address_pixel[2];
            }
            else
            {
                return _address_pixel[0] | _address_pixel[1] << 8 | _address_pixel[2] << 16;
            }

        case 4:
            return *(Uint32*)_address_pixel;

        default:
            return 0;
    }
}


/*
 * Return color of a pixel ( just WHITE or BLACK )
 */
block color_pixel(Uint32 f_pixel, SDL_Surface* f_surface)
{
    // Color elements ( Red, Green, Blue, Alpha : transparence );
    Uint8 _r, _g, _b, _a ;

    SDL_GetRGBA(f_pixel, f_surface->format, &_r, &_g, &_b, &_a);

    int _sum_rgb = _r + _g + _b ;

    // Colors nearly white
    if (_sum_rgb > 450)
    {
        return WHITE ;
    }
    else
    {
        return BLACK ;
    }
}


void load_picture(char* f_name, picture* f_picture)
{
    // Init surface
    SDL_Surface* _surface = NULL;
    _surface = SDL_LoadBMP(f_name);

    // Init picture
    f_picture->width_grid = _surface->w;
    f_picture->height_grid = _surface->h;

    init_picture(f_picture);


    // Array of WHITE and BLACK cells
    block** _pixels = malloc(_surface->w * sizeof(block*));

    for (int i = 0; i < _surface->w; i++)
    {
        _pixels[i] = malloc(_surface->h * sizeof(block));
    }


    for (int i = 0; i < _surface->h; i++)
    {
        for (int j = 0; j < _surface->w; j++)
        {
            _pixels[j][i] = color_pixel(get_pixel(_surface, j, i), _surface);
        }
    }

    get_data_grid(_pixels, f_picture);
}


/*
 * Fill data_line and data_column from pixels array
 */
void get_data_grid(block** f_pixels, picture* f_picture)
{
    for (int i = 0; i < f_picture->width_grid; i++)
    {
        get_data_column(f_pixels, i, f_picture);
    }
    for (int j = 0; j < f_picture->height_grid; j++)
    {
        get_data_line(f_pixels, j, f_picture);
    }
}


/*
 * Get line data from pixels array
 */
void get_data_line(block** f_pixels, int f_line, picture* f_picture)
{
    int k = 0;
    int _block = 0;

    for (int i = 0; i < f_picture->width_grid ; i++)
    {
        if (f_pixels[i][f_line] == BLACK)
        {
            _block += 1;
        }
        else if (_block != 0)
        {
            f_picture->data_line[k][f_line] = _block ;
            _block = 0;
            k += 1;
        }
    }
    if (_block != 0)
    {
        f_picture->data_line[k][f_line] = _block ;
    }

}

/*
 * Get column's data from pixels array
 */
void get_data_column(block** f_pixels, int f_column, picture* f_picture)
{
    int k = 0;
    int _block = 0;

    for (int i = 0; i < f_picture->height_grid ; i++)
    {
        if (f_pixels[f_column][i] == BLACK)
        {
            _block += 1;
        }
        else if (_block != 0)
        {
            f_picture->data_column[f_column][k] = _block ;
            _block = 0;
            k += 1;
        }
    }
    if (_block != 0)
    {
        f_picture->data_column[f_column][k] = _block ;
    }
}

