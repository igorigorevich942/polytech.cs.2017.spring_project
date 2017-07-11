#ifndef RECTANGLE_VIEW_H
#define RECTANGLE_VIEW_H

/** \file rectangle_view.h
\brief Файл, в котором опеределены функции для работы с элементом интерфейса: "прямоугольник".
*/

#include <allegro5/allegro.h>

/**
Создание прямоугольника.
\param[in] color - цвет.
\param[in] width - ширина.
\param[in] height - высота.
\return Адрес, созданного прямоугольника. \n
        NULL, если во время создания прямоугольника произошла ошибка.
*/
ALLEGRO_BITMAP* rectangle_view_create(ALLEGRO_COLOR color, unsigned int width, unsigned int height);

/**
Рисование треугольника.
\param[in] r_view - адрес прямоугольника, который нужно нарисовать.
\param[in] x - координата рисования верхнего левого угла прямоугольника по оси OX.
\param[in] y - координата рисования верхнего левого угла прямоугольника по оси OY.
\return Ноль, если прямоугольник был успешно отрисован. \n
        Ненулевое число, если во время рисования произошла ошибка.
*/
int rectangle_view_draw(ALLEGRO_BITMAP* r_view, unsigned int x, unsigned int y);

/**
Удаление прямоугольника.
\param[in] r_view - адрес прямоугольника, который нужно удалить.
\return Ноль, если удаление прошло успешно. \n
        Ненулевое число, если во время удаления произошла ошибка.
*/
int rectangle_view_destroy(ALLEGRO_BITMAP* r_view);


#endif // RECTANGLE_VIEW_H
