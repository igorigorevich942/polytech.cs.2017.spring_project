/**
\file test_TimerModel.c
\brief Файл тестирующий модель таймеров.
*/

#include "unity.h"
#include "unity_fixture.h"
#include "timer_model.h"

#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

TEST_GROUP(TestTimerModel);

TEST_GROUP_RUNNER(TestTimerModel)
{
    RUN_TEST_CASE(TestTimerModel, FunctionCreate);
    RUN_TEST_CASE(TestTimerModel, FunctionDestroy);
    RUN_TEST_CASE(TestTimerModel, FunctionIsStart);
    RUN_TEST_CASE(TestTimerModel, FunctionSaveResult);
    RUN_TEST_CASE(TestTimerModel, FunctionStart);
    RUN_TEST_CASE(TestTimerModel, FunctionUpdate);
}

TEST_SETUP(TestTimerModel)
{}

TEST_TEAR_DOWN(TestTimerModel)
{}

/**
Функция, которая тестирует функцию timer_model_create.
*/
TEST(TestTimerModel, FunctionCreate)
{
    FILE*f = fopen(PATH_DATA, "w");
    fprintf(f, "02:20\n");
    fclose(f);
    
    timer_model* t_model = timer_model_create();
    TEST_ASSERT_NOT_NULL(t_model);
    TEST_ASSERT_EQUAL(strcmp(t_model->top_time, "Record: 02:20"), 0);
    timer_model_destroy(t_model);
    
    f = fopen(PATH_DATA, "w");
    fprintf(f, "00:60\n");
    fclose(f);
    
    t_model = timer_model_create();
    TEST_ASSERT_NOT_NULL(t_model);
    TEST_ASSERT_EQUAL(strcmp(t_model->top_time, "Record: ??:??"), 0);
    timer_model_destroy(t_model);
}

/**
Функция, которая тестирует функцию timer_model_create.
*/
TEST(TestTimerModel, FunctionDestroy)
{
    TEST_ASSERT_NOT_EQUAL(timer_model_destroy(NULL), 0);
    timer_model* t_model = timer_model_create();
    TEST_ASSERT_EQUAL(timer_model_destroy(t_model), 0);
}

/**
Функция, которая тестирует функцию timer_model_destroy.
*/
TEST(TestTimerModel, FunctionIsStart)
{
    timer_model* t_model = timer_model_create();
    TEST_ASSERT_EQUAL(timer_model_is_start(t_model), 0);
    timer_model_start(t_model);
    TEST_ASSERT(timer_model_is_start(t_model) > 0);
    TEST_ASSERT(timer_model_is_start(NULL) < 0);
    timer_model_destroy(t_model);
}

/**
Функция, которая тестирует функцию timer_model_save_result.
*/
TEST(TestTimerModel, FunctionSaveResult)
{
    TEST_ASSERT_NOT_EQUAL(timer_model_save_result(NULL), 0);

    timer_model* t_model = timer_model_create();
    FILE* f = fopen(PATH_DATA, "w");
    fprintf(f, "00:15\n");
    fclose(f);
    
    strcpy(t_model->current_time, "00:14");
    TEST_ASSERT_NOT_EQUAL(timer_model_save_result(t_model), 0);
    timer_model_start(t_model);
    TEST_ASSERT_EQUAL(timer_model_save_result(t_model), 0);    
    
    f = fopen(PATH_DATA, "r");
    unsigned int mn, sec;
    int k = fscanf(f, "%u:%u", &mn, &sec);
    TEST_ASSERT_EQUAL(k, 2);
    fclose(f);    
    
    TEST_ASSERT_EQUAL(mn, 0);
    TEST_ASSERT_EQUAL(sec, 14);
    
    timer_model_destroy(t_model);
}

/**
Функция, которая тестирует функцию timer_model_start.
*/
TEST(TestTimerModel, FunctionStart)
{
    TEST_ASSERT_NOT_EQUAL(timer_model_start(NULL), 0);
    timer_model* t_model = timer_model_create();
    TEST_ASSERT_EQUAL(timer_model_start(t_model), 0);
    TEST_ASSERT_NOT_EQUAL(timer_model_start(t_model), 0);
    timer_model_destroy(t_model);
}

/**
Функция, которая тестирует функцию timer_model_update.
*/
TEST(TestTimerModel, FunctionUpdate)
{
    TEST_ASSERT_NOT_EQUAL(timer_model_update(NULL, time(NULL)), 0);
    time_t t = time(NULL);
    while (difftime(t, time(NULL)) == 0);
    timer_model* t_model = timer_model_create();    
    TEST_ASSERT_NOT_EQUAL(timer_model_update(t_model, t), 0);    
    TEST_ASSERT_NOT_EQUAL(timer_model_update(t_model, time(NULL)), 0); 
    timer_model_start(t_model);       
    TEST_ASSERT_NOT_EQUAL(timer_model_update(t_model, t), 0);    
    TEST_ASSERT_EQUAL(timer_model_update(t_model, time(NULL)), 0); 
    timer_model_destroy(t_model);
}


