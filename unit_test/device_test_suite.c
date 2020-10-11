#include "device_test_suite.h"
#include "device.h"
#include "mem.h"
#include "mem_mock.h"
#include "unity.h"

/* ------------------------------------------------------------------------- */
/* ------------------------ DEV_CreateDevice() CASES ----------------------- */
/* ------------------------------------------------------------------------- */

void test_device_MallocFailure_DEV_CreateDevice_ErrReturned()
{
    DEV_Status status;
    DEV_Info *devInfo;
    status = DEV_CreateDevice(&devInfo, DEV_ColorGreen, MEM_MallocFailMock);

    TEST_ASSERT_EQUAL_INT32(DEV_StatusMemErr, status);
}

void test_device_MultipleCalls_DEV_CreateDevice_CorrectIdAssigned()
{
    DEV_Status status;
    DEV_Info *devInfo;

    for (u8 i = 0; i < 10; i++) {
        status = DEV_CreateDevice(&devInfo, DEV_ColorGreen, MEM_Malloc);
        TEST_ASSERT_EQUAL_INT32(DEV_StatusOk, status);
        TEST_ASSERT_EQUAL_UINT32(i, devInfo->id);
        DEV_DestroyDevice(&devInfo);
    }
}

/* ------------------------------------------------------------------------- */
/* ------------------------ DEV_DestroyDevice() CASES ---------------------- */
/* ------------------------------------------------------------------------- */

void test_device_DevicePointer_DEV_DestroyDevice_NullAssigned()
{
    DEV_Info *devInfo;
    DEV_CreateDevice(&devInfo, DEV_ColorGreen, MEM_Malloc);
    TEST_ASSERT_NOT_NULL(devInfo);

    DEV_DestroyDevice(&devInfo);
    TEST_ASSERT_NULL(devInfo);
}
