#ifndef ADC_H
#define ADC_H

#include "adc_cfg.h"
#include "stm32g431xx.h"

void Adc_Init (const Adc_ConfigType* ConfigPtr);
Std_ReturnType Adc_SetupResultBuffer (Adc_GroupType Group,Adc_ValueGroupType* DataBufferPtr);
void Adc_DeInit (void);
void Adc_StartGroupConversion (Adc_GroupType Group);
void Adc_StopGroupConversion (Adc_GroupType Group);
Std_ReturnType Adc_ReadGroup (Adc_GroupType Group,Adc_ValueGroupType* DataBufferPtr);
void Adc_EnableHardwareTrigger (Adc_GroupType Group);
void Adc_DisableHardwareTrigger (Adc_GroupType Group);
Adc_StatusType Adc_GetGroupStatus (Adc_GroupType Group);
Adc_StreamNumSampleType Adc_GetStreamLastPointer (Adc_GroupType Group,Adc_ValueGroupType** PtrToSamplePtr);


#endif //ADC_H
