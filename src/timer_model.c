/** \file timer_model.с
\brief Файл, в котором реализованы функции для работы с моделью таймеров.

\def FUN_NAME 
\brief Имя текущей функции.
*/
#include "timer_model.h"
#include "error_report.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "timer_model.c" ///< Имя текущего файла.
#define DEFAULT_TOP_RESULT "Record: ??:??" ///< Строка по умолчанию для рекордного таймера.
#define SEC_IN_MN 60 ///< Количество секунд в минуте.

timer_model* timer_model_create()
{
    #define FUN_NAME "timer_model_create"

    timer_model* t_model = malloc(sizeof(*t_model));
    if (t_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "malloc error.");
        return NULL;
    }

    FILE* data = fopen(PATH_DATA, "r");
    if (data == NULL) {
        strcpy(t_model->top_time, DEFAULT_TOP_RESULT);
    } else {
        unsigned int mn, sec;
        int num = fscanf(data, "%u:%u", &mn, &sec);
        if (num == 2 && (mn <= MAX_MN) && (sec <= MAX_SEC) && (mn != 0 || sec != 0)) {
            sprintf(t_model->top_time, "Record: %02u:%02u", mn, sec);
        } else {
            strcpy(t_model->top_time, DEFAULT_TOP_RESULT);
        }
        fclose(data);
    }

    strcpy(t_model->current_time, "00:00");
    t_model->start_time = 0;

    return t_model;

    #undef FUN_NAME
}

int timer_model_start(timer_model* t_model)
{
    #define FUN_NAME "timer_model_start"

    if (t_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument t_model is NULL.");
        return -1;
    } else if (timer_model_is_start(t_model)) {
        error_report(FILE_NAME, FUN_NAME, "timer already start.");
        return -1;
    }
    

    t_model->start_time = time(NULL);
    return 0;

    #undef FUN_NAME

}

int timer_model_update(timer_model* t_model, time_t update_time)
{
    #define FUN_NAME "timer_model_update"

    if (t_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument t_model is NULL.");
        return -1;
    }

    if (t_model->start_time == 0) {
        error_report(FILE_NAME, FUN_NAME, "game don't start (start_time = 0).");
        return -1;
    }

    if (update_time < t_model->start_time) {
        error_report(FILE_NAME, FUN_NAME, "update_time less start_time.");
        return -1;
    }

    unsigned int sec = difftime(update_time, t_model->start_time);
    sprintf(t_model->current_time, "%02u:%02u", sec / 60, sec % 60);

    return 0;

    #undef FUN_NAME
}

int timer_model_save_result(timer_model* t_model)
{
    #define FUN_NAME "timer_model_save_result"

    if (t_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument t_model is NULL.");
        return -1;
    }

    if (t_model->start_time == 0) {
        error_report(FILE_NAME, FUN_NAME, "game don't start (start_time = 0).");
        return -1;
    }

    FILE* data = fopen(PATH_DATA, "w");
    if (data == NULL) {
        error_report(FILE_NAME, FUN_NAME, "don't open file to write data.");
        return -1;
    } else {
        if (strcmp(t_model->top_time, DEFAULT_TOP_RESULT) == 0) {
            fprintf(data, "%s\n", t_model->current_time);
            sprintf(t_model->top_time, "Record: %s", t_model->current_time);
        } else {
            unsigned int top_mn, top_sec;
            unsigned int mn, sec;

            sscanf(t_model->top_time, "Record: %u:%u", &top_mn, &top_sec);
            sscanf(t_model->current_time, "%u:%u", &mn, &sec);

            sec += mn * SEC_IN_MN;
            top_sec += top_mn * SEC_IN_MN;

            if (sec < top_sec) {
                fprintf(data, "%s\n", t_model->current_time);
                sprintf(t_model->top_time, "Record: %s", t_model->current_time);
            } else {
                fprintf(data, "%02u:%02u\n", top_sec / SEC_IN_MN, top_sec % SEC_IN_MN);
            }
        }
        fclose(data);
    }

    return 0;

    #undef FUN_NAME
}

int timer_model_destroy(timer_model* t_model)
{
    #define FUN_NAME "timer_model_destroy"

    if (t_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument t_model is NULL.");
        return -1;
    }

    free(t_model);
    return 0;

    #undef FUN_NAME
}

int timer_model_is_start(timer_model* t_model)
{
    #define FUN_NAME "timer_model_is_start"

    if (t_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument t_model is NULL.");
        return -1;
    }

    if (t_model->start_time) {
        return 1;
    } else {
        return 0;
    }

    #undef FUN_NAME
}

#undef FILE_NAME
