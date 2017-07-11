#include "player_model.h"
#include "error_report.h"

/** \file player_model.c
\brief Файл, в котором реализованы функции для работы с моделью игрока.

\def FUN_NAME 
\brief Имя текущей функции.
*/

#include <stdlib.h>
#include <math.h>

#define FILE_NAME "player_model.c" ///< Имя текущего файла.
#define EPS 1e-15 ///< Точность сравнения вещественных чисел.

player_model* player_model_create()
{
    #define FUN_NAME "player_model_create" 

    player_model* p_model = malloc(sizeof(*p_model));

    if (p_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "malloc error.");
        return NULL;
    }

    p_model->pos = 0;
    return p_model;

    #undef FUN_NAME
}

int player_model_update(player_model* p_model, double speed)
{
    #define FUN_NAME "player_model_update" 

    if (p_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument p_model is NULL.");
        return -1;
    }

    if (speed < 0) {
        error_report(FILE_NAME, FUN_NAME, "speed is negative.");
        return -1;
    }

    if (p_model->pos < 0 || p_model->pos > DISTANCE_LENGTH) {
        error_report(FILE_NAME, FUN_NAME, "position player is incorrect.");
        return -1;
    }

    p_model->pos += speed;
    if (p_model->pos > DISTANCE_LENGTH) {
        p_model->pos = DISTANCE_LENGTH;
    }

    return 0;

    #undef FUN_NAME
}

int player_model_destroy(player_model* p_model)
{
    #define FUN_NAME "player_model_destroy" 

    if (p_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument p_model is NULL.");
        return -1;
    }

    free(p_model);
    return 0;

    #undef FUN_NAME
}

int player_model_is_end(player_model* p_model)
{
    #define FUN_NAME "player_model_is_end" 

    if (p_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument p_model is NULL.");
        return -1;
    }

    if (fabs(p_model->pos - DISTANCE_LENGTH) < EPS) {
        return 1;
    } else {
        return 0;
    }

    #undef FUN_NAME
}

#undef FILE_NAME
