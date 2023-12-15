#include "cyhal.h"
#include "cybsp.h"


void PWMInit(void)
{
    cy_rslt_t   rslt;
    cyhal_pwm_t pwm_obj;
 
    // Initialize PWM on the supplied pin and assign a new clock
    rslt = cyhal_pwm_init(&pwm_obj, CYBSP_USER_LED, NULL);
 
    // Set a duty cycle of 50% and frequency of 1Hz
    rslt = cyhal_pwm_set_duty_cycle(&pwm_obj, 50, 1);
 
    // Start the PWM output
    rslt = cyhal_pwm_start(&pwm_obj);
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
	
	PWMInit();

    for (;;)
    {
    }
}

