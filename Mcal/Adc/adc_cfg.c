#include "adc_cfg.h"

const Adc_ChannelConfigType Adc_ChannelConfig[] = {
	{
		.Channel = ADC1_CH1,
		.InputMode = ADC_INPUT_SINGLE_ENDED,
		.SamplingTime = ADC_6_5_CLOCK_CYCLES
	}
};

const Adc_GroupConfigType Adc_GroupConfig[] = {
	{
		.GroupType = ADC_GROUP1,
		.NumberOfConversions = 1,
		.ConversionType = ADC_INJECTED_CONVERSION,
		.ValueGroup = 0,
		.ConversionMode = ADC_CONV_MODE_ONESHOT,
		.TriggerSource = ADC_TRIGG_SRC_HW,
		.HwTriggerSignal = ADC_HW_TRIG_RISING_EDGE,
		.HwTriggerSrc = ADC_EXT_TRG,
		.GroupAccessMode = ADC_ACCESS_MODE_SINGLE,
		.Adc_ChannelConfig = Adc_ChannelConfig
	}
};

const Adc_ConfigDataType Adc_ConfigData[] = {
	{
		.Adc_HWUnit = ADC_HW_1,
		.Adc_Resolution = ADC_BITS_12,
		.Adc_ResultAligment = ADC_ALIGN_RIGHT,
		.Adc_GroupConfig = Adc_GroupConfig,
		.Adc_NumberOfGroups = 1 
	}
};

const Adc_ConfigType Adc_Config = {
	.Adc_ConfigData = Adc_ConfigData,
	.Adc_ClkSrc = ADC_CLK_SYN_PRE2,
	.size = 1
};
