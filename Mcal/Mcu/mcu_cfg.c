#include "mcu_cfg.h"

static const Mcu_PllConfigType Mcu_PllConfig_0 = {
	.PllM = 8;
	.PllN = 100;
	.PllR = 2;
	.PllP = 7;
	.PllQ = 2;
	.PllROutputState = MCU_PLL_ENABLED;
	.PllQOutputState = MCU_PLL_ENABLED;
	.PllPOutputState = MCU_PLL_ENABLED;
	.PllInputSource =  MCU_CLOCKSOURCE_HSE;
}

static const Mcu_PeripherialConfigType Mcu_PeriphClkConfig_0 = {
	APB1_PRE = 0;
	APB2_PRE = 0;
	AHB_PRE = 0;
}

static const Mcu_ClockSettingsConfigType McuClockSettingConfig[] = {
	{
		.SysClkSource = MCU_CLOCKSOURCE_PLL; 
		.FlashLatencyWS = 4;
		.PwrRange = MCU_PWR_RANGE_1;
		.PllConfig = &Mcu_PllConfig_0;
		.PeriphClkConfigType = Mcu_PeriphClkConfig_0;
	}
}

const Mcu_ConfigType Mcu_Config_0 = {
	.ClockSettingsiConfig = &McuClockSettingConfig;
	.Mcu_NumberOfClockSettings = sizeof(ClockSettingConfig)/sizeof(ClockSettingConfig[0]);
}
