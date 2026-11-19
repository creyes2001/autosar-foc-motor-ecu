#include "Platform_Types.h"
#include <stdint.h>
 
void Adc_InterruptsEnable(void);
void Adc_InterruptsDisable(void);
void Adc_ISRHandler(void);

extern volatile uint8 endOfInjSeq; 
