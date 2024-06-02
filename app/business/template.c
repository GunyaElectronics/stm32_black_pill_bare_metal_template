#include "template.h"
#include "system/system.h"
#include "bsp/wdt.h"

NO_RETURN void Assert_Ext_ProcessFailure(uint_fast32_t pc)
{
    (void) pc;

    // Wait for WDT reset
    for (;;);
}

NO_RETURN void System_Ext_OnHardFault(uint_fast32_t pc)
{
    (void) pc;

    // Wait for WDT reset
    for (;;);
}

void Template_Run(void)
{
    Wdt_Init();
    System_Init();

    while (1) {
    }
}