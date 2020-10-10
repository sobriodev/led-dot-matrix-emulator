#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* ------------------------------------------------------------------------- */
/* -------------------------------- MACROS --------------------------------- */
/* ------------------------------------------------------------------------- */

#define COUNT_OF(ARR) (sizeof((ARR)) / sizeof((ARR)[0]))

/* Bit operations */
#define U32_BIT(POS)                (1U << (POS))
#define U32_CHECK_BIT_SET(VAL, BIT) ((u32)(VAL) & (u32)(BIT))

/* ------------------------------------------------------------------------- */
/* ------------------------------ DATA TYPES ------------------------------- */
/* ------------------------------------------------------------------------- */

/* Unsigned types */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

/* Signed types */
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

/* Other types */
typedef size_t size;

/* Memory allocation function type */
typedef void* (*CM_Mallock)(size);

/* ------------------------------------------------------------------------- */
/* ----------------------------- API FUNCTIONS ----------------------------- */
/* ------------------------------------------------------------------------- */

static inline bool CM_IndexExists(size index, size arraySize)
{
    return index < arraySize;
}

#if defined(__cplusplus)
}
#endif

#endif // TYPES_H
