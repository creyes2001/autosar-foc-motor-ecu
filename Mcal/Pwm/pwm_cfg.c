#include "pwm_cfg.h"

const Pwm_ChannelConfigType ChannelConfig [] = {
	{
		.ChannelId = PWM_CHANNEL1,
		.OutputMode = PWM_MODE_1,
		.Polarity = PWM_ACTIVE_HIGH
	},
	
	{
		.ChannelId = PWM_CHANNEL2,
		.OutputMode = PWM_MODE_1,
		.Polarity = PWM_ACTIVE_HIGH
	},
	
	{
		.ChannelId = PWM_CHANNEL3,
		.OutputMode = PWM_MODE_1,
		.Polarity = PWM_ACTIVE_HIGH
	}
};

const Pwm_ConfigType Pwm_Config = {
	.HwUnit = PWM_TIM1,
	.ClkSrc = PWM_INTERNAL_CLOCK,
	.Presc = 0,
	.Period = 1875,
	.Mode = PWM_CENTER_ALIGNED,
	.UpdateRate = PWM_UPDATE1, //Repetitio counter
	.EdgeNotification = PWM_BOTH_EDGES,
	.NumberOfChannels = 3,
	.Pwm_ChannelConfig = ChannelConfig
};
