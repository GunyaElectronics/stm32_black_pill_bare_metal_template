#ifndef SOFT_TIMER_PRIVATE_CONFIG_H_
#define SOFT_TIMER_PRIVATE_CONFIG_H_

#include "bsp/time.h"
#include <stdint.h>
#include <stdbool.h>

// Platform configuration - Time -----------------------------------------------
typedef Time_Ts SoftTimer_Ts;

static inline void SoftTimer_Ext_GetCurrentSystemTs(SoftTimer_Ts *pTs)
{
    Time_GetCurrentSystemTs(pTs);
}

uint_fast32_t SoftTimer_Ext_GetMsSinceTs(const SoftTimer_Ts *pTs)
{
    return Time_GetMsSinceTs(pTs);
}

#endif // SOFT_TIMER_PRIVATE_CONFIG_H_
