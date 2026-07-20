#ifndef MCU_CFG_H
#define MCU_CFG_H

#include "Platform_Types.h"
#include "Std_Types.h"
#include "stm32g431xx.h"

typedef uint8 Mcu_ClockType;
typedef uint8 Mcu_FlashLatencyWSType;

typedef enum{
	MCU_CLOCKSOURCE_HSE,
	MCU_CLOCKSOURCE_HSI,
	MCU_CLOCKSOURCE_PLL
}Mcu_ClockSourceType;

typedef enum{
	MCU_PWR_RANGE_1,
	MCU_PWR_RANGE_2
}Mcu_PwrRangeType;


typedef enum{
	MCU_PWR_CLK_ENABLE,
	MCU_PWR_CLK_DISABLE
}Mcu_PwrClkStateType;


typedef enum{
	MCU_HSE_ON,
	MCU_HSE_OFF
}Mcu_HseStateType;

typedef enum{
	MCU_HSE_RDY,
	MCU_HSE_NOT_RDY
}Mcu_HseStatusType;


typedef enum{
	MCU_PLL_ENABLED,
	MCU_PLL_DISABLED
}Mcu_PllOutputStateType;


typedef enum{
	MCU_PLL_ON,
	MCU_PLL_OFF
}Mcu_PllStateType;


typedef enum{
	MCU_PLL_LOCKED = 0,
	MCU_PLL_UNLOCKED,
	MCU_PLL_STATUS_UNDEFINED
}Mcu_PllStatusType;


typedef enum{
	MCU_HSE_SW,
	MCU_HSI16_SW,
	MCU_PLL_SW
}Mcu_SysclkSwType;

typedef enum{
MCU_HSE_SWS,
	MCU_HSI16_SWS,
	MCU_PLL_SWS
}Mcu_SysclkSwStatusType;

typedef struct{
	uint8  PllM;
	uint16 PllN;
	uint8  PllR;
	uint8  PllP;
	uint8  PllQ;
	Mcu_PllOutputStateType PllROutputState;
	Mcu_PllOutputStateType PllQOutputState;
	Mcu_PllOutputStateType PllPOutputState;
	Mcu_ClockSourceType 	PllInputSource;
}Mcu_PllConfigType;

typedef struct{
	uint8 APB1_PRE;
	uint8 APB2_PRE;
	uint16 AHB_PRE;
}Mcu_PeripherialConfigType;

typedef struct{
	Mcu_ClockSourceType 			 SysClkSource;
	Mcu_FlashLatencyWSType	 		 FlashLatencyWS;
	Mcu_PwrRangeType				 PwrRange;
	const Mcu_PllConfigType*   		 PllConfig;
	const Mcu_PeripherialConfigType* PeriphClkConfig;
}Mcu_ClockSettingsConfigType;

typedef struct{
	const Mcu_ClockSettingsConfigType* ClockSettingsConfig;
	uint8 Mcu_NumberOfClockSettings;
}Mcu_ConfigType;

#endif //MCU_CFG_H
