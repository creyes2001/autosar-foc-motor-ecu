#include "gpt_irq.h"

volatile uint8 gptoc4; 

void Gpt_InterruptsEnable(void){
	//TIM1
	TIM1->SR = ~TIM_SR_CC4IF; //clear flag
	TIM1->DIER |= TIM_DIER_CC4IE;
}

void Gpt_InterruptsDisable(void){
	TIM1->DIER &= ~TIM_DIER_CC4IE;
}

void Gpt_ISRHandler(void){
	if(TIM1->SR & TIM_SR_CC4IF){
		TIM1->SR = ~TIM_SR_CC4IF; //clear flag
		gptoc4 = 1;
	}
}

void TIM1_CC_IRQHandler(void){
	Gpt_ISRHandler();
}
