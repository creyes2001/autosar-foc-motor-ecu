#ifndef PWM_CFG_H
#define PWM_CFG_H

#include "Std_Types.h"
#include "Platform_Types.h"

typedef uint8 Pwm_TimHwUnitType;
typedef uint8 Pwm_ChannelType;
typedef uint16 Pwm_PeriodType;
typedef uint16 Pwm_PrescType;
typedef uint16 Pwm_UpdateRateType;
typedef uint8 Pwm_NumberOfChannels;

#define PWM_TIM1 ((Pwm_TimHwUnitType)0x00)
#define PWM_TIM8 ((Pwm_TimHwUnitType)0x01)

#define PWM_UPDATE0 ((Pwm_UpdateRateType)0x00)	//update rate of compare registers, it's 16 bits 
#define PWM_UPDATE1 ((Pwm_UpdateRateType)0x01)
#define PWM_UPDATE2 ((Pwm_UpdateRateType)0x02)
#define PWM_UPDATE3 ((Pwm_UpdateRateType)0x03)

#define PWM_CHANNEL1 ((Pwm_ChannelType)0x00)
#define PWM_CHANNEL2 ((Pwm_ChannelType)0x01)
#define PWM_CHANNEL3 ((Pwm_ChannelType)0x02)
#define PWM_CHANNEL4 ((Pwm_ChannelType)0x03)

typedef enum{
	PWM_HIGH = 0x00,
	PWM_LOW = 0x01
}Pwm_OutputStateType;

typedef enum{
	PWM_RISING_EDGE = 0x00,
	PWM_FALLING_EDGE = 0x01,
	PWM_BOTH_EDGES = 0x02
}Pwm_EdgeNotificationType;

typedef enum{
	PWM_RIGTH_ALIGNED = 0x00,
	PWM_LEFT_ALIGNED = 0x01,
	PWM_CENTER_ALIGNED = 0x02
}Pwm_ModeType;

typedef enum{
	PWM_INTERNAL_CLOCK = 0x00,
	PWM_EXTERNAL_CLOCK_MODE1 = 0x01,
	PWM_EXTERNAL_CLOCK_MODE2 = 0x02,
	PWM_ENCODER_MODE = 0x03
}Pwm_ClkSrcType;

typedef enum{
	PWM_ACTIVE_HIGH = 0x00,
	PWM_ACTIVE_LOW = 0x01
}Pwm_PolarityType;

typedef enum{
	PWM_MODE_1 = 0x00,
	PWM_MODE_2 = 0x01
}Pwm_OutputModeType;

typedef struct{
	Pwm_ChannelType ChannelId;
	Pwm_OutputModeType OutputMode;
	Pwm_PolarityType Polarity;
}Pwm_ChannelConfigType;

typedef struct{
	Pwm_TimHwUnitType HwUnit;
	Pwm_ClkSrcType ClkSrc;
	Pwm_PrescType Presc;
	Pwm_PeriodType Period; //Initial value
	Pwm_ModeType Mode;
	Pwm_UpdateRateType UpdateRate;
	Pwm_EdgeNotificationType EdgeNotification; 
	Pwm_NumberOfChannels NumberOfChannels;
	const Pwm_ChannelConfigType* Pwm_ChannelConfig;
}Pwm_ConfigType;

extern const Pwm_ConfigType Pwm_Config;
#endif //PWM_CFG_H
