#ifndef ADC_CFG_H
#define ADC_CFG_H

#include "Std_Types.h"
#include "Platform_Types.h"

typedef uint8 Adc_ChannelType;	//ID of an ADC channel
typedef uint8 Adc_GroupType;		//ID of an ADC group
typedef uint8 Adc_HWUnitType;

#define ADC1_CH1 ((Adc_ChannelType)0x00)
#define ADC1_CH2 ((Adc_ChannelType)0x01)
#define ADC1_CH3 ((Adc_ChannelType)0x02)
#define ADC1_CH4 ((Adc_ChannelType)0x03)
#define ADC1_CH5 ((Adc_ChannelType)0x04)
#define ADC1_CH6 ((Adc_ChannelType)0x05)
#define ADC1_CH7 ((Adc_ChannelType)0x06)
#define ADC1_CH8 ((Adc_ChannelType)0x07)
#define ADC1_CH9 ((Adc_ChannelType)0x08)
#define ADC1_CH10 ((Adc_ChannelType)0x09)
#define ADC1_CH11 ((Adc_ChannelType)0x0A)
#define ADC1_CH12 ((Adc_ChannelType)0x0B)
#define ADC1_CH13 ((Adc_ChannelType)0x0C)
#define ADC1_CH14 ((Adc_ChannelType)0x0D)
#define ADC1_CH15 ((Adc_ChannelType)0x0E)
#define ADC1_CH16 ((Adc_ChannelType)0x0F)
#define ADC1_CH17 ((Adc_ChannelType)0x10)
#define ADC1_CH18 ((Adc_ChannelType)0x20)

#define ADC2_CH1 ((Adc_ChannelType)0x00)
#define ADC2_CH2 ((Adc_ChannelType)0x01)
#define ADC2_CH3 ((Adc_ChannelType)0x02)
#define ADC2_CH4 ((Adc_ChannelType)0x03)
#define ADC2_CH5 ((Adc_ChannelType)0x04)
#define ADC2_CH6 ((Adc_ChannelType)0x05)
#define ADC2_CH7 ((Adc_ChannelType)0x06)
#define ADC2_CH8 ((Adc_ChannelType)0x07)
#define ADC2_CH9 ((Adc_ChannelType)0x08)
#define ADC2_CH10 ((Adc_ChannelType)0x09)
#define ADC2_CH11 ((Adc_ChannelType)0x0A)
#define ADC2_CH12 ((Adc_ChannelType)0x0B)
#define ADC2_CH13 ((Adc_ChannelType)0x0C)
#define ADC2_CH14 ((Adc_ChannelType)0x0D)
#define ADC2_CH15 ((Adc_ChannelType)0x0E)
#define ADC2_CH16 ((Adc_ChannelType)0x0F)
#define ADC2_CH17 ((Adc_ChannelType)0x10)
#define ADC2_CH18 ((Adc_ChannelType)0x20)

#define ADC_GROUP1 ((Adc_GroupType)0x00)
#define ADC_GROUP2 ((Adc_GroupType)0x01)
#define ADC_GROUP3 ((Adc_GroupType)0x02)
#define ADC_GROUP4 ((Adc_GroupType)0x03)

#define ADC_HW_1 ((Adc_HWUnitType)0x00)
#define ADC_HW_2 ((Adc_HWUnitType)0x01)

#define ADC_BITS_6   ((Adc_ResolutionType)0x06U)
#define ADC_BITS_8   ((Adc_ResolutionType)0x08U)
#define ADC_BITS_10  ((Adc_ResolutionType)0x0AU)
#define ADC_BITS_12  ((Adc_ResolutionType)0x0CU)

#define ADC_2_5_CLOCK_CYCLES	((Adc_SamplingTimeType)0x00)
#define ADC_6_5_CLOCK_CYCLES	((Adc_SamplingTimeType)0x01)
#define ADC_12_5_CLOCK_CYCLES	((Adc_SamplingTimeType)0x02)
#define ADC_24_5_CLOCK_CYCLES	((Adc_SamplingTimeType)0x03)
#define ADC_47_5_CLOCK_CYCLES	((Adc_SamplingTimeType)0x04)
#define ADC_92_5_CLOCK_CYCLES	((Adc_SamplingTimeType)0x05)
#define ADC_247_5_CLOCK_CYCLES	((Adc_SamplingTimeType)0x06)
#define ADC_640_5_CLOCK_CYCLES	((Adc_SamplingTimeType)0x07)

#define ADC_EXT_TRG		((Adc_HwTriggSrcType)0x00)
#define ADC_EXT_TRG1	((Adc_HwTriggSrcType)0x01)
#define ADC_EXT_TRG2	((Adc_HwTriggSrcType)0x02)
#define ADC_EXT_TRG3	((Adc_HwTriggSrcType)0x03)
#define ADC_EXT_TRG4	((Adc_HwTriggSrcType)0x04)
#define ADC_EXT_TRG5	((Adc_HwTriggSrcType)0x05)
#define ADC_EXT_TRG6	((Adc_HwTriggSrcType)0x06)
#define ADC_EXT_TRG7	((Adc_HwTriggSrcType)0x07)
#define ADC_EXT_TRG8	((Adc_HwTriggSrcType)0x08)
#define ADC_EXT_TRG9	((Adc_HwTriggSrcType)0x09)
#define ADC_EXT_TRG10	((Adc_HwTriggSrcType)0x0A)
#define ADC_EXT_TRG11	((Adc_HwTriggSrcType)0x0B)
#define ADC_EXT_TRG12	((Adc_HwTriggSrcType)0x0C)
#define ADC_EXT_TRG13	((Adc_HwTriggSrcType)0x0D)
#define ADC_EXT_TRG14	((Adc_HwTriggSrcType)0x0E)
#define ADC_EXT_TRG15	((Adc_HwTriggSrcType)0x0F)
#define ADC_EXT_TRG16	((Adc_HwTriggSrcType)0x10)
#define ADC_EXT_TRG17	((Adc_HwTriggSrcType)0x11)
#define ADC_EXT_TRG18	((Adc_HwTriggSrcType)0x12)
#define ADC_EXT_TRG19	((Adc_HwTriggSrcType)0x13)
#define ADC_EXT_TRG20	((Adc_HwTriggSrcType)0x14)
#define ADC_EXT_TRG21	((Adc_HwTriggSrcType)0x15)
#define ADC_EXT_TRG22	((Adc_HwTriggSrcType)0x16)
#define ADC_EXT_TRG23	((Adc_HwTriggSrcType)0x17)
#define ADC_EXT_TRG24	((Adc_HwTriggSrcType)0x18)
#define ADC_EXT_TRG25	((Adc_HwTriggSrcType)0x19)
#define ADC_EXT_TRG26	((Adc_HwTriggSrcType)0x1A)
#define ADC_EXT_TRG27	((Adc_HwTriggSrcType)0x1B)
#define ADC_EXT_TRG28	((Adc_HwTriggSrcType)0x1C)
#define ADC_EXT_TRG29	((Adc_HwTriggSrcType)0x1D)
#define ADC_EXT_TRG30	((Adc_HwTriggSrcType)0x1E)
#define ADC_EXT_TRG31	((Adc_HwTriggSrcType)0x1F)

typedef uint8 Adc_ValueGroupType;
typedef uint8 Adc_PrescaleType;
typedef uint8 Adc_ConversionTimeType;
typedef uint8 Adc_SamplingTimeType;
typedef uint8 Adc_ResolutionType;
typedef uint8 Adc_GroupDefType; //assigment of channels to a chanel group
typedef uint8 Adc_StreamNumSampleType;
typedef uint8 Adc_NumberOfConversionsType;
typedef uint8 Adc_NumberOfGroupsType;
typedef uint8 Adc_HwTriggSrcType;

typedef enum{
	ADC_INPUT_SINGLE_ENDED = 0x00,
	ADC_INPUT_DIFFERENTIAL = 0x01
}Adc_InputModeType;

typedef enum{
	ADC_REGULAR_CONVERSION = 0x00,
	ADC_INJECTED_CONVERSION = 0x01
}Adc_ConversionType;

typedef enum{
	ADC_STREAM_BUFFER_LINEAR = 0x00,
	ADC_STREAM_BUFFER_CIRCULAR = 0x01
}Adc_StreamBufferModeType;

typedef enum{
	ADC_ACCESS_MODE_SINGLE = 0x00,
	ADC_ACCESS_MODE_STREAMING = 0x01
}Adc_GroupAccessModeType;

typedef enum{
	ADC_HW_TRIG_RISING_EDGE = 0x00,
	ADC_HW_TRIG_FALLING_EDGE = 0x01,
	ADC_HW_TRIG_BOTH_EDGES = 0x02
}Adc_HwTriggerSignalType;

typedef enum{
	ADC_IDLE = 0x00,
	ADC_BUSY = 0x01,
	ADC_COMPLETED = 0x02,
	ADC_STREAM_COMPLETED = 0x03
}Adc_StatusType;

typedef enum{
	ADC_TRIGG_SRC_SW = 0x00,
	ADC_TRIGG_SRC_HW = 0x01
}Adc_TriggerSourceType;

typedef enum{
	ADC_CONV_MODE_ONESHOT = 0x00,
	ADC_CONV_MODE_CONTINUOUS = 0x01
}Adc_GroupConvModeType;

typedef enum{
	ADC_RANGE_UNDER_LOW = 0x00,
	ADC_RANGE_BETWEEN = 0x01,
	ADC_RANGE_OVER_HIGH = 0x02,
	ADC_RANGE_ALWAYS = 0x03,
	ADC_RANGE_NOT_UNDER_LOW = 0x04,
	ADC_RANGE_NOT_BETWEEN = 0x05,
	ADC_RANGE_NOT_OVER_HIGH = 0x06
}Adc_ChannelRangeSelectType;

typedef enum{
	ADC_ALIGN_LEFT = 0x00,
	ADC_ALIGN_RIGHT = 0x01
}Adc_ResultAligmentType;

//struct for channel specific configuration data
typedef struct{
	Adc_ChannelType Channel;
	Adc_InputModeType InputMode;
	Adc_SamplingTimeType SamplingTime;
}Adc_ChannelConfigType;

typedef struct{
	Adc_GroupType GroupType; 	
	Adc_NumberOfConversionsType NumberOfConversions; //Channels to be converted
	Adc_ConversionType ConversionType; //injected or regular
	Adc_ValueGroupType ValueGroup;
	Adc_GroupConvModeType ConversionMode;
	Adc_ConversionTimeType ConversionTimeType;
	Adc_TriggerSourceType TriggerSource;
	Adc_HwTriggerSignalType HwTriggerSignal;
	Adc_HwTriggSrcType HwTriggerSrc;
	Adc_GroupAccessModeType GroupAccessMode;
	Adc_StreamBufferModeType StreamBufferMode;
	Adc_StreamNumSampleType StreamNumSample;
	const Adc_ChannelConfigType* Adc_ChannelConfig;
}Adc_GroupConfigType;

typedef struct{
	Adc_HWUnitType Adc_HWUnit;
	Adc_ResolutionType Adc_Resolution;
	Adc_ResultAligmentType ResultAligment;
	const Adc_GroupConfigType* Adc_GroupConfig;
	Adc_NumberOfGroupsType Adc_NumberOfGroups;
}Adc_ConfigDataType;

//struct for ADC configuration data
typedef struct{
	const Adc_ConfigDataType* Adc_ConfigData; 
	uint8 size;
}Adc_ConfigType;

extern const Adc_ConfigType* Adc_Config;

#endif //ADC_CFG_H
