#ifndef SOFT_TIMER_H_
#define SOFT_TIMER_H_

#include <stdint.h>

// -----------------------------------------------------------------------------
// GLOBAL CONSTANTS
// -----------------------------------------------------------------------------
#define SOFT_TIMER_MAX_TIMER_COUNT  2U

// -----------------------------------------------------------------------------
// GLOBAL TYPES
// -----------------------------------------------------------------------------
struct SoftTimerHandle;
typedef void (*SoftTimer_PeriodCb)(void);

// -----------------------------------------------------------------------------
// GLOBAL FUNCTIONS
// -----------------------------------------------------------------------------
struct SoftTimerHandle *SoftTimer_NewHandle(void);
void SoftTimer_FreeHandle(struct SoftTimerHandle *pHandle);

void SoftTimer_InitHandle(struct SoftTimerHandle *pHandle,
                          uint32_t periodMs, SoftTimer_PeriodCb pCb);
void SoftTimer_Start(struct SoftTimerHandle *pHandle);
void SoftTimer_StartSingle(struct SoftTimerHandle *pHandle);
void SoftTimer_Stop(struct SoftTimerHandle *pHandle);
void SoftTimer_Process(struct SoftTimerHandle *pHandle);

#endif // SOFT_TIMER_H_