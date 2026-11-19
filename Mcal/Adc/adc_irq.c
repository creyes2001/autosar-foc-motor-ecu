#include "adc_irq.h"
#include "stm32g431xx.h"

volatile uint8 endOfInjSeq = 0;

void Adc_InterruptsEnable(void){
	//ADC1 
	ADC1->ISR  = ADC_ISR_JEOS; //clear flag
	ADC1->IER |= ADC_IER_JEOSIE; // end of injected conversion
}

void Adc_InterruptsDisable(void){
	ADC1->IER &= ~ADC_IER_JEOSIE; // end of injected conversion
}

void Adc_ISRHandler(void){
	if(ADC1->ISR & ADC_ISR_JEOS){
		ADC1->ISR = ADC_ISR_JEOS;  //clear flag
		endOfInjSeq = 1;
	}
}

void ADC1_2_IRQHandler(void)
{
	Adc_ISRHandler();
}
