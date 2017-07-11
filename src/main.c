/** \file main.c
\brief Файл, в котором создается и запускается игра.

\def FUN_NAME 
\brief Имя текущей функции.
*/

#include "game_view.h"
#include "error_report.h"

#include <allegro5/allegro.h>

#define FILE_NAME "main.c" ///< Текущие имя файла.

/**
Точка входа в программу.
\return Ноль, если программа успешно завершилась. \n
        Ненулевое число, если в ходе выполнения программы возникла ошибка.
*/
int main()
{
    #define FUN_NAME "main"

    if(!al_init()) {
        error_report(FILE_NAME, FUN_NAME, "failed to initialize allegro!");
        return -1;
    }

    if(!al_install_keyboard()) {
        error_report(FILE_NAME, FUN_NAME, "failed to initialize the keyboard!");
        return -1;
    }

    game_view* g_view = game_view_create();

    if (g_view == NULL) {
        error_report(FILE_NAME, FUN_NAME, "failed to create game view!");
        return -1;
    }

    game_view_start(g_view);
    game_view_destroy(g_view);

    return 0;

    #undef FUN_NAME
}

#undef FILE_NAME
