#ifndef GAME_VIEW_H
#define GAME_VIEW_H

/** \file game_view.h
\brief Файл, в котором опеределены функции для работы с отображением игры.
*/


#include "game_model.h"
#include "field_view.h"
#include "timer_view.h"

#include <allegro5/allegro.h>

#define FPS 60 ///< Частота обновления кадров в секунду.
#define SCREEN_WIDTH 800 ///< Ширина экрана.
#define SCREEN_HEIGHT 600 ///< Высота экрана.
#define GAME_V_BACKGROUND al_map_rgb(255, 255, 255) ///< Цвет фона.

/**
\brief Структура, которая описывает отображение игры.
*/
struct game_view {
    game_model* g_model; ///< Модель игры.
    timer_view* t_view;  ///< Отображение таймеров.
    field_view* f_view;  ///< Отображение поля игры.

    ALLEGRO_DISPLAY* display;         ///< Адрес дисплея.
    ALLEGRO_EVENT_QUEUE* event_queue; ///< Адрес очереди событий.
    ALLEGRO_TIMER* timer;             ///< Адрес таймера ALLEGRO.
}; 

typedef struct game_view game_view;

/**
Создание отображения игры.
\return Адрес, созданного отображения игры. \n
        NULL, если во время создания отображения игры произошла ошибка.
*/
game_view* game_view_create();

/**
Старт игры.
\param[in,out] g_view - адрес отображения игры, которую нужно начать.
\return Ноль, если игра успешно закончилась. \n
        Ненулево число, если игра было преджевременно прекращена.
*/
int game_view_start(game_view* g_view);

/**
Удаление отображения игры.
\param[in] g_view - адрес отображения игры, которое нужно удалить.
\return Ноль, если удаление прошло успешно. \n
        Ненулевое число, если во время удаления произошла ошибка.
*/
int game_view_destroy(game_view* g_view);

#endif // GAME_VIEW_H
