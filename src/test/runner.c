#include "unity.h"
#include "unity_fixture.h"

/** \file runner.c
\brief Функция запуска всех тестов.
*/

static void RunAllTests(void)
{
    RUN_TEST_GROUP(TestPlayerModel);
    RUN_TEST_GROUP(TestTimerModel);
    RUN_TEST_GROUP(TestGameModel);
}

int main(int argc, const char * argv[])
{
    return UnityMain(argc, argv, RunAllTests);
}
