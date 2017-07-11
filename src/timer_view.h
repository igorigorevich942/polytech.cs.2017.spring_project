#ifndef TIMER_VIEW_H
#define TIMER_VIEW_H

/** \file timer_view.h
\brief Файл, в котором опеределены функции для работы с отображением таймеров.
*/

#include "timer_model.h"
#include "label_view.h"

#define TIMER_BACKGROUND_COLOR al_map_rgb(255, 255, 255) ///< Цвет фона.
#define TIMER_BORDER_COLOR al_map_rgb(0, 0, 0)   ///< Цвет рамки.
#define TIMER_TEXT_COLOR al_map_rgb(255, 99, 71) ///< Цвет текста.

#define TIMER_WIDTH_LTOP      300 ///< Ширина таймера с рекордным времен.
#define TIMER_WIDTH_LCURRENT  200 ///< Ширина таймера с текущим времен.
#define TIMER_HEIGHT          70  ///< Высота таймеров.

/**
\brief Структура, которая описывает отображение таймеров.
*/
struct timer_view {
    label_view* l_top;     ///< Адрес надписи с рекордным временем.
    label_view* l_current; ///< Адрес надписи с текущим временем.
    timer_model* t_model;  ///< Адрес модели таймеров.
    unsigned int shift_x;  ///< Смещение позиций рисования таймеров по оси OX. 
    unsigned int shift_y;  ///< Смещение позиций рисования таймеров по оси OY. 
};

typedef struct timer_view timer_view;

/**
Создание отображения таймеров.
\param[in] t_model - адрес модели таймеров.
\param[in] width  - ширина области рисования.
\param[in] height - высота области рисования.
\param[in] shift_x - смещение позиций рисования таймеров по оси OX. 
\return Адрес, созданного отображения таймеров. \n
        NULL, если во время создания отображения таймеров произошла ошибка.
*/
timer_view* timer_view_create(timer_model* t_model, unsigned int width, unsigned int height, int shift_x);

/**
Рисование отображения таймеров.
\param[in] t_view - адрес отображения таймеров, которое нужно нарисовать.
\return Ноль, если отображение было успешно отрисовано. \n
        Ненулевое число, если во время рисования произошла ошибка.
*/
int timer_view_draw(timer_view* t_view);

/**
Удаление отображения таймеров.
\param[in] t_view - адрес отображения таймеров, которое нужно удалить.
\return Ноль, если удаление прошло успешно. \n
        Ненулевое число, если во время удаления произошла ошибка.
*/
int timer_view_destroy(timer_view* t_view);

#endif // TIMER_VIEW_H
