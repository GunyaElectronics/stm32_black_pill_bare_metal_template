#include "system.h"
#include "bsp/time.h"
#include "stm32f4xx_hal.h"
#include "assert.h"
#include "utils.h"
#include "bsp/wdt.h"

// -----------------------------------------------------------------------------
// LOCAL TYPES
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// LOCAL FUNCTIONS
// -----------------------------------------------------------------------------
static bool ConfigSystemClock(void);

// -----------------------------------------------------------------------------
// LOCAL VARIABLES
// -----------------------------------------------------------------------------
static uint16_t delayCyclesPerUs = 0U;
static volatile unsigned int criticalNesting = 0U;

// -----------------------------------------------------------------------------
// FUNCTIONS IMPLEMENTATION
// -----------------------------------------------------------------------------
bool System_Init(void)
{
    HAL_Init();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    return ConfigSystemClock();
}

NO_RETURN void System_Restart(void)
{
    NVIC_SystemReset();
}

NO_RETURN void System_Lockout(void)
{
    __disable_irq();
    for (;;) {
        Wdt_Reset();
    }
}

System_ResetCause System_GetResetCause(void)
{
    return
        __HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) ?
            SYSTEM_RESET_CAUSE_WDT : SYSTEM_RESET_CAUSE_UNKNOWN;
}

void System_ClearResetCause(void)
{
    __HAL_RCC_CLEAR_RESET_FLAGS();
}

void System_DelayUs(uint16_t delayUs)
{
    // Simple implementation of the minimum required delay (actual delay may be
    // higher due to interrupts, etc.) without usage of any additional periphery
    uint32_t cycles = ((uint32_t) delayUs) * delayCyclesPerUs;
    if (cycles > 0U) {
        // NOTE: nop's below used to pad cycle clocks to value minimizing
        // division rounding error for plausable CPU frequencies (e.g. 16MHz)
        __asm volatile(
            "1:\n"
            "sub %0, #1\n"      // 1 clock
            "cmp %0, #0\n"      // 1 clock
            "nop\n"             // 1 clock
            "nop\n"             // 1 clock
            "nop\n"             // 1 clock
            "bne 1b\n"          // 3 clocks (1 clock at exiting the loop)
            : : "r" (cycles)    // Cycle = 8 clocks
        );
    }
}

void System_DelayMs(uint32_t delayMs)
{
    STATIC_ASSERT(
        MAX_OF_UINT(delayMs) <= TIME_GET_MS_SINCE_TS_MAX,
        "Implementation expects that Time module can handle delay range");

    Time_Ts ts;
    Time_GetCurrentSystemTs(&ts);
    while (Time_GetMsSinceTs(&ts) < delayMs) {
        System_WaitForEvents();
    }
}

void System_WaitForEvents(void)
{
    __WFI();
}

unsigned int System_EnterCriticalSection(void)
{
    __disable_irq();
    criticalNesting++;
    return criticalNesting;
}

void System_ExitCriticalSection(unsigned int key)
{
    ASSERT((criticalNesting > 0U) && (criticalNesting == key));
    criticalNesting--;
    if (criticalNesting == 0) {
        __enable_irq();
    }
}

bool System_IsIsrContext(void)
{
    return ((__get_IPSR() & IPSR_ISR_Msk) != 0U);
}

void HardFault_Handler(void)
{
    struct ExceptionStackFrame_
    {
      uint32_t ulR0;
      uint32_t ulR1;
      uint32_t ulR2;
      uint32_t ulR3;
      uint32_t ulR12;
      uint32_t ulLr;
      uint32_t ulPc;
      uint32_t ulXpsr;
    } *pExceptionStackFrame;

    // Extract location of Exception Stack Frame:
    // get MSP or PSP value dependently on MSP/PSP flag in LR register
    __asm volatile(
          "mrs %0, msp\n"
          "mov r1, lr\n"
          "mov r2, #4\n"
          "tst r1, r2\n"
          "beq 1f\n"
          "mrs %0, psp\n"
          "1:\n"
        : "=r" (pExceptionStackFrame));

    System_Ext_OnHardFault(pExceptionStackFrame->ulPc);
}

static bool ConfigSystemClockHSE(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 128;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        return false;
    }

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    return HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) == HAL_OK;
}

static void ConfigSystemClockHSI(void)
{
    HAL_StatusTypeDef result;
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 200;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;

    result = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    ASSERT(result == HAL_OK);

    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    result = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3);
    ASSERT(result == HAL_OK); (void)result;
}

static bool ConfigSystemClock(void)
{
    bool isStartedFromHse = ConfigSystemClockHSE();

    if (!isStartedFromHse) {
        ConfigSystemClockHSI();
    }

    SystemCoreClockUpdate();

    // cycleClocks should correspond the number of clocks per single cycle
    // inside of System_DelayUs
    const uint32_t cycleClocks = 8U;
    const uint32_t delayCyclesPerUs32 =
        SystemCoreClock / 1000000U / cycleClocks;
    ASSERT((delayCyclesPerUs32 > 0U) && (delayCyclesPerUs32 <= UINT16_MAX));
    delayCyclesPerUs = (uint16_t) delayCyclesPerUs32;

    return isStartedFromHse;
}
