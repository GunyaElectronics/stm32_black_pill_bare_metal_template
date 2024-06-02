#ifndef TIME_H_
#define TIME_H_

#include "utils.h"
#include <stdint.h>

// -----------------------------------------------------------------------------
// GLOBAL CONSTANTS
// -----------------------------------------------------------------------------
#define TIME_GET_MS_SINCE_TS_MAX                                               \
    (MAX_OF_UINT(Time_GetMsSinceTs((Time_Ts *) 0)))

// -----------------------------------------------------------------------------
// GLOBAL TYPES
// -----------------------------------------------------------------------------
typedef struct Time_Ts_ {
    unsigned int : 32;
} Time_Ts;

// -----------------------------------------------------------------------------
// GLOBAL FUNCTIONS
// -----------------------------------------------------------------------------
void Time_Init(void);

void Time_GetCurrentSystemTs(Time_Ts *pTs);
uint32_t Time_GetMsSinceTs(const Time_Ts *pTs);
// Positive amountMs corresponds to shifting toward the future, while negative -
// toward the past
void Time_ShiftTs(Time_Ts *pTs, int32_t amountMs);

#endif // TIME_H_
