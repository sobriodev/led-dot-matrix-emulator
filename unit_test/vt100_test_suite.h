#ifndef VT100_TEST_SUITE_H
#define VT100_TEST_SUITE_H

#if defined(__cplusplus)
extern "C" {
#endif

#define VT_TEST_VERBOSE

/* ------------------------------------------------------------------------- */
/* ------------------------ VT_PrintCommand() CASES ----------------------- */
/* ------------------------------------------------------------------------- */

void test_vt100_InvalidLutIndexes_VT_PrintCommand_ErrorReturned(void);
void test_vt100_VT_PrintCommand_Works(void);

#if defined(__cplusplus)
}
#endif

#endif // COMMONT_TEST_SUITE_H
