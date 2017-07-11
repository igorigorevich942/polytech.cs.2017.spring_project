/** \file label_view.c
\brief Файл, в котором реализованы функции для работы с элементом интерфейса: "надпись".

\def FUN_NAME 
\brief Имя текущей функции.
*/

#include "label_view.h"
#include "rectangle_view.h"
#include "error_report.h"

#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#define LABEL_BORDER_SIZE 10                      ///< Размер рамки.
#define MIN_HEIGHT (LABEL_BORDER_SIZE * 2 + 10)   ///< Минимальная высота надписи.
#define MIN_WIDTH (LABEL_BORDER_SIZE * 2 + 45)    ///< Минимальная ширина надписи.
#define PATH_FONT "res/VeryConvincing.ttf"        ///< Путь к файлу со шрифтом.

#define FILE_NAME "label_view.c" ///< Имя текущего файла.

ALLEGRO_FONT* font = NULL; ///< Адрес объекта со шрифтом.

static int check_fiend(label_view *l_view, const char* fun_name)
{
    if (l_view == NULL) {
        error_report(FILE_NAME, fun_name, "l_view is NULL.");
    } else if (l_view->r_background == NULL) {
        error_report(FILE_NAME, fun_name, "r_background is NULL.");
    } else if (l_view->r_border == NULL) {
        error_report(FILE_NAME, fun_name, "r_border is NULL.");
    } else {
        return 0;
    }
    return -1;
}

int label_view_init_font()
{
    #define FUN_NAME "label_view_init_font"

    al_init_font_addon();
    al_init_ttf_addon();

    if (font) {
        label_view_destroy_font();
    }

    font = al_load_ttf_font(PATH_FONT,40,0 );
    if (font == NULL) {
        error_report(FILE_NAME, FUN_NAME, "can't load font.");
        return -1;
    }

    return 0;

    #undef FUN_NAME
}

int label_view_destroy_font()
{
    if (font) {
        al_destroy_font(font);
        font = NULL;
    }

    return 0;
}

label_view* label_view_create(const char* text, unsigned int width, unsigned int height, ALLEGRO_COLOR color_text, ALLEGRO_COLOR color_background, ALLEGRO_COLOR color_border)
{
    #define FUN_NAME "label_view_create"
    if (text == NULL) {
        error_report(FILE_NAME, FUN_NAME, "argument text is NULL.");
        return NULL;
    }

    if (strlen(text) > MAX_LEN_TEXT) {
        error_report(FILE_NAME, FUN_NAME, "text is very long.");
        return NULL;
    }

    if (width < MIN_WIDTH) {
        error_report(FILE_NAME, FUN_NAME, "argument width is incorrect.");
        return NULL;
    }

    if (height < MIN_HEIGHT) {
        error_report(FILE_NAME, FUN_NAME, "argument height is incorrect.");
        return NULL;
    }

    label_view* l_view = malloc(sizeof(*l_view));
    if (l_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "malloc error.");
        return NULL;
    }

    l_view->r_background = rectangle_view_create(color_background, width - 2 * LABEL_BORDER_SIZE, height - 2 * LABEL_BORDER_SIZE);
    if (l_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "error create r_background.");
        free(l_view);
        return NULL;
    }

    l_view->r_border = rectangle_view_create(color_border, width, height);
    if (l_view->r_border == NULL) {
        error_report(FILE_NAME, FUN_NAME, "error create r_border.");
        rectangle_view_destroy(l_view->r_background);
        free(l_view);
        return NULL;
    }

    strcpy(l_view->text, text);
    l_view->width = width;
    l_view->height = height;
    memcpy(&(l_view->color_text), &color_text, sizeof(color_text));

    return l_view;

    #undef FUN_NAME
}

int label_view_draw(label_view* l_view, unsigned int x, unsigned int y)
{
    #define FUN_NAME "label_view_draw"
    if (check_fiend(l_view, FUN_NAME)) {
        return -1;
    }

    if (font == NULL) {
        error_report(FILE_NAME, FUN_NAME, "error font not init.");
        return -1;
    }

    int err = 0;

    if (rectangle_view_draw(l_view->r_border, x, y)) {
        error_report(FILE_NAME, FUN_NAME, "error draw r_border.");
        err = 1;
    }
    if (rectangle_view_draw(l_view->r_background, x + LABEL_BORDER_SIZE, y + LABEL_BORDER_SIZE)) {
        error_report(FILE_NAME, FUN_NAME, "error draw r_background.");
        err = 1;
    }
    al_draw_text(font, l_view->color_text, x + (l_view->width / 2), y + LABEL_BORDER_SIZE, ALLEGRO_ALIGN_CENTRE, l_view->text);

    return err;

    #undef FUN_NAME
}

int label_view_set_text(label_view* l_view, const char* text)
{
    #define FUN_NAME "label_view_set_text"
    if (check_fiend(l_view, FUN_NAME)) {
        return -1;
    }

    if (strlen(text) > MAX_LEN_TEXT) {
        error_report(FILE_NAME, FUN_NAME, "text is very long.");
        return -1;
    }

    strcpy(l_view->text, text);

    return 0;

    #undef FUN_NAME

}

int label_view_destroy(label_view* l_view)
{
    #define FUN_NAME "label_view_destroy"
    if (check_fiend(l_view, FUN_NAME)) {
        return -1;
    }

    int err = 0;

    if (rectangle_view_destroy(l_view->r_background)) {
        error_report(FILE_NAME, FUN_NAME, "error destroy r_background.");
        err = -1;
    }

    if (rectangle_view_destroy(l_view->r_border)) {
        error_report(FILE_NAME, FUN_NAME, "error destroy r_border.");
        err = -1;
    }

    free(l_view);
    return err;

    #undef FUN_NAME
}

#undef FILE_NAME

