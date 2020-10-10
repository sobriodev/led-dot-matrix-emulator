#include "device_test_suite.h"
#include "device.h"
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

