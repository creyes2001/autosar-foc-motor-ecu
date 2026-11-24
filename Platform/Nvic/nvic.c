#include "nvic.h"

void Nvic_Init(void)
{
    NVIC_SetPriorityGrouping(3U);   /* 4 bits preemption, 0 sub-priority */

    NVIC_SetPriority(ADC1_2_IRQn, PRIO_ADC1_2);
	NVIC_SetPriority(TIM1_CC_IRQn, PRIO_TIM1_CC);

    /* Clear anything pending, then open the NVIC lines.
       Nothing fires until a module sets its own IER bit. */
    NVIC_ClearPendingIRQ(ADC1_2_IRQn);
	NVIC_SetPriority(TIM1_CC_IRQn, PRIO_TIM1_CC);

    NVIC_EnableIRQ(ADC1_2_IRQn);
	NVIC_EnableIRQ(TIM1_CC_IRQn);
}
