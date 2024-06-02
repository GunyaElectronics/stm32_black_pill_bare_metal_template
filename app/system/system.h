#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "compiler.h"
#include <stdint.h>
#include <stdbool.h>

// -----------------------------------------------------------------------------
// GLOBAL CONSTANTS
// -----------------------------------------------------------------------------
#define SYSTEM_BAUDRATE_INVALID             0U
#define SYSTEM_MAVLINK_SYSTEM_ID_INVALID    0U

// -----------------------------------------------------------------------------
// GLOBAL TYPES
// -----------------------------------------------------------------------------
typedef enum System_ResetCause_ {
    SYSTEM_RESET_CAUSE_UNKNOWN = 0U,
    SYSTEM_RESET_CAUSE_WDT
} System_ResetCause;

// -----------------------------------------------------------------------------
// GLOBAL FUNCTIONS
// -----------------------------------------------------------------------------
bool System_Init(void);

NO_RETURN void System_Restart(void);
NO_RETURN void System_Lockout(void);

System_ResetCause System_GetResetCause(void);
void System_ClearResetCause(void);

void System_DelayUs(uint16_t delayUs);
void System_DelayMs(uint32_t delayMs);

void System_WaitForEvents(void);

unsigned int System_EnterCriticalSection(void);
void System_ExitCriticalSection(unsigned int key);

bool System_IsIsrContext(void);

// Static callbacks to be implemented externally (outside of this module)
NO_RETURN void System_Ext_OnHardFault(unsigned int pc);

#endif // SYSTEM_H_
