#include "register_test_suite.h"
#include "register.h"
#include "unity.h"

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
