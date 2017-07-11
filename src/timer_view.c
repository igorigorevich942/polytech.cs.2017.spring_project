/** \file timer_view.c
\brief Файл, в котором реализованы функции для работы с отображением таймеров.

\def FUN_NAME 
\brief Имя текущей функции.
*/

#include "timer_view.h"
#include "error_report.h"

#include <stdlib.h>

#define FILE_NAME "timer_view.c" ///< Текущие имя файла.

static int check_field(timer_view* t_view, const char* fun_name)
{
    if (t_view == NULL) {
        error_report(FILE_NAME, fun_name, "argument t_view is NULL.");
        return -1;
    }

    if (t_view->l_current == NULL) {
        error_report(FILE_NAME, fun_name, "label current is NULL.");
        return -1;
    }

    if (t_view->l_top == NULL) {
        error_report(FILE_NAME, fun_name, "label top is NULL.");
        return -1;
    }

    if (t_view->t_model == NULL) {
        error_report(FILE_NAME, fun_name, "timer model is NULL.");
        return -1;
    }

    return 0;
}

timer_view* timer_view_create(timer_model* t_model, unsigned int width, unsigned int height, int shift_x)
{
    #define FUN_NAME "timer_view_create"
    if (t_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument t_model is NULL.");
        return NULL;
    }

    if (width < TIMER_WIDTH_LCURRENT || width < TIMER_WIDTH_LTOP) {
        error_report(FILE_NAME, FUN_NAME, "width is very small.");
        return NULL;
    }

    if (height < TIMER_HEIGHT * 2) {
        error_report(FILE_NAME, FUN_NAME, "height is very small.");
        return NULL;
    }

    timer_view* t_view = malloc(sizeof(*t_view));
    if (t_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "malloc error.");
        return NULL;
    }


    unsigned int w = TIMER_WIDTH_LTOP;
    unsigned int h = TIMER_HEIGHT;
    t_view->l_top = label_view_create(t_model->top_time, w, h, TIMER_TEXT_COLOR, TIMER_BACKGROUND_COLOR, TIMER_BORDER_COLOR);
    if (t_view->l_top == NULL) {
        error_report(FILE_NAME, FUN_NAME, "error label top create.");
        free(t_view);
        return NULL;
    }

    w = TIMER_WIDTH_LCURRENT;
    t_view->l_current = label_view_create(t_model->current_time, w, h, TIMER_TEXT_COLOR, TIMER_BACKGROUND_COLOR, TIMER_BORDER_COLOR);
    if (t_view->l_current == NULL) {
        error_report(FILE_NAME, FUN_NAME, "error label top create.");
        label_view_destroy(t_view->l_top);
        free(t_view);
        return NULL;
    }

    t_view->shift_x = shift_x;
    t_view->shift_y = ( height - TIMER_HEIGHT * 2 ) / 4;
    t_view->t_model = t_model;

    return t_view;

    #undef FUN_NAME
}

int timer_view_draw(timer_view* t_view)
{
    #define FUN_NAME "timer_view_draw"

    if (check_field(t_view, FUN_NAME)) {
        return -1;
    }

    int err = 0;

    if (label_view_set_text(t_view->l_top, t_view->t_model->top_time)) {
        err = -1;
    }

    if (label_view_set_text(t_view->l_current, t_view->t_model->current_time)) {
        err = -1;
    }

    if (label_view_draw(t_view->l_top, t_view->shift_x, t_view->shift_y)) {
        err = -1;
    }

    if (label_view_draw(t_view->l_current, t_view->shift_x, 3 * t_view->shift_y)) {
        err = -1;
    }

    return err;

    #undef FUN_NAME
}

int timer_view_destroy(timer_view* t_view)
{
    #define FUN_NAME "timer_view_destroy"

    if (check_field(t_view, FUN_NAME)) {
        return -1;
    }

    int err = 0;
    if (label_view_destroy(t_view->l_top)) {
        err = -1;
    }

    if (label_view_destroy(t_view->l_current)) {
        err = -1;
    }

    return err;

    #undef FUN_NAME
}

#undef FILE_NAME
