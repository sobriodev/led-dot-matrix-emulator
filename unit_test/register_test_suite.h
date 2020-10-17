#ifndef REGISTER_TEST_SUITE_H
#define REGISTER_TEST_SUITE_H

#if defined(__cplusplus)
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/* ------------------------- REG_MemoryInit() CASES ------------------------ */
/* ------------------------------------------------------------------------- */

void test_register_NullPassed_REG_MemoryInit_ErrReturned();
void test_register_ByDefault_REG_MemoryInit_PerformsCorrectInit();

/* ------------------------------------------------------------------------- */
/* --------------------------- REG_Write() CASES --------------------------- */
/* ------------------------------------------------------------------------- */

void test_register_NullPassed_REG_Write_ErrReturned();
void test_register_InvalidRegAddr_REG_Write_ErrReturned();
void test_register_InvalidRegState_REG_Write_ErrReturned();
void test_register_ValidRegAddr_REG_Write_MemoryUpdated();
void test_register_NoOpRegAddr_REG_Write_NothingIsDone();

#if defined(__cplusplus)
}
#endif

#endif // REGISTER_TEST_SUITE_H
