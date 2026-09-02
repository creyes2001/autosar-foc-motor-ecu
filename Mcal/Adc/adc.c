#include "adc.h"
#include "stm32g431xx.h"

static ADC_TypeDef* Adc_GetAdcHWUnit(Adc_HWUnitType HWUnit);
static void Adc_SetResolution(Adc_ResolutionType Resolution); 

void Adc_Init (const Adc_ConfigType* ConfigPtr){
	for(uint8 i = 0; i < ConfigPtr->size; i++){	
		
		const Adc_ConfigDataType* ConfigData = ConfigPtr->Adc_ConfigData[i];
		Adc_SetResolution(ConfigData.Adc_Resolution);
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

static void Adc_SetResolution(Adc_ResolutionType Resolution){
	//TODO:implement
}

static ADC_TypeDef* Adc_GetAdcHWUnit(Adc_HWUnitType HWUnit){
	if(HWUnit == ADC_HW_2){
		return ADC2;
	}
	else{
		return ADC1;
	}
}
