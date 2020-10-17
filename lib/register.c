#include "register.h"

/* ------------------------------------------------------------------------- */
/* --------------------------- PRIVATE FUNCTIONS --------------------------- */
/* ------------------------------------------------------------------------- */

/* Update digit register state */
static inline void UpdateDigitRegister(
        REG_Memory* regMemory,
        REG_Addr regAddr,
        u8 state)
{
    /* Digit registers base address is 0x01, thus one should be subtracted */
    u8 digitRegOffset = regAddr - 1;
    u8* digitRegToBeUpdated = &regMemory->digit0 + digitRegOffset;

    *digitRegToBeUpdated = state;
}

/* Update decode mode register state. Correct states do not fit into
 * indivisible range and should be handled explicitly
 */
static REG_Status UpdateDecodeModeRegister(REG_Memory* regMemory, u8 state)
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

/* Update registers whose possible states are in indivisible range */
static REG_Status UpdateRegisterIndivisibleRange(
        u8* regToBeUpdated,
        u8 rangeMin,
        u8 rangeMax,
        u8 state)
{
    /* Update state only if it fits into range */
    if (!CM_ValueInBounds(state, rangeMin, rangeMax)) {
        return REG_StatusWrongState;
    }

    *regToBeUpdated = state;
    return REG_StatusOk;
}

/* ------------------------------------------------------------------------- */
/* ----------------------------- API FUNCTIONS ----------------------------- */
/* ------------------------------------------------------------------------- */

REG_Status REG_MemoryInit(REG_Memory* regMemory)
{
    if (regMemory == NULL) {
        return REG_StatusNullPtr;
    }

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

    return REG_StatusOk;
}

REG_Status REG_Write(REG_Memory* regMemory, REG_Addr regAddr, u8 state)
{
    if (regMemory == NULL) {
        return REG_StatusNullPtr;
    }

    switch (regAddr) {
    /* In case no-op was passed - do nothing */
    case REG_AddrNoOp:
        return REG_StatusOk;
    /* Save digit state. Every combination is possible,
     * thus there is no point in checking argument correctness.
     */
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
    /* Update decode mode register */
    case REG_AddrDecodeMode:
        return UpdateDecodeModeRegister(regMemory, state);
    /* Update intensity register */
    case REG_AddrIntensity:
        return UpdateRegisterIndivisibleRange(
                    &regMemory->intensity,
                    REG_Intensity1_32,
                    REG_Intensity31_32,
                    state);
    /* Update scan limit register */
    case REG_AddrScanLimit:
        return UpdateRegisterIndivisibleRange(
                    &regMemory->scanLimit,
                    REG_ScanLimitDigit0,
                    REG_ScanLimitdigit0To7,
                    state);
    /* Update shutdown register */
    case REG_AddrShutdown:
        return UpdateRegisterIndivisibleRange(
                    &regMemory->shutdown,
                    REG_ShutdownOn,
                    REG_ShutdownOff,
                    state);
    /* Update display test register */
    case REG_AddrDisplayTest:
        return UpdateRegisterIndivisibleRange(
                    &regMemory->displayTest,
                    REG_DisplayTestOff,
                    REG_DisplayTestOn,
                    state);
    /* Other addresses lead to wrong address status */
    default:
        return REG_StatusWrongAddr;
    }
}
