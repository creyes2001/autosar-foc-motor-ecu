#include "pwm.h"

#define PWM_1 (6U)
#define PWM_2 (7U)

static Std_ReturnType Pwm_ClockConfig(Pwm_TimHwUnitType PwmTimHwUnit,Pwm_ClkSrcType ClkSrc,Pwm_PrescType Presc);
static Std_ReturnType Pwm_SetCounterMode(Pwm_TimHwUnitType PwmTimHwUnit,Pwm_ModeType Mode,Pwm_EdgeNotificationType Notification);
static Std_ReturnType Pwm_SetUpdateRate(Pwm_TimHwUnitType PwmTimHwUnit,Pwm_UpdateRateType UpdateRate);
static Std_ReturnType Pwm_ChannelConfig(Pwm_TimHwUnitType PwmTimHwUnit,Pwm_NumberOfChannels NumberOfChannels, const Pwm_ChannelConfigType* ChannelConfig);

static volatile TIM_TypeDef* PwmTim[2] = {TIM1,TIM8};

void Pwm_Init(const Pwm_ConfigType* ConfigPtr){

	Pwm_Stop(ConfigPtr->HwUnit);
	
	Pwm_ClockConfig(ConfigPtr->HwUnit,ConfigPtr->ClkSrc,ConfigPtr->Presc);
	Pwm_SetCounterMode(ConfigPtr->HwUnit,ConfigPtr->Mode,ConfigPtr->EdgeNotification);
	Pwm_SetUpdateRate(ConfigPtr->HwUnit,ConfigPtr->UpdateRate);
	Pwm_ChannelConfig(ConfigPtr->HwUnit,ConfigPtr->NumberOfChannels,ConfigPtr->Pwm_ChannelConfig);
	
	PwmTim[ConfigPtr->HwUnit]->EGR |= TIM_EGR_UG;	//set UG TIMxEGR to trasfer preload to shadow register manually
	Pwm_Start(ConfigPtr->HwUnit);
}
void Pwm_Start(Pwm_TimHwUnitType PwmTimHwUnit){
	if((PwmTim[PwmTimHwUnit]->CR1 & TIM_CR1_CEN) != 1U){
		PwmTim[PwmTimHwUnit]->CR1 |= TIM_CR1_CEN; 
	}
	
}

void Pwm_Stop(Pwm_TimHwUnitType PwmTimHwUnit){
	if((PwmTim[PwmTimHwUnit]->CR1 & TIM_CR1_CEN) != 0U){
		PwmTim[PwmTimHwUnit]->CR1 &= ~TIM_CR1_CEN; 
	}

}

void Pwm_SetDutyCycle(Pwm_TimHwUnitType PwmTimHwUnit,Pwm_ChannelType ChannelNumber,uint16 DutyCycle){
	switch(ChannelNumber){
		case PWM_CHANNEL1:
			PwmTim[PwmTimHwUnit]->CCR1 = (uint32)DutyCycle;
			break;
		case PWM_CHANNEL2:
			PwmTim[PwmTimHwUnit]->CCR2 = (uint32)DutyCycle;
			break;
		case PWM_CHANNEL3:
			PwmTim[PwmTimHwUnit]->CCR3 = (uint32)DutyCycle;
			break;
		case PWM_CHANNEL4:
			PwmTim[PwmTimHwUnit]->CCR4 = (uint32)DutyCycle;
			break;
		default:
			break;
	}
}

void Pwm_SetPeriodAndDuty(Pwm_TimHwUnitType PwmTimHwUnit,Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle){

	PwmTim[PwmTimHwUnit]->ARR = (uint32)Period;
	
	switch(ChannelNumber){
		case PWM_CHANNEL1:
			PwmTim[PwmTimHwUnit]->CCR1 = (uint32)DutyCycle;
			break;
		case PWM_CHANNEL2:
			PwmTim[PwmTimHwUnit]->CCR2 = (uint32)DutyCycle;
			break;
		case PWM_CHANNEL3:
			PwmTim[PwmTimHwUnit]->CCR3 = (uint32)DutyCycle;
			break;
		case PWM_CHANNEL4:
			PwmTim[PwmTimHwUnit]->CCR4 = (uint32)DutyCycle;
			break;
		default:
			break;
	}
}

static Std_ReturnType Pwm_ClockConfig(Pwm_TimHwUnitType PwmTimHwUnit,Pwm_ClkSrcType ClkSrc,Pwm_PrescType Presc){
	switch(ClkSrc){
		case PWM_INTERNAL_CLOCK:
			PwmTim[PwmTimHwUnit]->SMCR &= ~TIM_SMCR_SMS;		
			break;
		case PWM_EXTERNAL_CLOCK_MODE1:
			//TODO: implement 
			break;
		case PWM_EXTERNAL_CLOCK_MODE2:
			//TODO: implement 
			break;
		case PWM_ENCODER_MODE:
			//TODO: implement 
			break;
		default:
			return E_NOT_OK;
			break;
	}

	PwmTim[PwmTimHwUnit]->PSC =(uint32)Presc;
	return E_OK;
}

static Std_ReturnType Pwm_SetCounterMode(Pwm_TimHwUnitType PwmTimHwUnit,Pwm_ModeType Mode,Pwm_EdgeNotificationType Notification){
	switch(Mode){
		case PWM_RIGTH_ALIGNED:
			//TODO: implement
			break;
		case PWM_LEFT_ALIGNED:
			//TODO: implement
			break;
		case PWM_CENTER_ALIGNED:
			PwmTim[PwmTimHwUnit]->CR1 |= TIM_CR1_ARPE; //TIM ARR buffered 
			PwmTim[PwmTimHwUnit]->CR1 &= ~TIM_CR1_CMS; //clear 
			if(Notification == PWM_RISING_EDGE){
				PwmTim[PwmTimHwUnit]->CR1 |= TIM_CR1_CMS_1; 
			}
			else if(Notification == PWM_FALLING_EDGE){
				PwmTim[PwmTimHwUnit]->CR1 |= TIM_CR1_CMS_0; 
			}
			else if(Notification == PWM_BOTH_EDGES){
				PwmTim[PwmTimHwUnit]->CR1 |= TIM_CR1_CMS; 
			}
			else{
				return E_NOT_OK;
			}
			break;
		default:
			return E_NOT_OK;
			break;
	}
			return E_OK;
}

static Std_ReturnType Pwm_SetUpdateRate(Pwm_TimHwUnitType PwmTimHwUnit,Pwm_UpdateRateType UpdateRate){
	if(UpdateRate > 0xFFFFu){
		return E_NOT_OK;
	}
	PwmTim[PwmTimHwUnit]->RCR = (uint32)UpdateRate; 
	return E_OK;
}

static Std_ReturnType Pwm_ChannelConfig(Pwm_TimHwUnitType PwmTimHwUnit,Pwm_NumberOfChannels NumberOfChannels, const Pwm_ChannelConfigType* ChannelConfig){

	for(uint8 i =0; i <= NumberOfChannels; i++){
		switch(ChannelConfig->ChannelId){
			case PWM_CHANNEL1:
				PwmTim[PwmTimHwUnit]->CCMR1 &= ~(TIM_CCMR1_OC1M_Msk); //clear bitfield 
				if(ChannelConfig->OutputMode == PWM_MODE_1){
					PwmTim[PwmTimHwUnit]->CCMR1 |= (PWM_1 << TIM_CCMR1_OC1M_Pos); 
				}
				else if(ChannelConfig->OutputMode == PWM_MODE_2){
					PwmTim[PwmTimHwUnit]->CCMR1 |= (PWM_2 << TIM_CCMR1_OC1M_Pos); 
				}
				else{
					return E_NOT_OK;
				}

				PwmTim[PwmTimHwUnit]->CCMR1 |= TIM_CCMR1_OC1PE; //enable preload 
				PwmTim[PwmTimHwUnit]->CCER |= TIM_CCER_CC1E;	//enable output
				PwmTim[PwmTimHwUnit]->CCER &= ~TIM_CCER_CC1NE;	//disable complementary output

				break;

			case PWM_CHANNEL2:
				PwmTim[PwmTimHwUnit]->CCMR1 &= ~(TIM_CCMR1_OC2M_Msk); //clear bitfield 
				if(ChannelConfig->OutputMode == PWM_MODE_1){
					PwmTim[PwmTimHwUnit]->CCMR1 |= (PWM_1 << TIM_CCMR1_OC2M_Pos); 
				}
				else if(ChannelConfig->OutputMode == PWM_MODE_2){
					PwmTim[PwmTimHwUnit]->CCMR1 |= (PWM_2 << TIM_CCMR1_OC2M_Pos); 
				}
				else{
					return E_NOT_OK;
				}

				PwmTim[PwmTimHwUnit]->CCMR1 |= TIM_CCMR1_OC2PE; //enable preload 
				PwmTim[PwmTimHwUnit]->CCER |= TIM_CCER_CC2E;	//enable output
				PwmTim[PwmTimHwUnit]->CCER &= ~TIM_CCER_CC2NE;	//disable complementary output

				break;

			case PWM_CHANNEL3:
				PwmTim[PwmTimHwUnit]->CCMR2 &= ~(TIM_CCMR2_OC3M_Msk); //clear bitfield 
				if(ChannelConfig->OutputMode == PWM_MODE_1){
					PwmTim[PwmTimHwUnit]->CCMR2 |= (PWM_1 << TIM_CCMR2_OC3M_Pos); 
				}
				else if(ChannelConfig->OutputMode == PWM_MODE_2){
					PwmTim[PwmTimHwUnit]->CCMR2 |= (PWM_2 << TIM_CCMR2_OC3M_Pos); 
				}
				else{
					return E_NOT_OK;
				}

				PwmTim[PwmTimHwUnit]->CCMR2 |= TIM_CCMR2_OC3PE; //enable preload 
				PwmTim[PwmTimHwUnit]->CCER |= TIM_CCER_CC3E;	//enable output
				PwmTim[PwmTimHwUnit]->CCER &= ~TIM_CCER_CC3NE;	//disable complementary output

				break;

			case PWM_CHANNEL4:
				PwmTim[PwmTimHwUnit]->CCMR2 &= ~(TIM_CCMR2_OC4M_Msk); //clear bitfield 
				if(ChannelConfig->OutputMode == PWM_MODE_1){
					PwmTim[PwmTimHwUnit]->CCMR2 |= (PWM_1 << TIM_CCMR2_OC4M_Pos); 
				}
				else if(ChannelConfig->OutputMode == PWM_MODE_2){
					PwmTim[PwmTimHwUnit]->CCMR2 |= (PWM_2 << TIM_CCMR2_OC4M_Pos); 
				}
				else{
					return E_NOT_OK;
				}

				PwmTim[PwmTimHwUnit]->CCMR2 |= TIM_CCMR2_OC4PE; //enable preload 
				PwmTim[PwmTimHwUnit]->CCER |= TIM_CCER_CC4E;	//enable output
				PwmTim[PwmTimHwUnit]->CCER &= ~TIM_CCER_CC4NE;	//disable complementary output

				break;

			default:
				return E_NOT_OK;
				break;

		}
	}
	
	PwmTim[PwmTimHwUnit]->BDTR |= TIM_BDTR_MOE;
	PwmTim[PwmTimHwUnit]->BDTR &= ~TIM_BDTR_OSSR;

	return E_OK;
}
