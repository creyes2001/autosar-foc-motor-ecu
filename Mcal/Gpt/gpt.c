#include "gpt.h"

/*
*This driver relies on the correct clock configuration set up by the PWM driver.
*Gpt_Init must be called after Pwm_Init, and must use 
*the same TIM_CNT_CLK_HZ and PERIOD_US definitions.
*/

#define TIM_CNT_CLK_MHZ 75U
#define PERIOD_US 50U

static Std_ReturnType Gpt_ChannelConfig(Gpt_TimHwUnitType HwUnit, Gpt_ChannelType Channel, Gpt_ChannelModeType Mode);

static volatile TIM_TypeDef* GptTim[2] = {TIM1,TIM2};

void Gpt_Init(const Gpt_ConfigType* ConfigPtr){
	for(uint8 i = 0; i < ConfigPtr->size; i++){
		Gpt_ChannelConfig(ConfigPtr->HwTriggerConfig[i].HwUnit, ConfigPtr->HwTriggerConfig[i].ChannelId, ConfigPtr->HwTriggerConfig[i].Mode);
		Gpt_SetTriggerCompare(ConfigPtr->HwTriggerConfig[i].ChannelId,50U);
	}
}

void Gpt_SetTriggerCompare(Gpt_ChannelType Channel,uint16 compare){
	uint32 period = (TIM_CNT_CLK_MHZ * PERIOD_US) / 2;
	uint32 trigger =(((TIM_CNT_CLK_MHZ * PERIOD_US) / 2) * compare ) / 100; //assuming center aligned mode
	switch(Channel){
		case GPT_CHANNEL_1:
			TIM1->CCR1 = trigger;
			break;
		case GPT_CHANNEL_2:
			TIM1->CCR2 = trigger;
			break;
		case GPT_CHANNEL_3:
			TIM1->CCR3 = trigger;
			break;
		case GPT_CHANNEL_4:
			TIM1->CCR4 = trigger;
			break;
		default:
			break;
	}
	// TODO: extend to both timers
}

void Gpt_EnableHwTrigger(Gpt_ChannelType Channel){

	// TODO: extend to  both timers
}

void Gpt_DisableHwTrigger(Gpt_ChannelType Channel){

	// TODO: extend to both timers
}

static Std_ReturnType Gpt_ChannelConfig(Gpt_TimHwUnitType HwUnit, Gpt_ChannelType Channel, Gpt_ChannelModeType Mode){
		
	switch(Channel){
	
		case GPT_CHANNEL_1:
			//TODO:implement
			break;
	
		case GPT_CHANNEL_2:
			//TODO:implement
			break;
	
		case GPT_CHANNEL_3:
			//TODO:implement
			break;
	
		case GPT_CHANNEL_4:
			GptTim[HwUnit]->CCMR2 &= ~(TIM_CCMR2_OC4M_Msk); //Clear bitfield
			GptTim[HwUnit]->CCMR2 |= (Mode << TIM_CCMR2_OC4M_Pos);
			GptTim[HwUnit]->CCMR2 |= TIM_CCMR2_OC4PE; //enable preload
			GptTim[HwUnit]->CCER |= TIM_CCER_CC4E; //enable
			GptTim[HwUnit]->CCER &= ~TIM_CCER_CC4NE; //disable

			break;
	
		default: 
			return E_NOT_OK; 
			break;
	}	

	return E_OK;
}
