#include "gpt_cfg.h"

const Gpt_HwTriggerConfigType GptChannelConfig [] = {
	{
		.ChannelId = GPT_CHANNEL_4,
		.HwUnit = GPT_TIM1,
		.Mode = GPT_CH_PWM_MODE_1
	}
};

const Gpt_ConfigType Gpt_Config = {
	.HwTriggerConfig = GptChannelConfig,
	.size = 1
};
