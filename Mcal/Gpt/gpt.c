#include "gpt.h"


static Std_ReturnType Gpt_ChannelConfig(Gpt_TimHwUnitType HwUnit, Gpt_ChannelType Channel, Gpt_ChannelModeType Mode);

static volatile TIM_TypeDef* GptTim[2] = {TIM1,TIM2};

void Gpt_Init(const Gpt_ConfigType* ConfigPtr){
	for(uint8 i = 0; i < ConfigPtr->size; i++){
		Gpt_ChannelConfig(ConfigPtr->HwTriggerConfig[i].HwUnit, ConfigPtr->HwTriggerConfig[i].ChannelId, ConfigPtr->HwTriggerConfig[i].Mode);
	}
}

void Gpt_SetTriggerCompare(Gpt_ChannelType Channel,uint16 ms){

}

void Gpt_EnableHwTrigger(Gpt_ChannelType Channel){

}

void Gpt_DisableHwTrigger(Gpt_ChannelType Channel){

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
