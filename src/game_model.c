/** \file game_model.с
\brief Файл, в котором реализованы функции для с работы с моделью игры.

\def FUN_NAME 
\brief Имя текущей функции.
*/

#include "game_model.h"
#include "error_report.h"

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define FILE_NAME "game_model.c" ///< Имя текущего файла.

game_model* game_model_create()
{
    #define FUN_NAME "game_model_create"

    game_model* g_model = malloc(sizeof(*g_model));

    if (g_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "malloc error.");
        return NULL;
    }

    g_model->p_model = player_model_create();
    if (g_model->p_model == NULL) {
        free(g_model);
        error_report(FILE_NAME, FUN_NAME, "error create player_model.");
        return NULL;
    }

    g_model->t_model = timer_model_create();
    if (g_model->t_model == NULL) {
        player_model_destroy(g_model->p_model);
        free(g_model);
        error_report(FILE_NAME, FUN_NAME, "error create timer_model.");
        return NULL;
    }

    g_model->last_key = OTHER;
    g_model->num_push = calloc(NUM_PUSH_SIZE, sizeof(*(g_model->num_push)));

    unsigned int k;
    for (k = 0; k < NUM_PUSH_SIZE; ++k) {
        g_model->num_push[k] = 0;
    }

    return g_model;

    #undef FUN_NAME
}

int game_model_key_down(game_model* g_model, key_type k_type)
{
    #define FUN_NAME "game_model_key_down"

    if (g_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument g_model is NULL.");
        return -1;
    }

    if (timer_model_is_start(g_model->t_model) <= 0) {
        error_report(FILE_NAME, FUN_NAME, "game don't start.");
        return -1;
    }

    unsigned int sec = difftime(time(NULL), g_model->t_model->start_time);
    bool flag_add = false;

    switch(k_type) {
    case LEFT:
        if (g_model->last_key != LEFT) {
            flag_add = true;
        }
        g_model->last_key = k_type;
        break;
    case RIGHT:
        if (g_model->last_key != RIGHT) {
            flag_add = true;
        }
        g_model->last_key = k_type;
        break;
    default:
        error_report(FILE_NAME, FUN_NAME, "incorrect key_type.");
        return -1;
    }

    if (flag_add) {
        unsigned int k;
        unsigned int n = sec + SPEED_DOWN_FACTOR;
        if (n > NUM_PUSH_SIZE) {
            n = NUM_PUSH_SIZE;
        }

        for (k = sec; k < n; ++k) {
            ++(g_model->num_push[k]);
        }
    }

    return 0;

    #undef FUN_NAME
}

int game_model_update(game_model* g_model)
{
    #define FUN_NAME "game_model_update"
    if (g_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument g_model is NULL.");
        return -1;
    }

    time_t time_update = time(NULL);
    if (timer_model_update(g_model->t_model, time_update)) {
        error_report(FILE_NAME, FUN_NAME, "error call function timer_model_update.");
        return -1;
    }


    unsigned int sec = difftime(time_update, g_model->t_model->start_time);
    double speed = 0;

    if (sec >+ NUM_PUSH_SIZE) {
        error_report(FILE_NAME, FUN_NAME, "sec very long");
    } else {
        speed = (double) g_model->num_push[sec] / SPEED_DIV_FACTOR;
    }


    if (player_model_update(g_model->p_model, speed)) {
        error_report(FILE_NAME, FUN_NAME, "error call function player_model_update.");
        return -1;
    }

    return 0;

    #undef FUN_NAME
}

int game_model_start(game_model* g_model)
{
    #define FUN_NAME "game_model_start"
    if (g_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument g_model is NULL.");
        return -1;
    }

    if (timer_model_start(g_model->t_model)) {
        error_report(FILE_NAME, FUN_NAME, "error call function timer_model_start.");
        return -1;
    }

    return 0;

    #undef FUN_NAME

}

int game_model_is_end(game_model* g_model)
{
    #define FUN_NAME "game_model_is_end"
    if (g_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument g_model is NULL.");
        return -1;
    }

    if (player_model_is_end(g_model->p_model)) {
        return 1;
    } else {
        return 0;
    }

    #undef FUN_NAME
}

int game_model_destroy(game_model* g_model)
{
    #define FUN_NAME "game_model_destroy"

    if (g_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument g_model is NULL.");
        return -1;
    }

    int err = 0;

    if (player_model_destroy(g_model->p_model)) {
        error_report(FILE_NAME, FUN_NAME, "error destroy player model.");
        err = -1;
    }

    if (timer_model_destroy(g_model->t_model)) {
        error_report(FILE_NAME, FUN_NAME, "error destroy timer model.");
        err = -1;
    }

    free(g_model->num_push);
    free(g_model);

    return err;

    #undef FUN_NAME
}

#undef FILE_NAME
