#include "vt100.h"
#include "common.h"
#include <stdio.h>

/* ------------------------------------------------------------------------- */
/* -------------------------- PRIVATE VARIABLES ---------------------------- */
/* ------------------------------------------------------------------------- */

const char* foregroundColorsLut[] =
{
    "\e[31m",
    "\e[32m",
    "\e[33m",
    "\e[34m",
    "\e[35m",
    "\e[36m",
    "\e[39m"
};

const char* backgroundColorsLut[] =
{
    "\e[41m",
    "\e[42m",
    "\e[43m",
    "\e[44m",
    "\e[45m",
    "\e[46m",
    "\e[49m"
};

/* ------------------------------------------------------------------------- */
/* -------------------------- PRIVATE FUNCTIONS ---------------------------- */
/* ------------------------------------------------------------------------- */

void ResetFontFormatCommands(void)
{
    printf("\e[21m"); /* Reset bold format */
    printf("\e[24m"); /* Reset underlined format */
    printf("\e[25m"); /* Reset blink format */
    printf("\e[27m"); /* Reset inverted format */
}

void PrintFormatCommand(u8 format)
{
    /* Clear old settings */
    ResetFontFormatCommands();

    if (U32_CHECK_BIT_SET(format, VT_FormatBold)) {
        printf("\e[1m");
    }
    if (U32_CHECK_BIT_SET(format, VT_FormatUnderlined)) {
        printf("\e[4m");
    }
    if (U32_CHECK_BIT_SET(format, VT_FormatBlink)) {
        printf("\e[5m");
    }
    if (U32_CHECK_BIT_SET(format, VT_FormatInverted)) {
        printf("\e[7m");
    }
}

/* ------------------------------------------------------------------------- */
/* ---------------------------- API FUNCTIONS ------------------------------ */
/* ------------------------------------------------------------------------- */

VT_Status VT_PrintCommand(VT_Color foreground, VT_Color background, u8 format)
{
    if (!CM_IndexExists(foreground, COUNT_OF(foregroundColorsLut)) ||
        !CM_IndexExists(background, COUNT_OF(backgroundColorsLut))) {
        return VT_StatusLutErr;
    }

    /* Print color and font commands */
    printf("%s", foregroundColorsLut[foreground]);
    printf("%s", backgroundColorsLut[background]);
    PrintFormatCommand(format);

    return VT_StatusOk;
}

void VT_ResetAllCommands(void)
{
    printf("\e[0m");
}
