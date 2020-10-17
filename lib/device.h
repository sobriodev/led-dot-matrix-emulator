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
    DEV_StatusOk, /* OK */
    DEV_StatusMemErr, /* Memory allocation error */
    DEV_StatusNullPtr, /* NULL pointer passed error */
    DEV_StatusWrongLine
} DEV_Status;

/* Possible LED colors */
typedef enum
{
    DEV_ColorRed,
    DEV_ColorGreen,
    DEV_ColorBlue
} DEV_Color;

/* Device lines translate to digit registers */
typedef enum
{
    DEV_Line0 = 0,
    DEV_Line1,
    DEV_Line2,
    DEV_Line3,
    DEV_Line4,
    DEV_Line5,
    DEV_Line6,
    DEV_Line7
} DEV_Line;

/* Device info */
typedef struct
{
    u32 id; /* Should be unique within a program */
    DEV_Color color;
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

/* Print digit line */
DEV_Status DEV_GetLineStr(const DEV_Info* device, DEV_Line line);

#if defined(__cplusplus)
}
#endif

#endif // DEVICE_H
