#ifndef PLAYER_VIEW_H
#define PLAYER_VIEW_H

/** \file player_view.h
\brief Файл, в котором опеределены функции для работы с отображением игрока.
*/

#include "player_model.h"

#include <allegro5/allegro.h>

#define PLAYER_SIZE 50  ///< Размер игрока.
#define PLAYER_COLOR al_map_rgb(30, 144, 255) ///< Цвет игрока.

/**
\brief Структура, которая описывает отображение игрока.
*/
struct player_view {
    player_model* p_model;  ///< Адрес модели игрока.
    ALLEGRO_BITMAP* p_rect; ///< Адрес прямоугольника, через который отображается игрока.
    unsigned int x_start;   ///< Координата верхнего левого угла начальной позиции игрока по оси OX.
    unsigned int y_start;   ///< Координата верхнего левого угла начальной позиции игрока по оси OY.
    unsigned int y_finish;  ///< Координата верхнего левого угла конечно позиции игрока по оси OY.
};

typedef struct player_view player_view;

/**
Создание отображения игрока.
\param[in] p_model - адрес модели игрока.
\param[in] x_start - координата верхнего левого угла начальной позиции игрока по оси OX.
\param[in] y_start - координата верхнего левого угла начальной позиции игрока по оси OY.
\param[in] y_finish - координата верхнего левого угла конечно позиции игрока по оси OY.
\return Адрес, созданного отображения игрока. \n
        NULL, если во время создания отображения игрока произошла ошибка.
*/
player_view* player_view_create(player_model* p_model, unsigned int x_start, unsigned int y_start, unsigned int y_finish);

/**
Рисование отображения игрока.
\param[in] p_view - адрес отображения игрока, которое нужно нарисовать.
\return Ноль, если отображение было успешно отрисовано. \n
        Ненулевое число, если во время рисования произошла ошибка.
*/
int player_view_draw(player_view* p_view);

/**
Удаление отображения игрока.
\param[in] p_view - адрес отображения игрока, которое нужно удалить.
\return Ноль, если удаление прошло успешно. \n
        Ненулевое число, если во время удаления произошла ошибка.
*/
int player_view_destroy(player_view* p_view);

#endif // PLAYER_VIEW_H
