#ifndef TIME_PORT_H_
#define TIME_PORT_H_

#include "utils.h"
#include <stdint.h>

// -----------------------------------------------------------------------------
// GLOBAL CONSTANTS
// -----------------------------------------------------------------------------
#define TIME_GET_MS_SINCE_STARTUP                                              \
    (MAX_OF_UINT(Time_GetMsSinceStartup()))

// -----------------------------------------------------------------------------
// GLOBAL FUNCTIONS
// -----------------------------------------------------------------------------
// Returned value is saturated at TIME_GET_MS_SINCE_STARTUP
uint32_t Time_GetMsSinceStartup(void);

#endif // TIME_PORT_H_
