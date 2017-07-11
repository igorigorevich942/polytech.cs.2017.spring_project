/** \file field_view.c
\brief Файл, в котором реализованы функции для работы с отображением игрового поля.

\def FUN_NAME 
\brief Имя текущей функции.
*/

#include "field_view.h"
#include "rectangle_view.h"
#include "error_report.h"

#include <stdlib.h>

#define FILE_NAME "field_view.c" ///< Текущие имя файла.

static int field_view_check_field(field_view* f_view, const char* fun_name)
{
    if (f_view == NULL) {
        error_report(FILE_NAME, fun_name, "argument f_view is NULL.");
        return -1;
    }

    if (f_view->r_backgroud == NULL) {
        error_report(FILE_NAME, fun_name, "rectangle background is NULL.");
        return -1;
    }

    if (f_view->r_border == NULL) {
        error_report(FILE_NAME, fun_name, "rectangle border is NULL.");
        return -1;
    }

    if (f_view->p_view == NULL) {
        error_report(FILE_NAME, fun_name, "player view is NULL.");
        return -1;
    }

    return 0;
}

field_view* field_view_create(player_model* p_model, unsigned int width, unsigned int height)
{
    #define FUN_NAME "field_view_create"

    if (p_model == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument p_model is NULL.");
        return NULL;
    }

    if (width < PLAYER_SIZE + FIELD_BORDER_SIZE * 2) {
        error_report(FILE_NAME, FUN_NAME, "width is very small.");
        return NULL;
    }

    if (height < PLAYER_SIZE + FIELD_BORDER_SIZE * 2 + FIELD_HEGIHT_FINISH) {
        error_report(FILE_NAME, FUN_NAME, "height is very small.");
        return NULL;
    }

    field_view* f_view = malloc(sizeof(*f_view));
    if (f_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "malloc error.");
        return NULL;
    }

    unsigned int x_start = width / 2 - PLAYER_SIZE / 2;
    unsigned int y_start = height - FIELD_BORDER_SIZE - PLAYER_SIZE;
    unsigned int y_finish = FIELD_BORDER_SIZE + FIELD_HEGIHT_FINISH;
    f_view->p_view = player_view_create(p_model, x_start, y_start, y_finish);

    if (f_view->p_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "error create player view.");
        free(f_view);
        return NULL;
    }

    unsigned int w = width - FIELD_BORDER_SIZE * 2;
    unsigned int h = height - FIELD_BORDER_SIZE * 2;
    f_view->r_backgroud = rectangle_view_create(FIELD_BACKGROUND_COLOR, w, h);
    if (f_view->r_backgroud == NULL) {
        error_report(FILE_NAME, FUN_NAME, "error create rectangle background.");
        player_view_destroy(f_view->p_view);
        free(f_view);
        return NULL;
    }

    f_view->r_border = rectangle_view_create(FIELD_BORDER_COLOR, width, height);
    if (f_view->r_border == NULL) {
        error_report(FILE_NAME, FUN_NAME, "error create rectangle border.");
        rectangle_view_destroy(f_view->r_backgroud);
        player_view_destroy(f_view->p_view);
        free(f_view);
        return NULL;
    }

    w = width - 2 * FIELD_BORDER_SIZE;
    h = FIELD_HEGIHT_FINISH;
    f_view->l_finish = label_view_create("FINISH", w, h, FIELD_FINISH_COLOR, FIELD_BACKGROUND_COLOR, FIELD_BORDER_COLOR);
    if (f_view->l_finish == NULL) {
        error_report(FILE_NAME, FUN_NAME, "error create label finish.");
        rectangle_view_destroy(f_view->r_backgroud);
        rectangle_view_destroy(f_view->r_border);
        player_view_destroy(f_view->p_view);
        free(f_view);
        return NULL;
    }

    return f_view;
    #undef FUN_NAME
}

int field_view_draw(field_view* f_view)
{
    #define FUN_NAME "field_view_draw"

    if (field_view_check_field(f_view, FUN_NAME)) {
        return -1;
    }

    int err = 0;

    int x = 0;
    int y = 0;
    if (rectangle_view_draw(f_view->r_border, 0, 0)) {
        err = -1;
    }

    x = FIELD_BORDER_SIZE;
    y = FIELD_BORDER_SIZE;
    if (rectangle_view_draw(f_view->r_backgroud, x, y)) {
        err = -1;
    }

    if (label_view_draw(f_view->l_finish, x, y)) {
        err = -1;
    }

    if (player_view_draw(f_view->p_view)) {
        err = -1;
    }

    return err;

    #undef FUN_NAME
}

int field_view_destroy(field_view* f_view)
{
    #define FUN_NAME "field_view_destroy"

    if (field_view_check_field(f_view, FUN_NAME)) {
        return -1;
    }

    int err = 0;

    if (rectangle_view_destroy(f_view->r_backgroud)) {
        err = -1;
    }

    if (rectangle_view_destroy(f_view->r_border)) {
        err = -1;
    }

    if (player_view_destroy(f_view->p_view)) {
        err = -1;
    }

    if (label_view_destroy(f_view->l_finish)) {
        err = -1;
    }
    free(f_view);

    return err;

    #undef FUN_NAME
}

#undef FILE_NAME
