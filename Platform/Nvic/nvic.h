#include "stm32g4xx.h"

/* All priorities in one place: 0 = most urgent, 15 = least */
#define PRIO_ADC1_2   0U
#define PRIO_TIM1_CC  0U

void Nvic_Init(void);

#define Nvic_GlobalEnable()   __enable_irq()
#define Nvic_GlobalDisable()  __disable_irq()
