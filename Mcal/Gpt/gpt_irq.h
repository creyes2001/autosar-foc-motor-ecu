#include "Platform_Types.h"
#include "stm32g431xx.h"
#include <stdint.h>

void Gpt_InterruptsEnable(void);
void Gpt_InterruptsDisable(void);
void Gpt_ISRHandler(void);
 
extern volatile uint8 gptoc4; 

