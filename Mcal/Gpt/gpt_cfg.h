#ifndef GPT_CFG_H
#define GPT_CFG_H

#include "Std_Types.h"
#include "Platform_Types.h"

typedef uint8 Gpt_ChannelType;
typedef uint8 Gpt_TimHwUnitType;
 
#define PWM_TIM1 ((Gpt_TimHwUnitType)0x00)
#define PWM_TIM8 ((Gpt_TimHwUnitType)0x01)

typedef enum{
	GPT_TRIGGER_ACTIVE_HIGH = 0x00,
	GPT_TRIGGER_ACTIVE_LOW = 0x01,
}Gpt_HwTriggerPolarityType;

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
	Gpt_HwTriggerPolarityType Polarity;
}Gpt_HwTriggerConfigType;

typedef struct{
	const Gpt_HwTriggerConfigType* HwTriggerConfig;

}Gpt_ConfigType;


#endif //GPT_CFG_H
