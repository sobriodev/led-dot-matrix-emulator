#include "register.h"

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
