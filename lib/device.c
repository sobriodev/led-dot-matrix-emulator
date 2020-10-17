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

    return DEV_StatusOk;
}

DEV_Status DEV_DestroyDevice(DEV_Info** devInfo)
{
    MEM_Free(*devInfo);
    *devInfo = NULL;

    return DEV_StatusOk;
}

DEV_Status DEV_GetLineStr(const DEV_Info* device, DEV_Line line)
{
    /* Null pointer guard */
    if (device == NULL) {
        return DEV_StatusNullPtr;
    }

    /* If the line does not fulfill requirements throw error code */
    if (!CM_ValueInBounds(line, DEV_Line0, DEV_Line7)) {
        return DEV_StatusWrongLine;
    }

    return DEV_StatusOk;
}
