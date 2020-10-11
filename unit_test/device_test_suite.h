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

#if defined(__cplusplus)
}
#endif

#endif // DEVICE_TEST_SUITE_H
