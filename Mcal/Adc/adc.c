#include "adc.h"
#include "stm32g431xx.h"
#include "mcal.h"

#define MAX_ADC_GROUPS 4
#define ADC_CALIBRATION_TIMEOUT_US 1000U 
#define ADC_ENABLE_TIMEOUT_US 1000U

static void Adc_Start(Adc_HWUnitType HWUnit);
static void Adc_Stop(Adc_HWUnitType HWUnit);
static Std_ReturnType Adc_Enable(Adc_HWUnitType HWUnit); 
static Std_ReturnType Adc_Disable(Adc_HWUnitType HWUnit); 
static void Adc_SetResolution(Adc_HWUnitType HWUnit,Adc_ResolutionType Resolution); 

static const ADC_TypeDef* Hw_Unit[2] = {ADC1,ADC2}; //to get the CMSIS definition
static Adc_ConfigDataType* Adc_Data[MAX_ADC_GROUPS];//to hold the ConfigData struct pointer

void Adc_Init (const Adc_ConfigType* ConfigPtr){
	for(uint8 i = 0; i < ConfigPtr->size; i++){	
		
		Adc_ConfigDataType* ConfigData = ConfigPtr->Adc_ConfigData[i];
		Adc_SetResolution(ConfigData.Adc_HWUnit,ConfigData.Adc_Resolution);
		
		for(unit8 j = 0; j < ConfigData.Adc_NumberOfGroups; j++){
			const Adc_GroupConfigType* GroupConfig = ConfigData->Adc_GroupConfig[j];
			Adc_Data[GroupConfig.GroupType] = ConfigData; //assign the actual ConfigDatapointer at GroupType position in the array
			
			for(uint8 c = 0; c < GroupConfig.NumberOfConvertionsType)
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

}

static void Adc_SetResolution(Adc_HWUnitType HWUnit,Adc_ResolutionType Resolution){
	HW_Unit[HWUnit]->ADC_CFGR &= ~(ADC_CFGR_RES); //clear the bit field	
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

