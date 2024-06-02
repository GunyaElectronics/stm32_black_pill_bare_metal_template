#include "soft_timer.h"
#include "soft_timer_private_config.h"
#include "assert.h"
#include "utils.h"

// -----------------------------------------------------------------------------
// LOCAL TYPES
// -----------------------------------------------------------------------------
struct SoftTimerHandle {
    SoftTimer_Ts ts;
    uint32_t periodMs;
    SoftTimer_PeriodCb pCb;
    bool isStarted;
    bool isSingle;
    bool isUsed;
};

// -----------------------------------------------------------------------------
// LOCAL VARIABLES
// -----------------------------------------------------------------------------
static struct SoftTimerHandle handles[SOFT_TIMER_MAX_TIMER_COUNT] = {};

// -----------------------------------------------------------------------------
// FUNCTIONS IMPLEMENTATION
// -----------------------------------------------------------------------------
struct SoftTimerHandle *SoftTimer_NewHandle(void)
{
    struct SoftTimerHandle *pHandle = NULL;

    for (size_t i = 0; i < ARRAY_LENGTH(handles); i++) {
        if (!handles[i].isUsed) {
            pHandle = &handles[i];
            pHandle->isUsed = true;
            break;
        }
    }

    return pHandle;
}

void SoftTimer_FreeHandle(struct SoftTimerHandle *pHandle)
{
    ASSERT(pHandle != NULL);
    ASSERT(pHandle->isUsed);

    pHandle->isUsed = false;
}

void SoftTimer_InitHandle(struct SoftTimerHandle *pHandle,
                          uint32_t periodMs, SoftTimer_PeriodCb pCb)
{
    ASSERT(pHandle != NULL);
    ASSERT(periodMs > 0);

    pHandle->isUsed = true;
    pHandle->isSingle = false;
    pHandle->isStarted = false;
    pHandle->pCb = pCb;
    pHandle->periodMs = periodMs;

    SoftTimer_Ext_GetCurrentSystemTs(&pHandle->ts);
}

void SoftTimer_Start(struct SoftTimerHandle *pHandle)
{
    ASSERT(pHandle != NULL);
    ASSERT(pHandle->periodMs > 0);

    pHandle->isSingle = false;
    pHandle->isStarted = true;

    SoftTimer_Ext_GetCurrentSystemTs(&pHandle->ts);
}

void SoftTimer_StartSingle(struct SoftTimerHandle *pHandle)
{
    ASSERT(pHandle != NULL);
    ASSERT(pHandle->periodMs > 0);

    pHandle->isSingle = true;
    pHandle->isStarted = true;

    SoftTimer_Ext_GetCurrentSystemTs(&pHandle->ts);
}

void SoftTimer_Stop(struct SoftTimerHandle *pHandle)
{
    ASSERT(pHandle != NULL);
    ASSERT(pHandle->periodMs > 0);

    pHandle->isSingle = false;
    pHandle->isStarted = false;
}

void SoftTimer_Process(struct SoftTimerHandle *pHandle)
{
    ASSERT(pHandle != NULL);

    if (!pHandle->periodMs) {
        return;
    }

    if (pHandle->isStarted && (SoftTimer_Ext_GetMsSinceTs(&pHandle->ts) > pHandle->periodMs)) {
        if (pHandle->isSingle) {
            pHandle->isSingle = false;
            pHandle->isStarted = false;
        } else {
            SoftTimer_Ext_GetCurrentSystemTs(&pHandle->ts);
        }
        if (pHandle->pCb != NULL) {
            pHandle->pCb();
        }
    }
}