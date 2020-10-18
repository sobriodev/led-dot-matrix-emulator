#include "device_test_suite.h"
#include "device.h"
#include "mem.h"
#include "mem_mock.h"
#include "unity.h"

/* ------------------------------------------------------------------------- */
/* ---------------------------- PRIVATE FUNCTIONS -------------------------- */
/* ------------------------------------------------------------------------- */

/* Helper function for generating expected line string */
static void FillStrWithCh(char* buff, char ch, size len)
{
    for (size i = 0; i < len; i++) {
        buff[i] = ch;
    }
}

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

/* ------------------------------------------------------------------------- */
/* ------------------------- DEV_GetLineStr() CASES ------------------------ */
/* ------------------------------------------------------------------------- */

void test_device_NullPassed_DEV_GetLineStr_ErrReturned(void)
{
    DEV_Line dummyLine = DEV_Line0;
    char buff[DEV_LINE_BUFFER_LEN] = {0};
    TEST_ASSERT_EQUAL_INT32(
                DEV_StatusNullPtr,
                DEV_GetLineStr(NULL, dummyLine, buff));

    /* Buffer should be not modified after operation */
    TEST_ASSERT_EQUAL_STRING("", buff);
}

void test_device_WrongLine_DEV_GetLineStr_ErrReturned(void)
{
    const u32 wrongLines[] =
    {
        DEV_Line0 - 1,
        DEV_Line7 + 1,
        0x7813,
        -9401
    };

    DEV_Info* device;
    DEV_CreateDevice(&device, DEV_ColorGreen, MEM_Malloc);
    char buff[DEV_LINE_BUFFER_LEN] = {0};

    for (size i = 0; i < CM_COUNT_OF(wrongLines); i++) {
        DEV_Status status = DEV_GetLineStr(device, wrongLines[i], buff);
        TEST_ASSERT_EQUAL_INT32(DEV_StatusWrongLine, status);

        /* Buffer should be not modified after operation */
        TEST_ASSERT_EQUAL_STRING("", buff);
    }
    DEV_DestroyDevice(&device);
}

void test_device_ByDefault_DEV_GetLineStr_CorrectStrReturned(void)
{
    DEV_Info* device;
    DEV_CreateDevice(&device, DEV_ColorGreen, MEM_Malloc);
    char buff[DEV_LINE_BUFFER_LEN] = {0};

    /* Generate expected string */
    char defaultStr[DEV_LINE_BUFFER_LEN] = {0};
    FillStrWithCh(
            defaultStr,
            DEV_STR_FORMAT_CHAR_LED_OFF,
            DEV_LEDS);

    /* Do test */
    for (size i = DEV_Line0; i <= DEV_Line7; i++) {
        DEV_Status status = DEV_GetLineStr(device, i, buff);
        TEST_ASSERT_EQUAL_INT32(DEV_StatusOk, status);
        TEST_ASSERT_EQUAL_STRING(defaultStr, buff);
    }
    DEV_DestroyDevice(&device);
}

void test_device_DigitModified_DEV_GetLineStr_CorrectStrReturned(void)
{
    /* TODO there must be a function to modify on/off chars */
}

/* ------------------------------------------------------------------------- */
/* ----------------------- DEV_SetLineFormatCh() CASES --------------------- */
/* ------------------------------------------------------------------------- */

void test_device_NewFormatCh_DEV_SetLineFormatCh_SetCorrectly(void)
{
    /* New character set */
    DEV_StrFormatChars newCh;
    newCh.charLedOff = '_';
    newCh.charLedOn = 'x';

    DEV_Info* device;
    DEV_CreateDevice(&device, DEV_ColorGreen, MEM_Malloc);
    DEV_SetLineFormatCh(device, &newCh);

    TEST_ASSERT_EQUAL_CHAR('_', device->strFormatChars.charLedOff);
    TEST_ASSERT_EQUAL_CHAR('x', device->strFormatChars.charLedOn);

    DEV_DestroyDevice(&device);
}
