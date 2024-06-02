#include "time.h"
#include "private/time_private.h"
#include "stm32f4xx_hal.h"
#include "assert.h"
#include <stdbool.h>

// -----------------------------------------------------------------------------
// LOCAL VARIABLES
// -----------------------------------------------------------------------------
static uint32_t timeSinceStartupMs = 0U;

// -----------------------------------------------------------------------------
// FUNCTIONS IMPLEMENTATION
// -----------------------------------------------------------------------------
void Time_Init(void)
{
    // SysTick is initialized earlier by the HAL_Init.
    // Here just ensure its frequency
    ASSERT(HAL_GetTickFreq() == HAL_TICK_FREQ_1KHZ);
}

void Time_GetCurrentSystemTs(Time_Ts *pTs)
{
    ASSERT(pTs != NULL);
    *((uint32_t *) pTs) = HAL_GetTick();
}

uint32_t Time_GetMsSinceTs(const Time_Ts *pTs)
{
    ASSERT(pTs != NULL);
    return (uint_fast32_t) (HAL_GetTick() - *((uint32_t *) pTs));
}

void Time_ShiftTs(Time_Ts *pTs, int32_t amountMs)
{
    ASSERT(pTs != NULL);
    *((uint32_t *) pTs) += (uint32_t) amountMs;
}

void SysTick_Handler(void)
{
    HAL_IncTick();

    const uint32_t tickValueMs = HAL_GetTick();
    timeSinceStartupMs =
        (tickValueMs > timeSinceStartupMs) ?
        tickValueMs : TIME_GET_MS_SINCE_STARTUP;
}

uint32_t Time_GetMsSinceStartup(void)
{
    return timeSinceStartupMs;
}
