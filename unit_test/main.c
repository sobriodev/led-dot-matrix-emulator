#include "unity.h"
#include "common_test_suite.h"
#include "vt100_test_suite.h"
#include "device_test_suite.h"

void setUp(void)
{
    /* This can be done only for all test */
}

void tearDown(void)
{
    /* This can be done only for all test */
}

int main(void)
{
    UNITY_BEGIN();

    /* SUITE: Common */
    RUN_TEST(test_common_BitOperations_ValidResults);
    RUN_TEST(test_common_InvalidIndex_CM_IndexExists_FalseReturned);
    RUN_TEST(test_common_ValidIndex_CM_IndexExists_TrueReturned);

    /* SUITE: VT100 */
    RUN_TEST(test_vt100_InvalidLutIndexes_VT_PrintCommand_ErrorReturned);
    RUN_TEST(test_vt100_VT_PrintCommand_Works);

    /* SUITE: Device */
    RUN_TEST(test_device_MallocFailure_DEV_CreateDevice_ErrReturned);

    return UNITY_END();
}
