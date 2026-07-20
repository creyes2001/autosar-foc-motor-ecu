#include "mcu.h"

static const Mcu_ConfigType* Mcu_ConfigPtr = NULL_PTR;

static void Mcu_EnableHSE(void);
static void Mcu_PllCofiguration(const Mcu_PllConfigType* PllSetting);
static void Mcu_PheripherialConfiguration(const Mcu_PeripherialConfigType* PeriphSetting);
static void Mcu_FlashLatencyConfiguration(Mcu_FlashLatencyWSType FlashSetting);
static void Mcu_PwrRangeConfiguration(Mcu_PwrRangeType PwrRangeSetting);

void Mcu_Init(const Mcu_ConfigType *ConfigPtr){
	Mcu_ConfigPtr = ConfigPtr;
}

Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting){
	if(Mcu_ConfigPtr == NULL_PTR){
		return E_NOT_OK;
	}
	if(ClockSetting >= Mcu_ConfigPtr->Mcu_NumberOfClockSettings){
		return E_NOT_OK;
	}
	
	const Mcu_ClockSettingsConfigType* ClkSetting = &Mcu_ConfigPtr->ClockSettingsConfig[ClockSetting];
	

	Mcu_EnableHSE();
	Mcu_FlashLatencyConfiguration(ClkSetting->FlashLatencyWS);
	Mcu_PwrRangeConfiguration(ClkSetting->PwrRange);
	Mcu_PllCofiguration(ClkSetting->PllConfig);	
	Mcu_PheripherialConfiguration(ClkSetting->PeriphClkConfig);

	return E_OK;
}


Std_ReturnType Mcu_DistributePllClock(void){	
	if(!(RCC->CR & RCC_CR_PLLRDY)){	
		return E_NOT_OK;
	}
	RCC->CFGR &= ~RCC_CFGR_SW_Msk;
	RCC->CFGR |= RCC_CFGR_SW_PLL; 
	while((RCC->CFGR & RCC_CFGR_SWS) !=  RCC_CFGR_SWS_PLL);
	return E_OK;
}

Mcu_PllStatusType Mcu_GetPllStatus(void){
		if(RCC->CR & RCC_CR_PLLRDY){
			return MCU_PLL_LOCKED;
		}
		return MCU_PLL_UNLOCKED;
}

static void Mcu_EnableHSE(void){
	RCC->CR |= RCC_CR_HSEON;                     
	while (!(RCC->CR & RCC_CR_HSERDY)) { }         
}

static void Mcu_PllCofiguration(const Mcu_PllConfigType* PllSetting){
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM_Msk << RCC_PLLCFGR_PLLM_Pos);
	RCC->PLLCFGR |= (PllSetting->PllM << RCC_PLLCFGR_PLLM_Pos);

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLN_Msk << RCC_PLLCFGR_PLLN_Pos);
	RCC->PLLCFGR |= (PllSetting->PllN << RCC_PLLCFGR_PLLN_Pos);

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLR_Msk << RCC_PLLCFGR_PLLR_Pos);
	RCC->PLLCFGR |= (PllSetting->PllR << RCC_PLLCFGR_PLLR_Pos);

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLP_Msk << RCC_PLLCFGR_PLLP_Pos);
	RCC->PLLCFGR |= (PllSetting->PllP << RCC_PLLCFGR_PLLP_Pos);
	
	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLQ_Msk << RCC_PLLCFGR_PLLQ_Pos);
	RCC->PLLCFGR |= (PllSetting->PllQ << RCC_PLLCFGR_PLLQ_Pos);

	if(PllSetting->PllROutputState == MCU_PLL_ENABLED){
		RCC->PLLCFGR |= (RCC_PLLCFGR_PLLREN << RCC_PLLCFGR_PLLREN_Pos);	
	}
	else{
		RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLREN << RCC_PLLCFGR_PLLREN_Pos);	
	}

	if(PllSetting->PllQOutputState == MCU_PLL_ENABLED){
		RCC->PLLCFGR |= (RCC_PLLCFGR_PLLQEN << RCC_PLLCFGR_PLLQEN_Pos);	
	}
	else{
		RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLQEN << RCC_PLLCFGR_PLLQEN_Pos);	
	}
	
	if(PllSetting->PllPOutputState == MCU_PLL_ENABLED){
		RCC->PLLCFGR |= (RCC_PLLCFGR_PLLPEN << RCC_PLLCFGR_PLLPEN_Pos);	
	}
	else{
		RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLPEN << RCC_PLLCFGR_PLLPEN_Pos);	
	}

	RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLSRC_Msk << RCC_PLLCFGR_PLLSRC_Pos);

	if(PllSetting->PllInputSource == MCU_CLOCKSOURCE_HSE){
		RCC->PLLCFGR |= (RCC_PLLCFGR_PLLSRC_HSE << RCC_PLLCFGR_PLLSRC_HSE_Pos);
	}
	else if(PllSetting->PllInputSource == MCU_CLOCKSOURCE_HSI){
		RCC->PLLCFGR |= (RCC_PLLCFGR_PLLSRC_HSI << RCC_PLLCFGR_PLLSRC_HSI_Pos);
	}

	RCC->CR |= RCC_CR_PLLON;
	Mcu_PllStatusType PllStatus;
    while (PllStatus != MCU_PLL_LOCKED){ }

}

static void Mcu_PheripherialConfiguration(const Mcu_PeripherialConfigType* PeriphSetting){
	RCC->CFGR &= ~(RCC_CFGR_PPRE1 << RCC_CFGR_PPRE1_Pos);		
	RCC->CFGR |= (PeriphSetting->APB1_PRE << RCC_CFGR_PPRE1_Pos);		
	
	RCC->CFGR &= ~(RCC_CFGR_PPRE2 << RCC_CFGR_PPRE2_Pos);		
	RCC->CFGR |= (PeriphSetting->APB2_PRE << RCC_CFGR_PPRE2_Pos);		
	
	RCC->CFGR &= ~(RCC_CFGR_HPRE << RCC_CFGR_HPRE_Pos);		
	RCC->CFGR |= (PeriphSetting->AHB_PRE << RCC_CFGR_HPRE_Pos);		
}

static void Mcu_FlashLatencyConfiguration(Mcu_FlashLatencyWSType FlashSetting){
	FLASH->ACR |= (FlashSetting << FLASH_ACR_LATENCY_Pos);
}

static void Mcu_PwrRangeConfiguration(Mcu_PwrRangeType PwrRangeSetting){
	PWR->CR1 &= ~(PWR_CR1_VOS_Msk << PWR_CR1_VOS_Pos);
	PWR->CR1 |= (PwrRangeSetting << PWR_CR1_VOS_Pos); 
}
