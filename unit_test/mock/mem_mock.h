#ifndef MEM_MOCK_H
#define MEM_MOCK_H

#include "common.h"

#if defined(__cplusplus)
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/* ----------------------------- API FUNCTIONS ----------------------------- */
/* ------------------------------------------------------------------------- */

/* Memory allocate mock. It always return NULL */
void* MEM_MallocFailMock(size bytes);

#if defined(__cplusplus)
}
#endif

#endif // MEM_MOCK_H
