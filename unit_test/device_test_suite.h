#ifndef DEVICE_TEST_SUITE_H
#define DEVICE_TEST_SUITE_H

#if defined(__cplusplus)
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/* ------------------------ DEV_CreateDevice() CASES ----------------------- */
/* ------------------------------------------------------------------------- */

void test_device_MallocFailure_DEV_CreateDevice_ErrReturned();
void test_device_MultipleCalls_DEV_CreateDevice_CorrectIdAssigned();

/* ------------------------------------------------------------------------- */
/* ------------------------ DEV_DestroyDevice() CASES ---------------------- */
/* ------------------------------------------------------------------------- */

void test_device_DevicePointer_DEV_DestroyDevice_NullAssigned();

/* ------------------------------------------------------------------------- */
/* ------------------------- DEV_GetLineStr() CASES ------------------------ */
/* ------------------------------------------------------------------------- */

void test_device_NullPassed_DEV_GetLineStr_ErrReturned(void);
void test_device_WrongLine_DEV_GetLineStr_ErrReturned(void);
void test_device_ByDefault_DEV_GetLineStr_CorrectStrReturned(void);
void test_device_DigitModified_DEV_GetLineStr_CorrectStrReturned(void);

/* ------------------------------------------------------------------------- */
/* ----------------------- DEV_SetLineFormatCh() CASES --------------------- */
/* ------------------------------------------------------------------------- */

void test_device_NewFormatCh_DEV_SetLineFormatCh_SetCorrectly(void);


#if defined(__cplusplus)
}
#endif

#endif // DEVICE_TEST_SUITE_H
