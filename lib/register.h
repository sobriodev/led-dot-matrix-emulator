#ifndef REGISTER_H
#define REGISTER_H

#include "common.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/* ------------------------------ DATA TYPES ------------------------------- */
/* ------------------------------------------------------------------------- */

/* Register status codes */
typedef enum
{
    REG_StatusOk,
    REG_StatusWrongAddr,
    REG_StatusWrongState
} REG_Status;

/* Decode mode register format */
typedef enum
{
    REG_DecodeModeOff = 0x00,
    REG_DecodeModeDigit0 = 0x01,
    REG_DecodeModeDigit0To3 = 0x0F,
    REG_DecodeModeDigit0To7 = 0xFF
} REG_DecodeMode;

/* Intensity register format */
typedef enum
{
    REG_Intensity1_32 = 0x00,
    REG_Intensity3_32,
    REG_Intensity5_32,
    REG_Intensity7_32,
    REG_Intensity9_32,
    REG_Intensity11_32,
    REG_Intensity13_32,
    REG_Intensity15_32,
    REG_Intensity17_32,
    REG_Intensity19_32,
    REG_Intensity21_32,
    REG_Intensity23_32,
    REG_Intensity25_32,
    REG_Intensity27_32,
    REG_Intensity29_32,
    REG_Intensity31_32,
} REG_Intensity;

/* Shutdown register format */
typedef enum
{
    REG_ShutdownOn = 0x00,
    REG_ShutdownOff = 0x01
} REG_Shutdown;

/* Scan limit register format */
typedef enum
{
    REG_ScanLimitDigit0 = 0x00,
    REG_ScanLimitDigit0To1,
    REG_ScanLimitDigit0To2,
    REG_ScanLimitDigit0To3,
    REG_ScanLimitDigit0To4,
    REG_ScanLimitDigit0To5,
    REG_ScanLimitDigit0To6,
    REG_ScanLimitdigit0To7
} REG_ScanLimit;

/* Display test register format */
typedef enum
{
    REG_DisplayTestOff = 0x00,
    REG_DisplayTestOn = 0x01
} REG_DisplayTest;

/* Register address map */
typedef enum
{
    REG_AddrNoOp = 0x00,
    REG_AddrDigit0 = 0x01,
    REG_AddrDigit1 = 0x02,
    REG_AddrDigit2 = 0x03,
    REG_AddrDigit3 = 0x04,
    REG_AddrDigit4 = 0x05,
    REG_AddrDigit5 = 0x06,
    REG_AddrDigit6 = 0x07,
    REG_AddrDigit7 = 0x08,
    REG_AddrDecodeMode = 0x09,
    REG_AddrIntensity = 0x0A,
    REG_AddrScanLimit = 0x0B,
    REG_AddrShutdown = 0x0C,
    REG_AddrDisplayTest = 0x0F
} REG_Addr;

/* Register memory */
typedef struct
{
    u8 digit0; /* Do not change digit registers order */
    u8 digit1;
    u8 digit2;
    u8 digit3;
    u8 digit4;
    u8 digit5;
    u8 digit6;
    u8 digit7;
    REG_DecodeMode decodeMode;
    REG_Intensity intensity;
    REG_ScanLimit scanLimit;
    REG_Shutdown shutdown;
    REG_DisplayTest displayTest;
} REG_Memory;

/* ------------------------------------------------------------------------- */
/* ----------------------------- API FUNCTIONS ----------------------------- */
/* ------------------------------------------------------------------------- */

/* Initialize register memory */
void REG_MemoryInit(REG_Memory* regMemory);

/* Write to register */
REG_Status REG_Write(REG_Memory* regMemory, REG_Addr regAddr, u8 state);

#if defined(__cplusplus)
}
#endif

#endif // REGISTER_H
