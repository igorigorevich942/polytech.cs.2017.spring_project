/**
\file test_GameModel.c
\brief Файл тестирующий игровую модель.
*/
#include "unity.h"
#include "unity_fixture.h"
#include "game_model.h"

#include <stdlib.h>

TEST_GROUP(TestGameModel);

TEST_GROUP_RUNNER(TestGameModel)
{
    RUN_TEST_CASE(TestGameModel, FunctionCreate);
    RUN_TEST_CASE(TestGameModel, FunctionDestroy);
    RUN_TEST_CASE(TestGameModel, FunctionIsEnd);
    RUN_TEST_CASE(TestGameModel, FunctionKeyDown);
    RUN_TEST_CASE(TestGameModel, FunctionStart);
    RUN_TEST_CASE(TestGameModel, FunctionUpdate);
}

TEST_SETUP(TestGameModel)
{}

TEST_TEAR_DOWN(TestGameModel)
{}

/**
Функция, которая тестирует функцию game_model_create.
*/
TEST(TestGameModel, FunctionCreate)
{
    game_model* g_model = game_model_create();
    TEST_ASSERT_NOT_NULL(g_model);
    game_model_destroy(g_model);
}

/**
Функция, которая тестирует функцию game_model_destroy.
*/
TEST(TestGameModel, FunctionDestroy)
{
    TEST_ASSERT_NOT_EQUAL(game_model_destroy(NULL),0);
    game_model* g_model = game_model_create();
    TEST_ASSERT_EQUAL(game_model_destroy(g_model),0);    
}

/**
Функция, которая тестирует функцию game_model_is_end.
*/
TEST(TestGameModel, FunctionIsEnd)
{
    TEST_ASSERT(game_model_is_end(NULL) < 0);
    game_model* g_model = game_model_create();
    TEST_ASSERT_EQUAL(game_model_is_end(g_model), 0);
    game_model_start(g_model);
    TEST_ASSERT_EQUAL(game_model_is_end(g_model), 0);
    g_model->p_model->pos = DISTANCE_LENGTH;
    TEST_ASSERT_NOT_EQUAL(game_model_is_end(g_model), 0);
    game_model_destroy(g_model);
}

/**
Функция, которая тестирует функцию game_model_key_down.
*/
TEST(TestGameModel, FunctionKeyDown)
{
    TEST_ASSERT_NOT_EQUAL(game_model_key_down(NULL, LEFT),0);
    TEST_ASSERT_NOT_EQUAL(game_model_key_down(NULL, RIGHT),0);
    TEST_ASSERT_NOT_EQUAL(game_model_key_down(NULL, OTHER),0);
    game_model* g_model = game_model_create();
    TEST_ASSERT_NOT_EQUAL(game_model_key_down(g_model, LEFT),0);
    TEST_ASSERT_NOT_EQUAL(game_model_key_down(g_model, RIGHT),0);
    TEST_ASSERT_NOT_EQUAL(game_model_key_down(g_model, OTHER),0);
    game_model_start(g_model);
    TEST_ASSERT_EQUAL(game_model_key_down(g_model, LEFT),0);
    TEST_ASSERT_EQUAL(game_model_key_down(g_model, RIGHT),0);
    TEST_ASSERT_NOT_EQUAL(game_model_key_down(g_model, OTHER),0);
    game_model_destroy(g_model);
}

/**
Функция, которая тестирует функцию game_model_start.
*/
TEST(TestGameModel, FunctionStart)
{
    TEST_ASSERT_NOT_EQUAL(game_model_start(NULL),0);
    game_model* g_model = game_model_create();
    TEST_ASSERT_EQUAL(game_model_start(g_model),0);
    TEST_ASSERT_NOT_EQUAL(game_model_start(g_model),0);
    game_model_destroy(g_model);
}

/**
Функция, которая тестирует функцию game_model_update.
*/
TEST(TestGameModel, FunctionUpdate)
{
    TEST_ASSERT_NOT_EQUAL(game_model_update(NULL),0);
    game_model* g_model = game_model_create();
    TEST_ASSERT_NOT_EQUAL(game_model_update(g_model),0);
    game_model_start(g_model);
    TEST_ASSERT_EQUAL(game_model_update(g_model),0);
    game_model_destroy(g_model);
}
