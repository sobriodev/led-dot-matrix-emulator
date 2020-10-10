#ifndef DEVICE_H
#define DEVICE_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "common.h"

/* ------------------------------------------------------------------------- */
/* ------------------------------ DATA TYPES ------------------------------- */
/* ------------------------------------------------------------------------- */

/* Device status codes */
typedef enum
{
    DEV_StatusOK, /* OK */
    DEV_StatusMemErr /* Memory allocation error */
} DEV_Status;

/* Possible LED colors */
typedef enum
{
    DEV_ColorRed,
    DEV_ColorGreen,
    DEV_ColorBlue
} DEV_Color;

/* Device info */
typedef struct
{
    /* TODO add contents */
} DEV_Info;

/* ------------------------------------------------------------------------- */
/* ----------------------------- API FUNCTIONS ----------------------------- */
/* ------------------------------------------------------------------------- */

/* Create device */
DEV_Status DEV_CreateDevice(
        DEV_Info** devInfo,
        DEV_Color color,
        CM_Mallock mallocCallback);

/* Destroy device */
DEV_Status DEV_DestroyDevice(DEV_Info** devInfo);

#if defined(__cplusplus)
}
#endif

#endif // DEVICE_H
