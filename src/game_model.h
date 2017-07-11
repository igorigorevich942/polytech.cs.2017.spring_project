#ifndef GAME_MODEL_H
#define GAME_MODEL_H

/** \file game_model.h
\brief Файл, в котором опеределены функции для работы с моделью игры.
*/

#include "player_model.h"
#include "timer_model.h"

#include <time.h>

#define NUM_PUSH_SIZE (MAX_MN * MAX_SEC) ///< Максимальная продолжительность игры в секундах.
#define SPEED_DOWN_FACTOR 3 ///< Коэффициент расчета скорости №1.
#define SPEED_DIV_FACTOR 20 ///< Коэффициент расчета скорости №2.

///Тип нажимаемой клавиши.
enum key_type {
    LEFT,  ///< Стрелка влево.
    RIGHT, ///< Стрелка вправо.
    OTHER  ///< Другая клавиша.
};

typedef enum key_type key_type;

/**
\brief Структура, которая описывает модель игры.
*/
struct game_model {
    player_model* p_model;  ///< Адрес модели игрока.
    timer_model* t_model;   ///< Адрес модели таймеров.

    unsigned int* num_push; ///< Количество нажатий клавиш влево и вправо, в каждую секунду игры.
    key_type last_key;      ///< Тип клавиши нажатой в последний раз.
};

typedef struct game_model game_model;

/**
Создание модели игры.
\return Адрес, созданной модели. \n
        NULL, если во время создания модели произошла ошибка.
*/
game_model* game_model_create();

/**
Обработка нажатия клавиши.
\param[in,out] g_model - адрес модели, для которой обрабатывает нажатие.
\param[in] k_type - тип нажатой клавиши.
\return Ноль, если обработка прошла успешно. \n
        Ненулевое число, если во время обработки произошла ошибка.
*/
int game_model_key_down(game_model* g_model, key_type k_type);

/**
Обновление данных модели игры
\param[in,out] g_model - адрес модели игры, которую необходимо обновить.
\return Ноль, если обновление прошло успешно. \n
        Ненулевое число, если во время обновления произошла ошибка.
*/
int game_model_update(game_model* g_model);

/**
Старт игры.
\param[in,out] g_model - адрес модели игры, которую нужно запустить.
\return Ноль, если запуск прошёл успешно. \n
        Ненулевое число, если во время запуска произошла ошибка.
*/
int game_model_start(game_model* g_model);

/**
Проверка окончания игры.
\param[in] g_model - адрес модели игры, которую нужно проверить.
\return Отрицательное число, если во время проверки произошла ошибка. \n
        Ноль, если игра еще не закончилась. \n
        Положительное число, если игра закончилась.
*/
int game_model_is_end(game_model* g_model);

/**
Удаление модели игры.
\param[in] g_model - адрес модели игры, которую нужно удалить.
\return Ноль, если удаление прошло успешно. \n
        Ненулевое число, если во время удаления произошла ошибка.
*/
int game_model_destroy(game_model* g_model);

#endif // GAME_MODEL_H
