/** \file rectangle_view.c
\brief Файл, в котором реализованы функции для работы с элементом интерфейса: "прямоугольник".

\def FUN_NAME 
\brief Имя текущей функции.
*/

#include "rectangle_view.h"
#include "error_report.h"

#define FILE_NAME "rectangle_view.c" ///< Имя текущего файла.

ALLEGRO_BITMAP* rectangle_view_create(ALLEGRO_COLOR color, unsigned int width, unsigned int height)
{
    #define FUN_NAME "rectangle_view_create"

    if (width == 0 || height == 0) {
        error_report(FILE_NAME, FUN_NAME, "incorrect size.");
        return NULL;
    }

    ALLEGRO_BITMAP* r_view = al_create_bitmap(width, height);
    if (r_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "don't create bitmap.");
        return NULL;
    }

    al_set_target_bitmap(r_view);
    al_clear_to_color(color);

    return r_view;

    #undef FUN_NAME
}

int rectangle_view_draw(ALLEGRO_BITMAP* r_view, unsigned int x, unsigned int y)
{
    #define FUN_NAME "rectangle_view_draw"

    if (r_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument r_view is NULL.");
        return -1;
    }

    al_draw_bitmap(r_view, x, y, 0);

    return 0;

    #undef FUN_NAME
}

int rectangle_view_destroy(ALLEGRO_BITMAP* r_view)
{
    #define FUN_NAME "rectangle_view_destroy"

    if (r_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument r_view is NULL.");
        return -1;
    }

    al_destroy_bitmap(r_view);

    return 0;

    #undef FUN_NAME
}

#undef FILE_NAME
