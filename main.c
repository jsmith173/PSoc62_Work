#include "cyhal.h"
#include "cybsp.h"

bool LEDupdateFlag = false;

/* Isr_Timer configuration structure*/
cy_stc_sysint_t Isr_Timer_config = {
	.intrSrc = (IRQn_Type) CYBSP_TIMER_IRQ,
	.intrPriority = 7u
};

void Isr_Timer(void)
{
	
	volatile uint32_t interrupts = Cy_TCPWM_GetInterruptStatus(CYBSP_TIMER_HW, CYBSP_TIMER_NUM);
    /* Now the 'interrupts' contains all the currently pending interrupt masks */
	
    if (CY_TCPWM_INT_ON_TC & interrupts)
    {
		/* Clear the TCPWM peripheral interrupt */
		Cy_TCPWM_ClearInterrupt(CYBSP_TIMER_HW, CYBSP_TIMER_NUM, CY_TCPWM_INT_ON_TC);
    }
    if (CY_TCPWM_INT_ON_CC0 & interrupts)
    {
		/* Clear the TCPWM peripheral interrupt */
		Cy_TCPWM_ClearInterrupt(CYBSP_TIMER_HW, CYBSP_TIMER_NUM, CY_TCPWM_INT_ON_CC0);
    }
    volatile uint32_t cnt = TCPWM_CNT_COUNTER(CYBSP_TIMER_HW, CYBSP_TIMER_NUM);
	
	/* Clear the CM4 NVIC pending interrupt for TCPWM */
	NVIC_ClearPendingIRQ(Isr_Timer_config.intrSrc);
	LEDupdateFlag = true;
}

void TimerInit(void)
{
	/* Configure the TCPWM peripheral.
	Counter_config structure is defined based on the parameters entered
	in the Component configuration */
	Cy_TCPWM_Counter_Init(CYBSP_TIMER_HW, CYBSP_TIMER_NUM, &CYBSP_TIMER_config);
	/* Enable the initialized counter */
	Cy_TCPWM_Counter_Enable(CYBSP_TIMER_HW, CYBSP_TIMER_NUM);
	/* Start the enabled counter */
	Cy_TCPWM_TriggerStart(CYBSP_TIMER_HW, CYBSP_TIMER_MASK);
	/* Configure the ISR for the TCPWM peripheral*/
	Cy_SysInt_Init(&Isr_Timer_config, Isr_Timer);
	/* Enable interrupt in NVIC */
	NVIC_EnableIRQ((IRQn_Type)Isr_Timer_config.intrSrc);
}

int main(void)
{
    cy_rslt_t result;

#if defined (CY_DEVICE_SECURE)
    cyhal_wdt_t wdt_obj;

    /* Clear watchdog timer so that it doesn't trigger a reset */
    result = cyhal_wdt_init(&wdt_obj, cyhal_wdt_get_max_timeout_ms());
    CY_ASSERT(CY_RSLT_SUCCESS == result);
    cyhal_wdt_free(&wdt_obj);
#endif

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();
	
	TimerInit();

    for (;;)
    {
    }
}

