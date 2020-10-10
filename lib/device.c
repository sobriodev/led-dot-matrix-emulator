#include "device.h"
#include <stdlib.h>

DEV_Status DEV_CreateDevice(
        DEV_Info** devInfo,
        DEV_Color color,
        CM_Mallock mallocCallback)
{
    (void)devInfo;
    (void)color;

    /* Allocate memory for info struct */
    *devInfo = mallocCallback(sizeof(DEV_Info));
    if (NULL == *devInfo) {
        return DEV_StatusMemErr;
    }

    return DEV_StatusOK;
}

DEV_Status DEV_DestroyDevice(DEV_Info** devInfo)
{
    (void)(devInfo);
    return DEV_StatusOK;
}
