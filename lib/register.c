#include "register.h"

/* ------------------------------------------------------------------------- */
/* --------------------------- PRIVATE FUNCTIONS --------------------------- */
/* ------------------------------------------------------------------------- */

/* Update digit register state */
static inline void UpdateDigitRegister(
        REG_Memory *regMemory,
        REG_Addr regAddr,
        u8 state)
{
    /* Digit registers base address is 0x01 thus one should be subtracted */
    u8 digitRegOffset = regAddr - 1;
    u8* digitRegToBeUpdated = &regMemory->digit0 + digitRegOffset;

    *digitRegToBeUpdated = state;
}

/* Update decode mode register state */
static REG_Status UpdateDecodeModeRegister(REG_Memory *regMemory, u8 state)
{
    switch (state) {
    case REG_DecodeModeOff:
    case REG_DecodeModeDigit0:
    case REG_DecodeModeDigit0To3:
    case REG_DecodeModeDigit0To7:
        regMemory->decodeMode = state;
        return REG_StatusOk;
    default:
        return REG_StatusWrongState;
    }
}

/* Update intensity register state */
static REG_Status UpdateIntensityRegister(REG_Memory *regMemory, u8 state)
{
    if (!CM_ValueInBounds(state, REG_Intensity1_32, REG_Intensity31_32)) {
        return REG_StatusWrongState;
    }

    regMemory->intensity = state;
    return REG_StatusOk;
}

/* Update scan limit register */
static REG_Status UpdateScanLimitRegister(REG_Memory *regMemory, u8 state)
{
    if (!CM_ValueInBounds(state, REG_ScanLimitDigit0, REG_ScanLimitdigit0To7)) {
        return REG_StatusWrongState;
    }

    regMemory->scanLimit = state;
    return REG_StatusOk;
}

/* Update shutdown register */
static REG_Status UpdateShutdownRegister(REG_Memory *regMemory, u8 state)
{
    if (!CM_ValueInBounds(state, REG_ShutdownOn, REG_ShutdownOff)) {
        return REG_StatusWrongState;
    }

    regMemory->shutdown = state;
    return REG_StatusOk;
}

/* Update display test register */
static REG_Status UpdateDisplayTestRegister(REG_Memory *regMemory, u8 state)
{
    if (!CM_ValueInBounds(state, REG_DisplayTestOff, REG_DisplayTestOn)) {
        return REG_StatusWrongState;
    }

    regMemory->displayTest = state;
    return REG_StatusOk;
}

/* ------------------------------------------------------------------------- */
/* ----------------------------- API FUNCTIONS ----------------------------- */
/* ------------------------------------------------------------------------- */

void REG_MemoryInit(REG_Memory* regMemory)
{
    /* Initial power-up digit data */
    regMemory->digit0 = 0x00;
    regMemory->digit1 = 0x00;
    regMemory->digit2 = 0x00;
    regMemory->digit3 = 0x00;
    regMemory->digit4 = 0x00;
    regMemory->digit5 = 0x00;
    regMemory->digit6 = 0x00;
    regMemory->digit7 = 0x00;

    /* Initial power-up register data */
    regMemory->decodeMode = REG_DecodeModeOff;
    regMemory->intensity = REG_Intensity1_32;
    regMemory->scanLimit = REG_ScanLimitDigit0;
    regMemory->shutdown = REG_ShutdownOn;
    regMemory->displayTest = REG_DisplayTestOff;
}

REG_Status REG_Write(REG_Memory *regMemory, REG_Addr regAddr, u8 state)
{
    switch (regAddr) {
    /* Do nothing */
    case REG_AddrNoOp:
        return REG_StatusOk;
    /* Save digit state */
    case REG_AddrDigit0:
    case REG_AddrDigit1:
    case REG_AddrDigit2:
    case REG_AddrDigit3:
    case REG_AddrDigit4:
    case REG_AddrDigit5:
    case REG_AddrDigit6:
    case REG_AddrDigit7:
        UpdateDigitRegister(regMemory, regAddr, state);
        return REG_StatusOk;
    case REG_AddrDecodeMode:
        return UpdateDecodeModeRegister(regMemory, state);
    case REG_AddrIntensity:
        return UpdateIntensityRegister(regMemory, state);
    case REG_AddrScanLimit:
        return UpdateScanLimitRegister(regMemory, state);
    case REG_AddrShutdown:
        return UpdateShutdownRegister(regMemory, state);
    case REG_AddrDisplayTest:
        return UpdateDisplayTestRegister(regMemory, state);
    default:
        return REG_StatusWrongAddr;
    }
}
