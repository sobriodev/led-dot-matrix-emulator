#include "register_test_suite.h"
#include "register.h"
#include "unity.h"
#include <string.h>

/* ------------------------------------------------------------------------- */
/* ------------------------- REG_MemoryInit() CASES ------------------------ */
/* ------------------------------------------------------------------------- */

void test_register_ByDefault_REG_MemoryInit_PerformsCorrectInit()
{
    /* On initial power-up the registers have to contain specific data */
    REG_Memory memory;
    REG_MemoryInit(&memory);

    /* RAM registers */
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.digit0);
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.digit1);
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.digit2);
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.digit3);
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.digit4);
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.digit5);
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.digit6);
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.digit7);

    /* Config registers */
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.decodeMode);
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.intensity);
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.scanLimit);
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.shutdown);
    TEST_ASSERT_EQUAL_UINT8(0x00, memory.displayTest);
}

/* ------------------------------------------------------------------------- */
/* --------------------------- REG_Write() CASES --------------------------- */
/* ------------------------------------------------------------------------- */

void test_register_InvalidRegAddr_REG_Write_ErrReturned()
{
    /* Memory to be modified */
    REG_Memory memory;
    REG_MemoryInit(&memory);

    /* Memory to be compared */
    REG_Memory memoryCmp;
    REG_MemoryInit(&memoryCmp);

    u8 dummyState = 0xFF;
    TEST_ASSERT_EQUAL_INT32(
                REG_StatusWrongAddr,
                REG_Write(&memory, REG_AddrNoOp -1, dummyState));

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusWrongAddr,
                REG_Write(&memory, REG_AddrDisplayTest + 1, dummyState));

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusWrongAddr,
                REG_Write(&memory, 0x47184, dummyState));

    /* Memory should not be modified */
    TEST_ASSERT_EQUAL_INT32(0, memcmp(&memory, &memoryCmp, sizeof(REG_Memory)));
}

void test_register_InvalidRegState_REG_Write_ErrReturned()
{
    /* Memory to be modified */
    REG_Memory memory;
    REG_MemoryInit(&memory);

    /* Memory to be compared */
    REG_Memory memoryCmp;
    REG_MemoryInit(&memoryCmp);

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusWrongState,
                REG_Write(
                    &memory,
                    REG_AddrDecodeMode,
                    REG_DecodeModeDigit0To3 + 1));

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusWrongState,
                REG_Write(
                    &memory,
                    REG_AddrIntensity,
                    REG_Intensity31_32 + 1));

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusWrongState,
                REG_Write(
                    &memory,
                    REG_AddrScanLimit,
                    REG_ScanLimitDigit0 - 1));

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusWrongState,
                REG_Write(
                    &memory,
                    REG_AddrShutdown,
                    0xFF));

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusWrongState,
                REG_Write(
                    &memory,
                    REG_AddrDisplayTest,
                    0xAC));

    /* Memory should not be modified */
    TEST_ASSERT_EQUAL_INT32(0, memcmp(&memory, &memoryCmp, sizeof(REG_Memory)));
}

void test_register_ValidRegAddr_REG_Write_MemoryUpdated()
{
    REG_Memory memory;
    REG_MemoryInit(&memory);

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusOk,
                REG_Write(&memory, REG_AddrDigit0, 0xFA));

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusOk,
                REG_Write(&memory, REG_AddrDecodeMode, REG_DecodeModeDigit0));

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusOk,
                REG_Write(&memory, REG_AddrIntensity, REG_Intensity29_32));

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusOk,
                REG_Write(&memory, REG_AddrScanLimit, REG_ScanLimitDigit0To5));

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusOk,
                REG_Write(&memory, REG_AddrShutdown, REG_ShutdownOff));

    TEST_ASSERT_EQUAL_INT32(
                REG_StatusOk,
                REG_Write(&memory, REG_AddrDisplayTest, REG_DisplayTestOn));

    /* Check whether new values are set */
    TEST_ASSERT_EQUAL_INT32(0xFA, memory.digit0);
    TEST_ASSERT_EQUAL_INT32(REG_DecodeModeDigit0, memory.decodeMode);
    TEST_ASSERT_EQUAL_INT32(REG_Intensity29_32, memory.intensity);
    TEST_ASSERT_EQUAL_INT32(REG_ScanLimitDigit0To5, memory.scanLimit);
    TEST_ASSERT_EQUAL_INT32(REG_ShutdownOff, memory.shutdown);
    TEST_ASSERT_EQUAL_INT32(REG_DisplayTestOn, memory.displayTest);
}

void test_register_NoOpRegAddr_REG_Write_NothingIsDone()
{
    /* Memory to be modified */
    REG_Memory memory;
    REG_MemoryInit(&memory);

    /* Memory to be compared */
    REG_Memory memoryCmp;
    REG_MemoryInit(&memoryCmp);

    u8 dummyState = 0xAF;
    TEST_ASSERT_EQUAL_INT32(
                REG_StatusOk,
                REG_Write(&memory, REG_AddrNoOp, dummyState));

    /* Memory should not be modified */
    TEST_ASSERT_EQUAL_INT32(0, memcmp(&memory, &memoryCmp, sizeof(REG_Memory)));
}
