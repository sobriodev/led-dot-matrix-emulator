#include "unity.h"
#include "common_test_suite.h"
#include "vt100_test_suite.h"
#include "device_test_suite.h"
#include "register_test_suite.h"

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
    RUN_TEST(test_common_MiscValues_CM_ValueInBounds_CorrectResults);

    /* SUITE: VT100 */
    RUN_TEST(test_vt100_InvalidLutIndexes_VT_PrintCommand_ErrorReturned);
    RUN_TEST(test_vt100_VT_PrintCommand_Works);

    /* SUITE: Device */
    RUN_TEST(test_device_MallocFailure_DEV_CreateDevice_ErrReturned);
    RUN_TEST(test_device_MultipleCalls_DEV_CreateDevice_CorrectIdAssigned);
    RUN_TEST(test_device_DevicePointer_DEV_DestroyDevice_NullAssigned);
    RUN_TEST(test_device_NullPassed_DEV_GetLineStr_ErrReturned);

    /* SUITE: Register */
    RUN_TEST(test_register_NullPassed_REG_MemoryInit_ErrReturned);
    RUN_TEST(test_register_ByDefault_REG_MemoryInit_PerformsCorrectInit);
    RUN_TEST(test_register_NullPassed_REG_Write_ErrReturned);
    RUN_TEST(test_register_InvalidRegAddr_REG_Write_ErrReturned);
    RUN_TEST(test_register_InvalidRegState_REG_Write_ErrReturned);
    RUN_TEST(test_register_ValidRegAddr_REG_Write_MemoryUpdated);
    RUN_TEST(test_register_NoOpRegAddr_REG_Write_NothingIsDone);

    return UNITY_END();
}
