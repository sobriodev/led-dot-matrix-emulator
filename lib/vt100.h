#ifndef VT100_H
#define VT100_H

#include "common.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/* ------------------------------ DATA TYPES ------------------------------- */
/* ------------------------------------------------------------------------- */

typedef enum
{
    VT_STATUS_OK, /* OK */
    VT_STATUS_LUT_ERR /* Invalid LUT array index */
} VT_Status;

typedef enum
{
    VT_ColorRed,
    VT_ColorGreen,
    VT_ColorYellow,
    VT_ColorBlue,
    VT_ColorMagenta,
    VT_ColorCyan,
    VT_ColorDefault /* The default color should be always at the end */
} VT_Color;

typedef enum
{
    VT_FormatNone = 0,
    VT_FormatBold = U32_BIT(0),
    VT_FormatUnderlined = U32_BIT(1),
    VT_FormatBlink = U32_BIT(2),
    VT_FormatInverted = U32_BIT(3),
} VT_FontFormat;

/* ------------------------------------------------------------------------- */
/* ---------------------------- API FUNCTIONS ------------------------------ */
/* ------------------------------------------------------------------------- */

VT_Status VT_PrintCommand(VT_Color foreground, VT_Color background, u8 format);
void VT_ResetAllCommand(void);

#if defined(__cplusplus)
}
#endif

#endif // VT100_H
