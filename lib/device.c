#include "device.h"
#include "mem.h"
#include "common.h"
#include <stdlib.h>

/* ------------------------------------------------------------------------- */
/* --------------------------- PRIVATE VARIABLES --------------------------- */
/* ------------------------------------------------------------------------- */

/* Counter for generating device id */
static u32 devIdCnt = 0;

/* ------------------------------------------------------------------------- */
/* ----------------------------- API FUNCTIONS ----------------------------- */
/* ------------------------------------------------------------------------- */

DEV_Status DEV_CreateDevice(
        DEV_Info** devInfo,
        DEV_Color color,
        CM_Mallock mallocCallback)
{
    /* Allocate memory for info struct */
    *devInfo = mallocCallback(sizeof(DEV_Info));
    if (NULL == *devInfo) {
        return DEV_StatusMemErr;
    }

    (*devInfo)->id = devIdCnt++;
    (*devInfo)->color = color;

    /* Call memory init */
    REG_MemoryInit(&(*devInfo)->regMemory);

    /* Set default format chars */
    (*devInfo)->strFormatChars.charLedOn = DEV_STR_FORMAT_CHAR_LED_ON;
    (*devInfo)->strFormatChars.charLedOff = DEV_STR_FORMAT_CHAR_LED_OFF;

    return DEV_StatusOk;
}

DEV_Status DEV_DestroyDevice(DEV_Info** devInfo)
{
    MEM_Free(*devInfo);
    *devInfo = NULL;

    return DEV_StatusOk;
}

DEV_Status DEV_GetLineStr(
        const DEV_Info* device,
        DEV_Line line,
        char* outputStr)
{
    /* Null pointer guard */
    if (device == NULL) {
        return DEV_StatusNullPtr;
    }

    /* If the line does not fulfill requirements throw error code */
    if (!CM_ValueInBounds(line, DEV_Line0, DEV_Line7)) {
        return DEV_StatusWrongLine;
    }

    /* Find correct digit register and build string */
    char strBuff[DEV_LINE_BUFFER_LEN] = {0};
    const u8* regDigit = &device->regMemory.digit0 + line;
    for (size i = 0; i < DEV_LEDS; i++) {
        strBuff[i] = CM_U32_CHECK_BIT_SET(*regDigit, CM_U32_BIT(i))
                      ? device->strFormatChars.charLedOn
                      : device->strFormatChars.charLedOff;
    }
    /* Copy calculated string */
    strcpy(outputStr, strBuff);

    return DEV_StatusOk;
}
