#include "adc.h"
#include "stm32g431xx.h"

static void Adc_SetResolution(Adc_HWUnitType HWUnit,Adc_ResolutionType Resolution); 

static const ADC_TypeDef* Hw_Unit[2] = {ADC1,ADC2}; //array to get the CMSIS definition

void Adc_Init (const Adc_ConfigType* ConfigPtr){
	for(uint8 i = 0; i < ConfigPtr->size; i++){	
		
		Adc_ConfigDataType* ConfigData = ConfigPtr->Adc_ConfigData[i];
		Adc_SetResolution(ConfigData.Adc_HWUnit,ConfigData.Adc_Resolution);
		for(unit8 j = 0; j < ConfigData.Adc_NumberOfGroups; j++){
			const Adc_GroupConfigType* GroupConfig = ConfigData->Adc_GroupConfig[j];

		}

	}
}

Std_ReturnType Adc_SetupResultBuffer (Adc_GroupType Group,Adc_ValueGroupType* DataBufferPtr){
	//TODO:implement
}

void Adc_DeInit (void){
	//TODO:implement
}

void Adc_StartGroupConversion (Adc_GroupType Group){
	//TODO:implement
}

void Adc_StopGroupConversion (Adc_GroupType Group){
	//TODO:implement
}

Std_ReturnType Adc_ReadGroup (Adc_GroupType Group,Adc_ValueGroupType* DataBufferPtr){
	//TODO:implement
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

Adc_StreamNumSampleType Adc_GetStreamLastPointer (Adc_GroupType Group,Adc_ValueGroupType** PtrToSamplePtr){
	//TODO:implement
}

static void Adc_SetResolution(Adc_HWUnitType HWUnit,Adc_ResolutionType Resolution){
	HW_Unit[HWUnit]->ADC_CFGR &= ~(ADC_CFGR_RES); //clear the bit field	
	switch(Resolution){
		case ADC_BITS_6:
		HW_Unit[HWUnit]->ADC_CFGR |= ADC_CFGR_RES;	
		break;
	
		case ADC_BITS_8:
		HW_Unit[HWUnit]->ADC_CFGR |= ADC_CFGR_RES_1;		
		break;

		case ADC_BITS_10:
		HW_Unit[HWUnit]->ADC_CFGR |= ADC_CFGR_RES_0;	
		break;

		case ADC_BITS_12:
		HW_Unit[HWUnit]->ADC_CFGR &= ~(ADC_CFGR_RES);	
		break;

		default:
		HW_Unit[HWUnit]->ADC_CFGR |= ADC_CFGR_RES;	//ADC set as 6-bit resolution by default	
		break;
	}
}

