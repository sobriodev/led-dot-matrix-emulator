#ifndef MEM_H
#define MEM_H

#include "common.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/* ----------------------------- API FUNCTIONS ----------------------------- */
/* ------------------------------------------------------------------------- */

/* Memory allocate */
void* MEM_Malloc(size bytes);

/* Memory Free */
void MEM_Free(void* mem);

#if defined(__cplusplus)
}
#endif

#endif // MEM_H
