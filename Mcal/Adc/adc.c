#include "adc.h"
#include "mcal.h"

#define MAX_ADC_GROUPS 4
#define ADC_CALIBRATION_TIMEOUT_US 1000U 
#define ADC_ENABLE_TIMEOUT_US 1000U
#define ADC_DISABLE_TIMEOUT_US 1000U
#define ADC_STOP_TIMEOUT_US 1000U
#define ADC_JSTOP_TIMEOUT_US 1000U

static void Adc_Start(Adc_HWUnitType HWUnit);
static void Adc_Stop(Adc_HWUnitType HWUnit);
static Std_ReturnType Adc_Enable(Adc_HWUnitType HWUnit); 
static Std_ReturnType Adc_Disable(Adc_HWUnitType HWUnit); 
static void Adc_SetResolution(Adc_HWUnitType HWUnit,Adc_ResolutionType Resolution); 
static Std_ReturnType Adc_Calibration(Adc_HWUnitType HWUnit,Adc_ConversionType Conversion);//must be called after Adc_Start
static Std_ReturnType Adc_DataAligment(Adc_HWUnitType HWUnit,Adc_ResultAligmentType ResultAligment);
static Std_ReturnType Adc_SetChannelInputMode(Adc_HWUnitType HWUnit,Adc_ChannelType ChannelId,Adc_InputModeType InputM);//must be called when ADC is disable
static Std_ReturnType Adc_SetChannelSamplingTime(Adc_HWUnitType HWUnit,Adc_ChannelType ChannelId,Adc_SamplingTimeType SamplingT);
static Std_ReturnType Adc_SetGroupChannels(Adc_HWUnitType HWUnit,Adc_ConversionType Conversion,Adc_NumberOfConversionsType NumberOfConversions,const Adc_ChannelConfigType* ChannelConfig);
static Std_ReturnType Adc_SetTriggerSrc(Adc_HWUnitType HWUnit,Adc_TriggerSourceType Trigger,Adc_HwTriggerSignalType Signal,Adc_ConversionType Conversion, Adc_HwTriggSrcType HwTriggSrc);
static Std_ReturnType Adc_ConversionMode(Adc_HWUnitType HWUnit,Adc_GroupConvModeType ConvMode);

static volatile ADC_TypeDef* const HW_Unit[2] = {ADC1,ADC2}; //to get the CMSIS definition
static const Adc_ConfigDataType* Adc_Data[MAX_ADC_GROUPS];//to hold the ConfigData struct pointer

void Adc_Init (const Adc_ConfigType* ConfigPtr){
	for(uint8 i = 0; i < ConfigPtr->size; i++){	
		
		const Adc_ConfigDataType* ConfigData = &ConfigPtr->Adc_ConfigData[i];
		
		Adc_Start(ConfigData->Adc_HWUnit);
		Adc_Disable(ConfigData->Adc_HWUnit);
		Adc_SetResolution(ConfigData->Adc_HWUnit,ConfigData->Adc_Resolution);
		Adc_DataAligment(ConfigData->Adc_HWUnit,ConfigData->Adc_ResultAligment);
		
		for(uint8 j = 0; j < ConfigData->Adc_NumberOfGroups; j++){
			
			const Adc_GroupConfigType* GroupConfig = &ConfigData->Adc_GroupConfig[j];
			Adc_Data[GroupConfig->GroupType] = ConfigData; //assign the actual ConfigDatapointer at GroupType position in the array

			Adc_Calibration(ConfigData->Adc_HWUnit,GroupConfig->ConversionType);
			if(GroupConfig->ConversionType == ADC_REGULAR_CONVERSION){ //injected mode cannot be converted continuously
				Adc_ConversionMode(ConfigData->Adc_HWUnit,GroupConfig->ConversionMode);
			}
			Adc_SetTriggerSrc(ConfigData->Adc_HWUnit,GroupConfig->TriggerSource,GroupConfig->HwTriggerSignal,GroupConfig->ConversionType,GroupConfig->HwTriggerSrc);
			Adc_SetGroupChannels(ConfigData->Adc_HWUnit,GroupConfig->ConversionType,GroupConfig->NumberOfConversions, GroupConfig->Adc_ChannelConfig);

			for(uint8 c = 0; c < GroupConfig->NumberOfConversions; c++){
				
				const Adc_ChannelConfigType* ChannelConfig = &GroupConfig->Adc_ChannelConfig[c];	
				Adc_SetChannelInputMode(ConfigData->Adc_HWUnit,ChannelConfig->Channel,ChannelConfig->InputMode);
				Adc_SetChannelSamplingTime(ConfigData->Adc_HWUnit,ChannelConfig->Channel,ChannelConfig->SamplingTime);
			
			}
		}
	}
}


void Adc_DeInit (void){
	//TODO:implement
}

void Adc_StartGroupConversion (Adc_GroupType Group){
	if(Adc_Data[Group]->Adc_GroupConfig[Group].ConversionType == ADC_REGULAR_CONVERSION)
	{
		HW_Unit[Adc_Data[Group]->Adc_HWUnit]->CR |= ADC_CR_ADSTART;
	}
	if(Adc_Data[Group]->Adc_GroupConfig[Group].ConversionType == ADC_INJECTED_CONVERSION)
	{
		HW_Unit[Adc_Data[Group]->Adc_HWUnit]->CR |= ADC_CR_JADSTART;
	}
}

void Adc_StopGroupConversion (Adc_GroupType Group){
	if(Adc_Data[Group]->Adc_GroupConfig[Group].ConversionType == ADC_REGULAR_CONVERSION)
	{
		HW_Unit[Adc_Data[Group]->Adc_HWUnit]->CR |= ADC_CR_ADSTP;
		Mcal_WaitBitTimeout(&HW_Unit[Adc_Data[Group]->Adc_HWUnit]->CR,ADC_CR_ADSTART,0U,ADC_STOP_TIMEOUT_US);

	}
	if(Adc_Data[Group]->Adc_GroupConfig[Group].ConversionType == ADC_INJECTED_CONVERSION)
	{
		HW_Unit[Adc_Data[Group]->Adc_HWUnit]->CR |= ADC_CR_JADSTP;
		Mcal_WaitBitTimeout(&HW_Unit[Adc_Data[Group]->Adc_HWUnit]->CR,ADC_CR_JADSTART,0U,ADC_JSTOP_TIMEOUT_US);

	}

}

Std_ReturnType Adc_ReadGroup (Adc_GroupType Group,Adc_ValueGroupType* DataBufferPtr){
	volatile static uint8 i = 0;
	if(Adc_Data[Group]->Adc_GroupConfig[Group].ConversionType ==  ADC_REGULAR_CONVERSION){
		DataBufferPtr[i] = HW_Unit[Adc_Data[Group]->Adc_HWUnit]->DR;
		i++;
		if(HW_Unit[Adc_Data[Group]->Adc_HWUnit]->ISR && ADC_ISR_EOS){ //end of sequence of conversions
			HW_Unit[Adc_Data[Group]->Adc_HWUnit]->ISR |= ADC_ISR_EOS;
			i = 0;
		}
	}
	else if(Adc_Data[Group]->Adc_GroupConfig[Group].ConversionType == ADC_INJECTED_CONVERSION){
		switch(Adc_Data[Group]->Adc_GroupConfig[Group].NumberOfConversions){
			case 1U:
				DataBufferPtr[0] = HW_Unit[Adc_Data[Group]->Adc_HWUnit]->JDR1;
				break;
			case 2U:
				DataBufferPtr[1] = HW_Unit[Adc_Data[Group]->Adc_HWUnit]->JDR1;
				break;
			case 3U:
				DataBufferPtr[2] = HW_Unit[Adc_Data[Group]->Adc_HWUnit]->JDR1;
				break;
			case 4U:
				DataBufferPtr[3] = HW_Unit[Adc_Data[Group]->Adc_HWUnit]->JDR1;
				break;
			default:
				break;
		}

	}
	else{
		return E_NOT_OK;
	}
	return E_OK;
}

void Adc_EnableHardwareTrigger (Adc_GroupType Group){
	//TODO:implement
}

void Adc_DisableHardwareTrigger (Adc_GroupType Group){
	//TODO:implement
}

Adc_StatusType Adc_GetGroupStatus (Adc_GroupType Group){
	//TODO:implement
}


static void Adc_Start(Adc_HWUnitType HWUnit){
	HW_Unit[HWUnit]->CR &= ~ADC_CR_DEEPPWD;
	HW_Unit[HWUnit]->CR |= ADC_CR_ADVREGEN; 
	Mcal_DelayUs(40); //startup delay time
}

static void Adc_Stop(Adc_HWUnitType HWUnit){
	HW_Unit[HWUnit]->CR &= ~ADC_CR_ADEN;
	HW_Unit[HWUnit]->CR &= ADC_CR_DEEPPWD;
}

static Std_ReturnType Adc_Enable(Adc_HWUnitType HWUnit){
	if(Mcal_WaitBitTimeout(&HW_Unit[HWUnit]->CR,ADC_CR_ADCAL,0U,ADC_CALIBRATION_TIMEOUT_US) != E_OK){
		return E_NOT_OK;
	}
	else{
		HW_Unit[HWUnit]->ISR |= ADC_ISR_ADRDY;
		HW_Unit[HWUnit]->CR |= ADC_CR_ADEN;
		if(Mcal_WaitBitTimeout(&HW_Unit[HWUnit]->ISR,ADC_ISR_ADRDY,ADC_ISR_ADRDY,ADC_ENABLE_TIMEOUT_US) != E_OK){
			return E_NOT_OK;
		}
		HW_Unit[HWUnit]->ISR |= ADC_ISR_ADRDY;
	}
	return E_OK;

}

static Std_ReturnType Adc_Disable(Adc_HWUnitType HWUnit){
	if((HW_Unit[HWUnit]->CR & ADC_CR_ADSTART) == ADC_CR_ADSTART){
		HW_Unit[HWUnit]->CR |= ADC_CR_ADSTP;
		if(Mcal_WaitBitTimeout(&HW_Unit[HWUnit]->CR,ADC_CR_ADSTP,0U,ADC_STOP_TIMEOUT_US) != E_OK){
			return E_NOT_OK;
		}
	}
	if((HW_Unit[HWUnit]->CR & ADC_CR_JADSTART) == ADC_CR_JADSTART){
		HW_Unit[HWUnit]->CR |= ADC_CR_JADSTP;
		if(Mcal_WaitBitTimeout(&HW_Unit[HWUnit]->CR,ADC_CR_JADSTP,0U,ADC_JSTOP_TIMEOUT_US) != E_OK){
			return E_NOT_OK;
		}
	}
	
	HW_Unit[HWUnit]->CR |= ADC_CR_ADDIS;

	if(Mcal_WaitBitTimeout(&HW_Unit[HWUnit]->CR,ADC_CR_ADEN,0U,ADC_DISABLE_TIMEOUT_US) != E_OK){
		return E_NOT_OK;
	}
	return E_OK;
}

static void Adc_SetResolution(Adc_HWUnitType HWUnit,Adc_ResolutionType Resolution){
	HW_Unit[HWUnit]->CFGR &= ~(ADC_CFGR_RES); //clear the bit field	
	switch(Resolution){
		case ADC_BITS_6:
		HW_Unit[HWUnit]->CFGR |= ADC_CFGR_RES;	
		break;
	
		case ADC_BITS_8:
		HW_Unit[HWUnit]->CFGR |= ADC_CFGR_RES_1;		
		break;

		case ADC_BITS_10:
		HW_Unit[HWUnit]->CFGR |= ADC_CFGR_RES_0;	
		break;

		case ADC_BITS_12:
		HW_Unit[HWUnit]->CFGR &= ~(ADC_CFGR_RES);	
		break;

		default:
		HW_Unit[HWUnit]->CFGR |= ADC_CFGR_RES;	//ADC set as 6-bit resolution by default	
		break;
	}
}

static Std_ReturnType Adc_Calibration(Adc_HWUnitType HWUnit,Adc_ConversionType Conversion){
	if((HW_Unit[HWUnit]->CR & ADC_CR_ADEN) == ADC_CR_ADEN){
		if(Adc_Disable(HWUnit) != E_OK){
			return E_NOT_OK;
		}
	}

	if(Conversion == ADC_INPUT_SINGLE_ENDED){
		HW_Unit[HWUnit]->CR &= ~ADC_CR_ADCALDIF; 
	}
	else if(Conversion == ADC_INPUT_DIFFERENTIAL){
		HW_Unit[HWUnit]->CR |= ADC_CR_ADCALDIF; 
	}
	else{
		return E_NOT_OK;
	}

	HW_Unit[HWUnit]->CR |= ADC_CR_ADCAL;

	if(Mcal_WaitBitTimeout(&HW_Unit[HWUnit]->CR,ADC_CR_ADCAL,0U,ADC_CALIBRATION_TIMEOUT_US) != E_OK){
		return E_NOT_OK;
	}
	return E_OK;
}

static Std_ReturnType Adc_DataAligment(Adc_HWUnitType HWUnit,Adc_ResultAligmentType ResultAligment){
	if(ResultAligment == ADC_ALIGN_LEFT){
		HW_Unit[HWUnit]->CFGR |= ADC_CFGR_ALIGN;
	}
	else if(ResultAligment == ADC_ALIGN_RIGHT){
		HW_Unit[HWUnit]->CFGR &= ~ADC_CFGR_ALIGN;
	}
	else{
		return E_NOT_OK;
	}
	return E_OK;
}

static Std_ReturnType Adc_SetChannelInputMode(Adc_HWUnitType HWUnit,Adc_ChannelType ChannelId,Adc_InputModeType InputM){

	if((HW_Unit[HWUnit]->CR & ADC_CR_ADEN) == ADC_CR_ADEN){
        if(Adc_Disable(HWUnit) != E_OK){
            return E_NOT_OK;
        }
    }

	if(InputM == ADC_INPUT_SINGLE_ENDED){
	HW_Unit[HWUnit]->DIFSEL &= ~(1UL << ChannelId);
	}

	else if(InputM == ADC_INPUT_DIFFERENTIAL) {
	HW_Unit[HWUnit]->DIFSEL |= (1UL << ChannelId);
	}

	else{
		return E_NOT_OK;
	}

	return E_OK;
}

static Std_ReturnType Adc_SetChannelSamplingTime(Adc_HWUnitType HWUnit,Adc_ChannelType ChannelId,Adc_SamplingTimeType SamplingT){
	
	if(((HW_Unit[HWUnit]->CR & ADC_CR_ADSTART) == ADC_CR_ADSTART) || ((HW_Unit[HWUnit]->CR & ADC_CR_JADSTART) == ADC_CR_JADSTART)){
        if(Adc_Disable(HWUnit) != E_OK){
            return E_NOT_OK;
        }
    }

	if(ChannelId <= 0x09){	//from channel 0 to 9
		HW_Unit[HWUnit]->SMPR1 &= ~(ADC_SMPR1_SMP0 << (ChannelId * 3));	
		HW_Unit[HWUnit]->SMPR1 |= ((SamplingT & 0x7U)<< (ChannelId * 3));
	}

	else if(ChannelId >= 0x0A && ChannelId <= 0x12) { //from channel 10 to 18
		HW_Unit[HWUnit]->SMPR2 &= ~(ADC_SMPR2_SMP10 << ((ChannelId - 0x0A)* 3));	
		HW_Unit[HWUnit]->SMPR2 |= ((SamplingT & 0x7U) << ((ChannelId - 0x0A) * 3));
	}

	else{
		return E_NOT_OK;
	}

	return E_OK;
}


static Std_ReturnType Adc_SetGroupChannels(Adc_HWUnitType HWUnit,Adc_ConversionType Conversion,Adc_NumberOfConversionsType NumberOfConversions,const Adc_ChannelConfigType* ChannelConfig){
		
	if((HW_Unit[HWUnit]->CR & ADC_CR_ADEN) == ADC_CR_ADEN){
		if(Adc_Disable(HWUnit) != E_OK){
			return E_NOT_OK;
		}
	}
		if(Conversion == ADC_REGULAR_CONVERSION){
			HW_Unit[HWUnit]->SQR1 &= ~ADC_SQR1_L;	
			HW_Unit[HWUnit]->SQR1 |= (NumberOfConversions << ADC_SQR1_L_Pos);

			for(uint8 i = 0U; i < NumberOfConversions; i++){
				if(i >= 0 && i<= 3){
					HW_Unit[HWUnit]->SQR1 |= (ChannelConfig[i].Channel << (ADC_SQR1_SQ1_Pos + (i*6)));
				}
				else if(i >= 4 && i<= 8){
					HW_Unit[HWUnit]->SQR2 |= (ChannelConfig[i].Channel << (ADC_SQR2_SQ5_Pos + ((i-4)*6)));
				}
				else if(i >= 9 && i<= 13){
					HW_Unit[HWUnit]->SQR3 |= (ChannelConfig[i].Channel << (ADC_SQR3_SQ10_Pos + ((i-9)*6)));
				}
				else if(i >= 14 && i<= 15){
					HW_Unit[HWUnit]->SQR4 |= (ChannelConfig[i].Channel << (ADC_SQR4_SQ15_Pos + ((i-14)*6)));
				}
			}
		}
		else if(Conversion == ADC_INJECTED_CONVERSION){
			HW_Unit[HWUnit]->JSQR &= ~ADC_JSQR_JL;
			HW_Unit[HWUnit]->JSQR |= (NumberOfConversions << ADC_JSQR_JL_Pos);
			
			for(uint8 i = 0U; i < NumberOfConversions; i++){
				HW_Unit[HWUnit]->JSQR |= (ChannelConfig[i].Channel << (ADC_JSQR_JSQ1_Pos + (i*6)));
			}

		}
		else{
			return E_NOT_OK;
		}
	
	return E_OK;
}

static Std_ReturnType Adc_SetTriggerSrc(Adc_HWUnitType HWUnit,Adc_TriggerSourceType Trigger,Adc_HwTriggerSignalType Signal,Adc_ConversionType Conversion, Adc_HwTriggSrcType HwTriggSrc){
	
	if((HW_Unit[HWUnit]->CR & ADC_CR_ADEN) == ADC_CR_ADEN){
		if(Adc_Disable(HWUnit) != E_OK){
			return E_NOT_OK;
		}
	}

	if(Conversion == ADC_REGULAR_CONVERSION){
		if(Trigger == ADC_TRIGG_SRC_SW){
			HW_Unit[HWUnit]->CFGR &= ~ADC_CFGR_EXTEN;
		}
		else if(Trigger == ADC_TRIGG_SRC_HW){
			HW_Unit[HWUnit]->CFGR &= ~ADC_CFGR_EXTEN;	//clear 
			switch(Signal){
				case ADC_HW_TRIG_RISING_EDGE:
					HW_Unit[HWUnit]->CFGR |= ADC_CFGR_EXTEN_0;
					break;
				case ADC_HW_TRIG_FALLING_EDGE:
					HW_Unit[HWUnit]->CFGR |= ADC_CFGR_EXTEN_1;
					break;
				case ADC_HW_TRIG_BOTH_EDGES:
					HW_Unit[HWUnit]->CFGR |= ADC_CFGR_EXTEN;
					break;
				default:
					break;
			}
			
			HW_Unit[HWUnit]->CFGR &= ~ADC_CFGR_EXTSEL;	//clear
			HW_Unit[HWUnit]->CFGR |= (HwTriggSrc << ADC_CFGR_EXTSEL_Pos);	//set the haedware trigger source	
		}
		else{
			return E_NOT_OK;
		}
	}

	else if(Conversion == ADC_INJECTED_CONVERSION){
		if(Trigger == ADC_TRIGG_SRC_SW){
			HW_Unit[HWUnit]->JSQR &= ~ADC_JSQR_JEXTEN;
		}
		else if(Trigger == ADC_TRIGG_SRC_HW){
			HW_Unit[HWUnit]->JSQR &= ~ADC_JSQR_JEXTEN;	//clear
			switch(Signal){
				case ADC_HW_TRIG_RISING_EDGE:
					HW_Unit[HWUnit]->JSQR |= ADC_JSQR_JEXTEN_0;
					break;
				case ADC_HW_TRIG_FALLING_EDGE:
					HW_Unit[HWUnit]->JSQR |= ADC_JSQR_JEXTEN_1;
					break;
				case ADC_HW_TRIG_BOTH_EDGES:
					HW_Unit[HWUnit]->JSQR |= ADC_JSQR_JEXTEN;
					break;
				default:
					break;
			}
			HW_Unit[HWUnit]->JSQR &= ~ADC_JSQR_JEXTSEL;	//clear
			HW_Unit[HWUnit]->JSQR |= (HwTriggSrc << ADC_JSQR_JEXTSEL_Pos);	//set the hardware trigger source
		}
		else{
			return E_NOT_OK;
		}
	
	}

	else{
		return E_NOT_OK;
	}
	
	return E_OK;
}

static Std_ReturnType Adc_ConversionMode(Adc_HWUnitType HWUnit,Adc_GroupConvModeType ConvMode){
		
	if((HW_Unit[HWUnit]->CR & ADC_CR_ADEN) == ADC_CR_ADEN){
		if(Adc_Disable(HWUnit) != E_OK){
			return E_NOT_OK;
		}
	}

	if(ConvMode == ADC_CONV_MODE_ONESHOT){
		HW_Unit[HWUnit]->CFGR |= ADC_CFGR_CONT;
	}
	else if(ConvMode == ADC_CONV_MODE_CONTINUOUS){
		HW_Unit[HWUnit]->CFGR &= ~ADC_CFGR_CONT;
	}
	else{
		return E_NOT_OK;
	}
	return E_OK;
}
	
