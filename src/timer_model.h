#ifndef TIMER_MODEL_H
#define TIMER_MODEL_H

/** \file timer_model.h
\brief Файл, в котором опеределены функции для работы с моделью таймеров.
*/

#include <time.h>

#define PATH_DATA "res/record_time.txt" ///< Путь к файлу с лучшим рекордным временем.
#define SIZE_TIME_STRING 20 ///< Максимальный размер строки, в которой хранятся данные таймеров.

#define MAX_MN 60   ///< Максимальное количество минут измеряемое таймером.
#define MAX_SEC 59  ///< Максимальное количество секунд измеряемое таймером.

/**
\brief Структура, которая описывает модель таймеров.
*/
struct timer_model {
    char top_time[SIZE_TIME_STRING];     ///< Рекорное время.
    char current_time[SIZE_TIME_STRING]; ///< Текущее время.
    time_t start_time; ///< Время пуска таймера.                      
};

typedef struct timer_model timer_model;

/**
Создание модели таймера.
\return Адрес, созданной модели. \n
        NULL, если во время создания модели произошла ошибка.
*/
timer_model* timer_model_create();

/**
Пуск таймера.
\param[in,out] t_model - адрес модели таймера, который нужно запустить.
\return Ноль, если запуск прошёл успешно. \n
        Ненулевое число, если во время запуска произошла ошибка.
*/
int timer_model_start(timer_model* t_model);

/**
Обновление данных модели таймера.
\param[in,out] t_model - адрес модели таймера, которую необходимо обновить.
\param[in] update_time - время, в которое происходит обновление.
\return Ноль, если обновление прошло успешно. \n
        Ненулевое число, если во время обновления произошла ошибка.
*/
int timer_model_update(timer_model* t_model, time_t update_time);

/**
Сохранение рекорда.
\param[in] t_model - адрес модели таймера, рекорд которой нужно сохранить.
\return Ноль, если сохранение прошло успешно. \n
        Ненулевое число, если во время сохранения произошла ошибка.
*/

int timer_model_save_result(timer_model* t_model);

/**
Удаление модели таймера.
\param[in] t_model - адрес модели таймера, которую нужно удалить.
\return Ноль, если удаление прошло успешно. \n
        Ненулевое число, если во время удаления произошла ошибка.
*/
int timer_model_destroy(timer_model* t_model);

/**
Проверка запуска таймера.
\param[in] t_model - адрес модели таймера, которую нужно проверить.
\return Отрицательное число, если во время проверки произошла ошибка. \n
        Ноль, если таймер не запущен. \n
        Положительное число, если таймер запущен.
*/
int timer_model_is_start(timer_model* t_model);

#endif // TIMER_MODEL_H
