#ifndef ADC_CFG_H
#define ADC_CFG_H

typedef uint Adc_ChannelType;	//ID of an ADC channel
typedef uint Adc_GroupType;		//ID of an ADC group
typedef int Adc_ValueGroupType;
typedef uint Adc_PrescaleType;
typedef uint Adc_ConversionTimeType;
typedef uint Adc_SamplingTimeType;
typedef uint8 Adc_ResolutionType;
typedef uint8 Adc_GroupPriorityType;
typedef Adc_GroupDefType; //assigment of channels to a chanel group
typedef uint Adc_StreamNumSampleType;

/////////////////////////////////////
typedef uint8 Adc_NumerOfConversionsType;

typedef enum{
	ADC_INPUT_SINGLE_ENDED = 0x00;
	ADC_INPUT_DIFFERENTIAL = 0x01;
}Adc_InputModeType;

typedef enum{
	ADC_REGULAR_CONVERSION = 0x00;
	ADC_INJECTED_CONVERSION = 0x01;
}Adc_ConversionType;
//////////////////////////////////////////////

typedef enum{
	ADC_STREAM_BUFFER_LINEAR = 0x00;
	ADC_STREAM_BUFFER_CIRCULAR = 0x01;
}Adc_StreamBufferModeType;

typedef enum{
	ADC_ACCESS_MODE_SINGLE = 0x00;
	ADC_ACCESS_MODE_STREAMING = 0x01;
}Adc_GroupAccessModeType;

typedef enum{
	ADC_HW_TRIG_RISING_EDGE = 0x00;
	ADC_HW_TRIG_FALLING_EDGE = 0x01;
	ADC_HW_TRIG_BOTH_EDGES = 0x02;
}Adc_HwTriggerSignalType;

typedef enum{
	ADC_IDLE = 0x00;
	ADC_BUSY = 0x01;
	ADC_COMPLETED = 0x02;
	ADC_STREAM_COMPLETED = 0x03;
}Adc_StatusType;

typedef enum{
	ADC_TRIGG_SRC_SW = 0x00;
	ADC_TRIGG_SRC_HW = 0x01;
}Adc_TriggerSourceType;

typedef enum{
	ADC_CONV_MODE_ONESHOT = 0x00;
	ADC_CONV_MODE_CONTINUOUS = 0x01;
}Adc_GroupConvModeType;

typedef enum{
	ADC_RANGE_UNDER_LOW = 0x00;
	ADC_RANGE_BETWEEN = 0x01;
	ADC_RANGE_OVER_HIGH = 0x02;
	ADC_RANGE_ALWAYS = 0x03;
	ADC_RANGE_NOT_UNDER_LOW = 0x04;
	ADC_RANGE_NOT_BETWEEN = 0x05;
	ADC_RANGE_NOT_OVER_HIGH = 0x06;
}Adc_ChannelRangeSelectType;

typedef enum{
	ADC_ALIGN_LEFT = 0x00;
	ADC_ALIGN_RIGHT = 0x01;
}Adc_ResultAlignmentType;

//struct for channel specific configuration data
typedef struct{
	Adc_ChannelType Channel;
	Adc_InputModeType InputMode;
	Adc_SamplingTimeType SamplingTime;
	Adc_ChannelRangeSelecttype ChannelRange;
}Adc_ChannelConfigtype;

typedef struct{
	Adc_GroupType GroupType; 	
	Addc_GroupPriorityType Priority;
	Adc_NumberOfConvertionsType NumberOfConversions; //Channels to be converted
	Adc_ConversionType ConversionType; //injected or regular
	Adc_ValueGroupType ValueGroup;
	Adc_GroupConvModetype ConversionMode;
	Adc_ConversionTimetype ConversionType;
	Adc_TroggerSourceType TriggerSource;
	Adc_HwTriggerSignalType HwTriggerSignal;
	Adc_GroupAccessModeType GroupAccessMode;
	Adc_Stream_BufferModeType StreamBufferMode;
	Adc_Stream_NumSampleType StreamNumSample;
	Adc_ResultAligmentType ResultAligment;
}Adc_GroupConfigType;

//struct for ADC device configuration data
typedef struct{
	Adc_ResolutionType Resolution;

}Adc_DeviceConfigType;

//struct for general configuration data
typedef struct{

}Adc_SettingsConfigType;

//struct that holds the main array configuration data
typedef struct{

}Adc_ConfigType;

extern const Adc_Configtype Adc_Config;

#endif //ADC_CFG_H
