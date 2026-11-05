#include "gpt_cfg.h"

const Gpt_ChannelConfigType ChannelConfig [] = {
	{
		.Channel = GPT_CHANNEL4,
		.HwUnit = GPT_TIM1,
		.Mode = GPT_PWM_MODE_1
	}
};

const Gpt_ConfigType GptConfig = {
	.Gpt_ChannelConfig = ChannelConfig,
	.size = 1
};
