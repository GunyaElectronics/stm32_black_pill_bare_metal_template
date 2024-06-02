#include "wdt.h"
#include "stm32f4xx.h"
#include <stdint.h>

// -----------------------------------------------------------------------------
// FUNCTIONS IMPLEMENTATION
// -----------------------------------------------------------------------------
void Wdt_Init(void)
{
    // Start watchdog
    const uint32_t startKey = 0x0000CCCC;
    IWDG->KR = startKey;

    // IWDG is clocked with 32KHz clock.
    // Having divider 1/8 and Reload value 4095 that gives Watchdog period
    // equal 1024ms (should be bigger than single 16KB sector erase & program
    // time = 500ms + (16384 / 4 * 100us) = 910ms)
    const uint32_t enableWriteKey = 0x00005555;
    IWDG->KR  = enableWriteKey;
    IWDG->PR  = IWDG_PR_PR_0;   // Divider = 1/8
    IWDG->RLR = 4095U;          // Reload
    while ((IWDG->SR & (IWDG_SR_PVU | IWDG_SR_RVU)) != 0U) {
        (void) 0;
    }
    Wdt_Reset();
}

void Wdt_Reset(void)
{
    const uint32_t resetKey = 0x0000AAAA;
    IWDG->KR = resetKey;
}
