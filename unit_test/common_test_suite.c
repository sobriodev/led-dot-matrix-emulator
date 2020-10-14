#include "common.h"
#include "unity.h"

/* ------------------------------------------------------------------------- */
/* ------------------------- BIT OPERATION CASES --------------------------- */
/* ------------------------------------------------------------------------- */

void test_common_BitOperations_ValidResults(void)
{
    /* Bit generator */
    TEST_ASSERT_EQUAL_UINT32(1, U32_BIT(0));
    TEST_ASSERT_EQUAL_UINT32(128, U32_BIT(7));
    TEST_ASSERT_EQUAL_UINT32(2147483648, U32_BIT(31));

    /* Bit set */
    TEST_ASSERT_FALSE(U32_CHECK_BIT_SET(0, 0));
    TEST_ASSERT_FALSE(U32_CHECK_BIT_SET(15, U32_BIT(4)));
    TEST_ASSERT_TRUE(U32_CHECK_BIT_SET(1, U32_BIT(0)));
    TEST_ASSERT_TRUE(U32_CHECK_BIT_SET(255, U32_BIT(3)));
    TEST_ASSERT_TRUE(U32_CHECK_BIT_SET(4294967295, U32_BIT(31)));
}

/* ------------------------------------------------------------------------- */
/* ------------------------- CM_IndexExists() CASES ------------------------ */
/* ------------------------------------------------------------------------- */

void test_common_InvalidIndex_CM_IndexExists_FalseReturned(void)
{
    TEST_ASSERT_FALSE(CM_IndexExists(0, 0));
    TEST_ASSERT_FALSE(CM_IndexExists(1, 0));

    TEST_ASSERT_FALSE(CM_IndexExists(-1, 1));
    TEST_ASSERT_FALSE(CM_IndexExists(2, 1));
    TEST_ASSERT_FALSE(CM_IndexExists(10, 1));
    TEST_ASSERT_FALSE(CM_IndexExists(-100, 1));

    TEST_ASSERT_FALSE(CM_IndexExists(-10, 10));
    TEST_ASSERT_FALSE(CM_IndexExists(10, 10));
    TEST_ASSERT_FALSE(CM_IndexExists(11, 10));
    TEST_ASSERT_FALSE(CM_IndexExists(10, 10));
}

void test_common_ValidIndex_CM_IndexExists_TrueReturned(void)
{
    TEST_ASSERT_TRUE(CM_IndexExists(0, 1));

    TEST_ASSERT_TRUE(CM_IndexExists(0, 2));
    TEST_ASSERT_TRUE(CM_IndexExists(1, 2));

    TEST_ASSERT_TRUE(CM_IndexExists(0, 6));
    TEST_ASSERT_TRUE(CM_IndexExists(1, 6));
    TEST_ASSERT_TRUE(CM_IndexExists(2, 6));
    TEST_ASSERT_TRUE(CM_IndexExists(3, 6));
    TEST_ASSERT_TRUE(CM_IndexExists(4, 6));
    TEST_ASSERT_TRUE(CM_IndexExists(5, 6));

    /* Signed numbers are converted to unsigned, thus it should also work */
    TEST_ASSERT_TRUE(CM_IndexExists(18446744073709551605U, -10));
}

/* ------------------------------------------------------------------------- */
/* ----------------------- CM_ValueInBounds() CASES ------------------------ */
/* ------------------------------------------------------------------------- */

void test_common_MiscValues_CM_ValueInBounds_CorrectResults()
{
    /* Values out of bounds */
    TEST_ASSERT_FALSE(CM_ValueInBounds(1, 0, 0));
    TEST_ASSERT_FALSE(CM_ValueInBounds(1, -1, 0));
    TEST_ASSERT_FALSE(CM_ValueInBounds(10, 0, 9));
    TEST_ASSERT_FALSE(CM_ValueInBounds(-1921, -19, -18));

    /* Values in bounds */
    TEST_ASSERT_TRUE(CM_ValueInBounds(0, 0, 0));
    TEST_ASSERT_TRUE(CM_ValueInBounds(0, 0, 10));
    TEST_ASSERT_TRUE(CM_ValueInBounds(-10, -10, 312));
    TEST_ASSERT_TRUE(CM_ValueInBounds(56, -10021, 56));

    /* Left > right */
    TEST_ASSERT_FALSE(CM_ValueInBounds(0, 10, -10));
    TEST_ASSERT_FALSE(CM_ValueInBounds(100, 100, -1000));
    TEST_ASSERT_FALSE(CM_ValueInBounds(87, 99, 87));
}
