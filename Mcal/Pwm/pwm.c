#include "pwm.h"

static Std_ReturnType Pwm_ClockConfig(PwmTimHwUnitType PwmTimHwUnit,Pwm_CLkSrcType ClkSrc,Pwm_PrescType Presc);
static Std_ReturnType Pwm_SetCounterMode(PwmTimHwUnitType PwmTimHwUnit,Pwm_ModeType Mode,Pwm_EdgeNotificationType Notification);
static Std_ReturnType Pwm_SetUpdateRate(PwmTimHwUnitType PwmTimHwUnit,Pwm_UpdateRateType UpdateRate);

static volatile TIM_TypeDef* PwmTim[2] = {TIM1,TIM8};

void Pwm_Init(const Pwm_ConfigType* ConfigPtr){
	
	if((PwmTim[ConfigPtr->HwUnit]->CR1 & TIM_CR1_CEN) != 0U){
		PwmTim[ConfigPtr->HwUnit]->CR1 &= ~TIM_CR1_CEN; 
	}

	Pwm_ClockConfig(ConfigPtr->HwUnit,ConfigPtr->ClkSrc,ConfigPtr->Presc);
		
}

void Pwm_Start(PwmTimHwUnitType PwmTimHwUnit){
	
}

void Pwm_Stop(PwmTimHwUnitType PwmTimHwUnit){

}

void Pwm_SetDutyCycle(PwmTimHwUnitType PwmTimHwUnit,Pwm_ChannelType ChannelNumber,uint16 DutuCycle){

}

void Pwm_SetPeriodAndDuty(PwmTimHwUnitType PwmTimHwUnit,Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCyle){

}

static Std_ReturnType Pwm_ClockConfig(PwmTimHwUnitType PwmTimHwUnit,Pwm_CLkSrcType ClkSrc,Pwm_PrescType Presc){
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

static Std_ReturnType Pwm_SetCounterMode(PwmTimHwUnitType PwmTimHwUnit,Pwm_ModeType Mode,Pwm_EdgeNotificationType Notification){
	switch(Mode){
		case PWM_RIGTH_ALIGNED:
			//TODO: implement
			break;
		case PWM_LEFT_ALIGNED:
			//TODO: implement
			break;
		case PWM_CENTER_ALIGNED:
			PwmTim[PwmTimHwunit]->CR1 &= ~TIM_CR1_CMS; //clear 
			if(Notification == PWM_RISING_EDGE){
				PwmTim[PwmTimHwunit]->CR1 |= TIM_CR1_CMS_1; 
			}
			else if(Notification == PWM_FALLING_EDGE){
				PwmTim[PwmTimHwunit]->CR1 |= TIM_CR1_CMS_0; 
			}
			else if(Notification == PWM_BOTH_EDGES){
				PwmTim[PwmTimHwunit]->CR1 |= TIM_CR1_CMS; 
			}
			else{
				return E_NOT_OK;
			break;
		default:
			return E_NOT_OK;
			break;
	}
			return E_OK;
}

static Std_ReturnType Pwm_SetUpdateRate(PwmTimHwUnitType PwmTimHwUnit,Pwm_UpdateRateType UpdateRate){
	if(UpdateRate > 0xFFFFu){
		return E_NOT_OK;
	}
	PwmTim[PwmTimHwunit]->RCR = (uint32)UpdateRate; 
	return E_OK;
}
