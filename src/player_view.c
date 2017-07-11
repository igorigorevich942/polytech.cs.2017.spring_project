/** \file player_view.с
\brief Файл, в котором опеределены функции для работы с отображением игрока.

\def FUN_NAME 
\brief Имя текущей функции.
*/

#include "player_view.h"
#include "rectangle_view.h"
#include "error_report.h"

#include <stdlib.h>

#define FILE_NAME "player_view.c" ///<Имя текущего файла.

#define abs(a) (((a) > 0) ? (a) : (-(a)))  ///< Макрос для нахождение модуля аргумента.

player_view* player_view_create(player_model* p_model, unsigned int x_start, unsigned int y_start, unsigned int y_finish)
{
    #define FUN_NAME "player_view_create"
    if (p_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument p_model is NULL.");
        return NULL;
    }

    if (abs(y_start - y_finish) < PLAYER_SIZE) {
        error_report(FILE_NAME, FUN_NAME, "distance very small.");
        return NULL;
    }

    player_view* p_view = malloc(sizeof(*p_view));
    if (p_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "malloc error.");
        return NULL;
    }

    p_view->p_rect = rectangle_view_create(PLAYER_COLOR, PLAYER_SIZE, PLAYER_SIZE);
    if (p_view->p_rect == NULL) {
        error_report(FILE_NAME, FUN_NAME, "error create rectangle.");
        free(p_view);
        return NULL;
    }

    p_view->p_model = p_model;
    p_view->x_start = x_start;
    p_view->y_start = y_start;
    p_view->y_finish = y_finish;

    return p_view;

    #undef FUN_NAME
}

int player_view_draw(player_view* p_view)
{
    #define FUN_NAME "player_view_draw"

    if (p_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument p_view is NULL.");
        return -1;
    }

    if (p_view->p_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "p_model is NULL.");
        return -1;
    }

    if (p_view->p_rect == NULL) {
        error_report(FILE_NAME, FUN_NAME, "p_rect is NULL.");
        return -1;
    }

    unsigned int x = p_view->x_start;
    double dy = ((double)DISTANCE_LENGTH - p_view->p_model->pos) / DISTANCE_LENGTH;
    unsigned int y = (int)p_view->y_finish + dy * ((int)p_view->y_start - (int)p_view->y_finish);
    rectangle_view_draw(p_view->p_rect, x, y);

    return 0;

    #undef FUN_NAME
}

int player_view_destroy(player_view* p_view)
{
    #define FUN_NAME "player_view_destroy"

    if (p_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument p_view is NULL.");
        return -1;
    }

    if (p_view->p_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "p_model is NULL.");
        return -1;
    }

    if (p_view->p_rect == NULL) {
        error_report(FILE_NAME, FUN_NAME, "p_rect is NULL.");
        return -1;
    }

    int err = 0;

    if (rectangle_view_destroy(p_view->p_rect)) {
        error_report(FILE_NAME, FUN_NAME, "error destroy p_rect.");
        err = -1;
    }
    free(p_view);

    return err;

    #undef FUN_NAME
}

#undef abs
#undef FILE_NAME
