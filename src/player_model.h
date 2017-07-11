#ifndef PLAYER_MODEL_H
#define PLAYER_MODEL_H

/** \file player_model.h
\brief Файл, в котором опеределены функции для работы с моделью игрока.
*/

#define DISTANCE_LENGTH 1000 ///< Дистанция, которую должен пройти игрок.
#define MAX_SPEED 1000 ///< Максимальная скорость игрока.

/**
\brief Структура, которая описывает модель игрока.
*/
struct player_model {
    double pos; ///< Текущая позиция игрока, от начала координат.
};

typedef struct player_model player_model;

/**
Создание модели игрока.
\return Адрес, созданной модели. \n
        NULL, если во время создания модели произошла ошибка.
*/
player_model* player_model_create();

/**
Обновление данных модели игрока.
\param[in,out] p_model - адрес модели игрока, которую необходимо обновить.
\param[in] speed - текущая скорость игрока.
\return Ноль, если обновление прошло успешно. \n
        Ненулевое число, если во время обновления произошла ошибка.
*/
int player_model_update(player_model* p_model, double speed);

/**
Удаление модели игрока.
\param[in,out] p_model - адрес модели игрока, которую необходимо удалить.
\return Ноль, если удаление прошло успешно. \n
        Ненулевое число, если во время удаления произошла ошибка.
*/
int player_model_destroy(player_model* p_model);

/**
Проверка прохождения игроком всей дистанции.
\param[in] p_model - адрес модели игрока, данные которой небходимо проверить.
\return Отрицательное число, если во время проверки произошла ошибка. \n
        Ноль, если игрок не прошел дистанцию. \n
        Положительное число, если игрок прошел дистанцию.
*/
int player_model_is_end(player_model* p_model);

#endif // PLAYER_MODEL_H