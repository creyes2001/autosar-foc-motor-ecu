#ifndef GPT_CFG_H
#define GPT_CFG_H

#include "Std_Types.h"
#include "Platform_Types.h"

typedef uint8 Gpt_ChannelType;
typedef uint8 Gpt_TimHwUnitType;
 
#define PWM_TIM1 ((Gpt_TimHwUnitType)0x00)
#define PWM_TIM8 ((Gpt_TimHwUnitType)0x01)

#define GPT_CHANNEL_1 ((Gpt_ChannelType)0x00)
#define GPT_CHANNEL_2 ((Gpt_ChannelType)0x01)
#define GPT_CHANNEL_3 ((Gpt_ChannelType)0x02)
#define GPT_CHANNEL_4 ((Gpt_ChannelType)0x03)


typedef enum{
	GPT_CH_FROZEN = 0x00,
	GPT_CH_SET_ACTIVE = 0x01,
	GPT_CH_SET_INACTIVE = 0x02,
	GPT_CH_TOGGLE = 0x03,
	GPT_CH_FORCE_INACTIVE = 0x04,
	GPT_CH_FORCE_ACTIVE = 0x05,
	GPT_CH_PWM_MODE_1 = 0x06,
	GPT_CH_PWM_MODE_2 = 0x07
}Gpt_ChannelModeType;

typedef struct{
	Gpt_ChannelType ChannelId;
	Gpt_TimHwUnitType HwUnit;
	Gpt_ChannelModeType Mode;
}Gpt_HwTriggerConfigType;

typedef struct{
	const Gpt_HwTriggerConfigType* HwTriggerConfig;
	uint8 size;
}Gpt_ConfigType;


#endif //GPT_CFG_H
