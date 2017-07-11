/** \file game_view.c
\brief Файл, в котором опеределены функции для работы с отображением игры.

\def FUN_NAME 
\brief Имя текущей функции.
*/

#include "game_view.h"
#include "error_report.h"

#include <stdlib.h>
#include <stdbool.h>

#define FILE_NAME "game_view.c" ///< Имя текущего файла.

static int init_allegro_field(game_view* g_view)
{
    #define FUN_NAME "init_allegro_field"

    g_view->timer = al_create_timer(1.0 / FPS);
    if (!(g_view->timer)) {
        error_report(FILE_NAME, FUN_NAME, "error create timer.");
        return -1;
    }

    g_view->display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!(g_view->display)) {
        error_report(FILE_NAME, FUN_NAME, "error create display.");
        return -1;
    }

    g_view->event_queue = al_create_event_queue();
    if (!(g_view->event_queue)) {
        error_report(FILE_NAME, FUN_NAME, "error create event_queue.");
        return -1;
    }

    return 0;

    #undef FUN_NAME
}

static int init_view_and_model_field(game_view* g_view)
{
    #define FUN_NAME "init_view_and_model_field"

    label_view_init_font();

    g_view->g_model = game_model_create();
    if (!(g_view->g_model)) {
        error_report(FILE_NAME, FUN_NAME, "error create game_model.");
        return -1;
    }

    unsigned int w = SCREEN_WIDTH / 2;
    unsigned int h = SCREEN_HEIGHT;
    g_view->f_view = field_view_create(g_view->g_model->p_model, w, h);
    if (!(g_view->f_view)) {
        error_report(FILE_NAME, FUN_NAME, "error create field_view.");
        return -1;
    }

    unsigned int shift_x = (SCREEN_WIDTH * 5) / 8;
    w = SCREEN_WIDTH - shift_x;
    g_view->t_view = timer_view_create(g_view->g_model->t_model, w, h, shift_x);
    if (!(g_view->t_view)) {
        error_report(FILE_NAME, FUN_NAME, "error create timer view.");
        return -1;
    }

    return 0;

    #undef FUN_NAME
}

static int draw(game_view* g_view)
{
    al_clear_to_color(GAME_V_BACKGROUND);

    int err1 = field_view_draw(g_view->f_view);
    int err2 = timer_view_draw(g_view->t_view);

    al_flip_display();

    return (err1) ? err1 : err2;
}

game_view* game_view_create()
{
    #define FUN_NAME "game_view_create"

    game_view* g_view = malloc(sizeof(*g_view));
    if (g_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "error malloc.");
        return NULL;
    }

    g_view->display = NULL;
    g_view->event_queue = NULL;
    g_view->timer = NULL;

    g_view->g_model = NULL;
    g_view->f_view = NULL;
    g_view->t_view = NULL;

    int err = init_allegro_field(g_view);
    err = (err) ? err : init_view_and_model_field(g_view);

    if (err) {
        game_view_destroy(g_view);
        error_report(FILE_NAME, FUN_NAME, "error create game model.");
        return NULL;
    }

    al_register_event_source(g_view->event_queue, al_get_display_event_source(g_view->display));
    al_register_event_source(g_view->event_queue, al_get_timer_event_source(g_view->timer));
    al_register_event_source(g_view->event_queue, al_get_keyboard_event_source());

    al_set_target_bitmap(al_get_backbuffer(g_view->display));
    draw(g_view);

    return g_view;

    #undef FUN_NAME
}

static int wait_enter(game_view* g_view)
{
    while (true) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(g_view->event_queue, &ev);
        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            return 1;
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                return 0;
            }
        }
    }
}

int game_view_start(game_view* g_view)
{
    if (wait_enter(g_view)) return 1;
    game_model_start(g_view->g_model);
    al_start_timer(g_view->timer);

    while (!(game_model_is_end(g_view->g_model))) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(g_view->event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            return 1;
        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                game_model_key_down(g_view->g_model, LEFT);
            } else if (ev.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                game_model_key_down(g_view->g_model, RIGHT);
            }
        }

        game_model_update(g_view->g_model);

        draw(g_view);
    }

    if (game_model_is_end(g_view->g_model)) {
        timer_model_save_result(g_view->g_model->t_model);
        draw(g_view);
    }

    wait_enter(g_view);

    return 0;
}

int game_view_destroy(game_view* g_view)
{
    label_view_destroy_font();

    if (g_view->display) {
        al_destroy_display(g_view->display);
    }

    if (g_view->event_queue) {
        al_destroy_event_queue(g_view->event_queue);
    }

    if (g_view->timer) {
        al_destroy_timer(g_view->timer);
    }

    int err1 = 0;
    int err2 = 0;
    int err3 = 0;
    if (g_view->g_model) {
        err1 = game_model_destroy(g_view->g_model);
    }

    if (g_view->f_view) {
        err2 = field_view_destroy(g_view->f_view);
    }

    if (g_view->t_view) {
        err3 = timer_view_destroy(g_view->t_view);
    }

    free(g_view);

    return (err1 || err2 || err3) ? -1 : 0;
}

#undef FILE_NAME
