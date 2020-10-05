#include "vt100_test_suite.h"
#include "vt100.h"
#include "unity.h"
#include <stdio.h>

/* ------------------------------------------------------------------------- */
/* ------------------------ VT_PrintCommand() CASES ----------------------- */
/* ------------------------------------------------------------------------- */

void test_vt100_InvalidLutIndexes_VT_PrintCommand_ErrorReturned(void)
{
    /* This should return LUT error code */
    TEST_ASSERT_EQUAL_INT32(
                VT_StatusLutErr,
                VT_PrintCommand(-1, 0, 0));
    TEST_ASSERT_EQUAL_INT32(
                VT_StatusLutErr,
                VT_PrintCommand(VT_ColorMagenta, VT_ColorDefault + 1, 0));
    TEST_ASSERT_EQUAL_INT32(
                VT_StatusLutErr,
                VT_PrintCommand(VT_ColorDefault + 1, 0, 0));
}

void test_vt100_VT_PrintCommand_Works(void)
{
    /* It cannot be unit tested */

#ifdef VT_TEST_VERBOSE
    printf("-------- VT100 TEST --------\n");

    VT_PrintCommand(VT_ColorRed, VT_ColorDefault, VT_FormatNone);
    printf("The text should be red without any extras\n");

    VT_PrintCommand(VT_ColorRed, VT_ColorDefault, VT_FormatBold);
    printf("The text should be bold red without any extras\n");

    VT_PrintCommand(
                VT_ColorBlue,
                VT_ColorYellow,
                VT_FormatBold | VT_FormatUnderlined | VT_FormatBlink);
    printf("The text should bold blue with yellow foreground"
           " and underlined/blink extras\n");

    VT_PrintCommand(
                VT_ColorCyan,
                VT_ColorMagenta,
                VT_FormatBold | VT_FormatUnderlined
                | VT_FormatBlink | VT_FormatInverted);
    printf("The text should bold magenta with cyan foreground"
           " and underlined/blink extras because invert flag is set\n");

    VT_PrintCommand(VT_ColorGreen, VT_ColorDefault, VT_FormatUnderlined);
    printf("The text should be green and underlined\n");
    VT_ResetAllCommand();

    printf("The text should have default properties\n");

    printf("-------- VT100 TEST END --------\n");
#endif

    TEST_ASSERT_TRUE(true); /* Dummy test pass */
}
