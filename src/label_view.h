#ifndef LABEL_VIEW_H
#define LABEL_VIEW_H

/** \file label_view.h
\brief Файл, в котором опеределены функции для работы с элементом интерфейса: "надпись".
*/

#include <allegro5/allegro.h>

#define MAX_LEN_TEXT 20 ///< Максимальное количество символов в надписи.

/**
\brief Структура, которая описывает элемент интерфейса: "надпись".
*/
struct label_view {
    char text[MAX_LEN_TEXT];      ///< Текст.
    unsigned int height;          ///< Высота.
    unsigned int width;           ///< Ширина.
    ALLEGRO_COLOR color_text;     ///< Цвет текста.  
    ALLEGRO_BITMAP* r_background; ///< Прямоугольник фона.
    ALLEGRO_BITMAP* r_border;     ///< Прямоугольник рамки.
};

typedef struct label_view label_view;

/**
Инициализация шрифта текстов надписей.
\return Ноль, если инифиализация прошла успешно. \n
        Ненулевое число, если во время инициализации произошла ошибка.

\warning Эту функцию обязательно нужно вызвать до создания элементов интерфейса "надпись".
*/
int label_view_init_font();

/**
Удаление шрифта.
\return Ноль, если удаление прошло успешно. \n
        Ненулевое число, если во время удаления произошла ошибка.

\warning Эту функцию обязательно нужно вызвать после удаления всех элементов интерфейса "надпись".
*/
int label_view_destroy_font();

/**
Создание надписи.
\param[in] text - текст.
\param[in] width - ширина.
\param[in] height - высота.
\param[in] color_text - цвет текста.
\param[in] color_background - цвет фона.
\param[in] color_border - цвет рамки.
\return Адрес, созданной надписи. \n
        NULL, если во время создания надписи произошла ошибка.
*/
label_view* label_view_create(const char* text, unsigned int width, unsigned int height, ALLEGRO_COLOR color_text, ALLEGRO_COLOR color_background, ALLEGRO_COLOR color_border);

/**
Рисование надписи.
\param[in] l_view - адрес надписи, которую нужно нарисовать.
\param[in] x - координата рисования верхнего левого угла надписи по оси OX.
\param[in] y - координата рисования верхнего левого угла надписи по оси OY.
\return Ноль, если надпись была успешно отрисована. \n
        Ненулевое число, если во время рисования произошла ошибка.
*/
int label_view_draw(label_view* l_view, unsigned int x, unsigned int y);

/**
Изменение текста надписи.
\param[in,out] l_view - адрес надписи, текст которой нужно изменить.
\param[in] text - новый текст надписи.
\return Ноль, если текст надписи был успешно изменен. \n
        Ненулевое число, если во время изменения текста произошла ошибка.
*/
int label_view_set_text(label_view* l_view, const char* text);

/**
Удаление надписи.
\param[in] l_view - адрес надписи, которую нужно удалить.
\return Ноль, если удаление прошло успешно. \n
        Ненулевое число, если во время удаления произошла ошибка.
*/
int label_view_destroy(label_view* l_view);

#endif // LABEL_VIEW_H
