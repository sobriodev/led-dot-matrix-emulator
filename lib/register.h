#ifndef REGISTER_H
#define REGISTER_H

#if defined(__cplusplus)
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/* ------------------------------ DATA TYPES ------------------------------- */
/* ------------------------------------------------------------------------- */

/* Register address map */
typedef enum
{
    REG_MapNoOp = 0x00,
    REG_MapDigit0 = 0x01,
    REG_MapDigit1 = 0x02,
    REG_MapDigit2 = 0x03,
    REG_MapDigit3 = 0x04,
    REG_MapDigit4 = 0x05,
    REG_MapDigit5 = 0x06,
    REG_MapDigit6 = 0x07,
    REG_MapDigit7 = 0x08,
    REG_MapDecodeMode = 0x09,
    REG_MapIntensity = 0x0A,
    REG_MapsScanLimit = 0x0B,
    REG_MapShutdown = 0x0C,
    REG_MapDisplayTest = 0x0F
} REG_Map;

#if defined(__cplusplus)
}
#endif

#endif // REGISTER_H
