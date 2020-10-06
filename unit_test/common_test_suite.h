#ifndef COMMON_TEST_SUITE_H
#define COMMON_TEST_SUITE_H

#if defined(__cplusplus)
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/* ------------------------- BIT OPERATION CASES --------------------------- */
/* ------------------------------------------------------------------------- */

void test_common_BitOperations_ValidResults(void);

/* ------------------------------------------------------------------------- */
/* ------------------------ CM_IndexExists() CASES ------------------------- */
/* ------------------------------------------------------------------------- */

void test_common_InvalidIndex_CM_IndexExists_FalseReturned(void);
void test_common_ValidIndex_CM_IndexExists_TrueReturned(void);

#if defined(__cplusplus)
}
#endif

#endif // COMMONT_TEST_SUITE_H
