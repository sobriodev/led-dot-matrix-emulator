#include <stdio.h>
#include "vt100.h"
#include "unity.h"

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_test(void)
{
    TEST_ASSERT_TRUE(1);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_test);
    return UNITY_END();
}
