#include "device.h"

DEV_Status DEV_CreateDevice(DEV_Info* devInfo, DEV_Color color)
{
    (void)devInfo;
    (void)color;
    return DEV_StatusOK;
}

DEV_Status DEV_DestroyDevice(DEV_Info** devInfo)
{
    (void)(devInfo);
    return DEV_StatusOK;
}
