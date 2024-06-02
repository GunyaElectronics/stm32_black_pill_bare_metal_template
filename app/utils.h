#ifndef UTILS_H_
#define UTILS_H_

#include <limits.h>
#include <string.h>

// -----------------------------------------------------------------------------
// GLOBAL MACROS
// -----------------------------------------------------------------------------
// Macro to determine array length
#define ARRAY_LENGTH(arrayName)     (sizeof(arrayName) / sizeof(arrayName[0]))
#define ELEMENT_SIZE(arrayName)     (sizeof(arrayName[0]))
#define ZERO_MEMORY(addr, size)     (memset((addr), 0, (size)))

// Macro to retreive max of 2 supplied integers
#define MAX_OF_UINT(expr)                                                      \
    ((1ULL << ((sizeof(expr) * CHAR_BIT) - 1)) -  1ULL +                       \
    (1ULL << ((sizeof(expr) * CHAR_BIT) - 1)))

#endif // UTILS_H_
