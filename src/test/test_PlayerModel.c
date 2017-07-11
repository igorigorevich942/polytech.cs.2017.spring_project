/**
\file test_PlayerModel.c
\brief Файл тестирующий модель игрока.
*/

#include "unity.h"
#include "unity_fixture.h"
#include "player_model.h"

#include <stdlib.h>

TEST_GROUP(TestPlayerModel);

TEST_GROUP_RUNNER(TestPlayerModel)
{
    RUN_TEST_CASE(TestPlayerModel, FunctionCreate);
    RUN_TEST_CASE(TestPlayerModel, FunctionDestroy);
    RUN_TEST_CASE(TestPlayerModel, FunctionIsEnd);
    RUN_TEST_CASE(TestPlayerModel, FunctionUpdate);
}

TEST_SETUP(TestPlayerModel)
{}

TEST_TEAR_DOWN(TestPlayerModel)
{}


/**
Функция, которая тестирует функцию player_model_create.
*/
TEST(TestPlayerModel, FunctionCreate)
{
    TEST_ASSERT_NOT_NULL(player_model_create());
}

/**
Функция, которая тестирует функцию player_model_destroy.
*/
TEST(TestPlayerModel, FunctionDestroy)
{
    TEST_ASSERT_NOT_EQUAL(player_model_destroy(NULL), 0);
    player_model* p_model = player_model_create();
    TEST_ASSERT_EQUAL(player_model_destroy(p_model), 0);
}

/**
Функция, которая тестирует функцию player_model_update.
*/
TEST(TestPlayerModel, FunctionUpdate)
{
    player_model* p_model = player_model_create();   
    TEST_ASSERT_NOT_EQUAL(player_model_update(p_model, -1), 0);    
    TEST_ASSERT_NOT_EQUAL(player_model_update(p_model, -0.1), 0);        
    TEST_ASSERT_EQUAL(player_model_update(p_model, 0), 0);    
    TEST_ASSERT_NOT_EQUAL(player_model_update(NULL, -1), 0);    
    TEST_ASSERT_NOT_EQUAL(player_model_update(NULL, -0.1), 0);  
    TEST_ASSERT_NOT_EQUAL(player_model_update(NULL, 0), 0);                 
    p_model->pos = DISTANCE_LENGTH + 1;
    TEST_ASSERT_NOT_EQUAL(player_model_update(p_model, 0), 0);          
    player_model_destroy(p_model);
}

/**
Функция, которая тестирует функцию player_model_is_end.
*/
TEST(TestPlayerModel, FunctionIsEnd)
{
    player_model* p_model = player_model_create();   
    TEST_ASSERT_EQUAL(player_model_is_end(p_model), 0);  
    p_model->pos = DISTANCE_LENGTH;
    TEST_ASSERT_NOT_EQUAL(player_model_is_end(p_model), 0);      
    player_model_destroy(p_model);
}


