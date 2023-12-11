/* NOTE: This is a preview only. It combines elements of the
 * cycfg_peripherals.c and cycfg_peripherals.h files located in the folder
 * C:/Work/mtw/PSoc62_Work/bsps/TARGET_APP_CY8CKIT-062S2-43012/config/GeneratedSource.
 */

#include "cy_tcpwm_counter.h"
#include "cy_sysclk.h"
#include "cycfg_routing.h"
#if defined (CY_USING_HAL)
    #include "cyhal_hwmgr.h"
#endif //defined (CY_USING_HAL)

#define tcpwm_0_cnt_0_HW TCPWM0
#define tcpwm_0_cnt_0_NUM 0UL
#define tcpwm_0_cnt_0_MASK (1UL << 0)
#define tcpwm_0_cnt_0_IRQ tcpwm_0_interrupts_0_IRQn
#define tcpwm_0_cnt_0_INPUT_DISABLED 0x7U

const cy_stc_tcpwm_counter_config_t tcpwm_0_cnt_0_config = 
{
    .period = 32768,
    .clockPrescaler = CY_TCPWM_COUNTER_PRESCALER_DIVBY_1,
    .runMode = CY_TCPWM_COUNTER_CONTINUOUS,
    .countDirection = CY_TCPWM_COUNTER_COUNT_UP,
    .compareOrCapture = CY_TCPWM_COUNTER_MODE_CAPTURE,
    .compare0 = 16384,
    .compare1 = 16384,
    .enableCompareSwap = false,
    .interruptSources = CY_TCPWM_INT_ON_TC,
    .captureInputMode = tcpwm_0_cnt_0_INPUT_DISABLED & 0x3U,
    .captureInput = CY_TCPWM_INPUT_0,
    .reloadInputMode = tcpwm_0_cnt_0_INPUT_DISABLED & 0x3U,
    .reloadInput = CY_TCPWM_INPUT_0,
    .startInputMode = tcpwm_0_cnt_0_INPUT_DISABLED & 0x3U,
    .startInput = CY_TCPWM_INPUT_0,
    .stopInputMode = tcpwm_0_cnt_0_INPUT_DISABLED & 0x3U,
    .stopInput = CY_TCPWM_INPUT_0,
    .countInputMode = tcpwm_0_cnt_0_INPUT_DISABLED & 0x3U,
    .countInput = CY_TCPWM_INPUT_1,
};
#if defined (CY_USING_HAL)
    const cyhal_resource_inst_t tcpwm_0_cnt_0_obj = 
    {
        .type = CYHAL_RSC_TCPWM,
        .block_num = 0U,
        .channel_num = 0U,
    };
#endif //defined (CY_USING_HAL)


void init_cycfg_peripherals(void)
{
    Cy_SysClk_PeriphAssignDivider(PCLK_TCPWM0_CLOCKS0, CY_SYSCLK_DIV_8_BIT, 1U);
}

void reserve_cycfg_peripherals(void)
{
#if defined (CY_USING_HAL)
    cyhal_hwmgr_reserve(&tcpwm_0_cnt_0_obj);
#endif //defined (CY_USING_HAL)
}
