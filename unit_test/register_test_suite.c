#include "register_test_suite.h"
#include "register.h"
#include "unity.h"
#include <string.h>

/* ------------------------------------------------------------------------- */
/* --------------------------- PRIVATE FUNCTIONS --------------------------- */
/* ------------------------------------------------------------------------- */

/* Test if register memory was not modified */
static void AssertRegMemoryNotModified(const REG_Memory* memory)
{
    REG_Memory memoryCmp;
    REG_MemoryInit(&memoryCmp);

    TEST_ASSERT_EQUAL_INT32(0, memcmp(memory, &memoryCmp, sizeof(REG_Memory)));
}

/* ------------------------------------------------------------------------- */
/* ------------------------- REG_MemoryInit() CASES ------------------------ */
/* ------------------------------------------------------------------------- */

void test_register_ByDefault_REG_MemoryInit_PerformsCorrectInit()
{
    REG_Memory memory;
    REG_MemoryInit(&memory);

    /* On initial power-up the registers have to contain specific data */

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

    /* Array of wrong addresses */
    const u32 wrongAddr[] =
    {
        (REG_AddrNoOp -1),
        (REG_AddrDisplayTest + 1),
        0x47184,
        -4143
    };

    u8 dummyState = 0xFF;
    for (size i = 0; i < COUNT_OF(wrongAddr); i++) {
        REG_Status status = REG_Write(&memory, wrongAddr[i], dummyState);
        TEST_ASSERT_EQUAL_INT32(REG_StatusWrongAddr, status);
    }

    /* Eventually memory should not be modified */
    AssertRegMemoryNotModified(&memory);
}

void test_register_InvalidRegState_REG_Write_ErrReturned()
{
    /* Memory to be modified */
    REG_Memory memory;
    REG_MemoryInit(&memory);

    /* Array of wrong (address, wrong state) pairs */
    const u32 wrongAddrStatePair[][5] =
    {
        {REG_AddrDecodeMode, REG_DecodeModeDigit0To3 + 1},
        {REG_AddrIntensity, REG_Intensity31_32 + 1},
        {REG_AddrScanLimit, REG_ScanLimitDigit0 - 1},
        {REG_AddrShutdown, 0xFF},
        {REG_AddrDisplayTest, 0xAC}

    };

    for (size i = 0 ; i < COUNT_OF(wrongAddrStatePair); i++) {
        REG_Status status = REG_Write(
                                &memory,
                                wrongAddrStatePair[i][0],
                                wrongAddrStatePair[i][1]);
        TEST_ASSERT_EQUAL_INT32(REG_StatusWrongState, status);
    }

    /* Eventually memory should not be modified */
    AssertRegMemoryNotModified(&memory);
}

void test_register_ValidRegAddr_REG_Write_MemoryUpdated()
{
    /* Struct for keeping test params */
    typedef struct
    {
        u8* regMemory;
        REG_Addr regAddr;
        u8 regState;
    } TestParams;

    /* Init memory */
    REG_Memory memory;
    REG_MemoryInit(&memory);

    const TestParams testParams[] =
    {
        {&memory.digit0, REG_AddrDigit0, 0xFA},
        {&memory.digit7, REG_AddrDigit7, 0xBB},
        {&memory.decodeMode, REG_AddrDecodeMode, REG_DecodeModeDigit0},
        {&memory.intensity, REG_AddrIntensity, REG_Intensity29_32},
        {&memory.scanLimit, REG_AddrScanLimit, REG_ScanLimitDigit0To5},
        {&memory.shutdown, REG_AddrShutdown, REG_ShutdownOff},
        {&memory.displayTest, REG_AddrDisplayTest, REG_DisplayTestOn}
    };

    for (size i = 0; i < COUNT_OF(testParams); i++) {
        REG_Status status = REG_Write(
                                &memory,
                                testParams[i].regAddr,
                                testParams[i].regState);
        TEST_ASSERT_EQUAL_INT32(REG_StatusOk, status);

        /* Check if state is saved */
        TEST_ASSERT_EQUAL_UINT8(
                    testParams[i].regState,
                    *testParams[i].regMemory);
    }
}

void test_register_NoOpRegAddr_REG_Write_NothingIsDone()
{
    /* Memory to be modified */
    REG_Memory memory;
    REG_MemoryInit(&memory);

    u8 dummyState = 0xAF;
    TEST_ASSERT_EQUAL_INT32(
                REG_StatusOk,
                REG_Write(&memory, REG_AddrNoOp, dummyState));

    /* Eventually memory should not be modified */
    AssertRegMemoryNotModified(&memory);
}
