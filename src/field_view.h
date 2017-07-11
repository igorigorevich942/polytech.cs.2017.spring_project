#ifndef FIELD_VIEW_H
#define FIELD_VIEW_H

/** \file field_view.h
\brief Файл, в котором опеределены функции для работы с отображением игрового поля.
*/

#include "player_model.h"
#include "player_view.h"
#include "label_view.h"

#include <allegro5/allegro.h>

#define FIELD_BORDER_SIZE 10 ///< Размер рамки.
#define FIELD_HEGIHT_FINISH 70 ///< Высота надписи "Finish".
#define FIELD_BORDER_COLOR al_map_rgb(0, 0, 0) ///< Цвет рамки.
#define FIELD_BACKGROUND_COLOR al_map_rgb(255, 255, 255) ///< Цвет фона.
#define FIELD_FINISH_COLOR al_map_rgb(255, 99, 71) ///< Цвет надписи "Finish".

/**
\brief Структура, которая описывает отображение игрового поля.
*/
struct field_view {
    ALLEGRO_BITMAP* r_backgroud; ///< Адрес прямоугольника фона.
    ALLEGRO_BITMAP* r_border; ///< Адрес прямоугольника рамки.
    player_view* p_view;  ///< Адрес отображения игрока.
    label_view* l_finish; ///< Адрес надпси "Finish".
};

typedef struct field_view field_view;

/**
Создание отображения игрового поля.
\param[in] p_model - модель игрока.
\param[in] width - ширина поля.
\param[in] height - высота поля.
\return Адрес, созданного отображения игрового поля. \n
        NULL, если во время создания отображения игрового поля произошла ошибка.
*/
field_view* field_view_create(player_model* p_model, unsigned int width, unsigned int height);

/**
Рисование отображения игрового поля.
\param[in] f_view - адрес отображения игрового, которое нужно нарисовать.
\return Ноль, если отображение было успешно отрисовано. \n
        Ненулевое число, если во время рисования произошла ошибка.
*/
int field_view_draw(field_view* f_view);

/**
Удаление отображения игрового поля.
\param[in] f_view - адрес отображения игрового поля, которое нужно удалить.
\return Ноль, если удаление прошло успешно. \n
        Ненулевое число, если во время удаления произошла ошибка.
*/
int field_view_destroy(field_view* f_view);

#endif // FIELD_VIEW_H
