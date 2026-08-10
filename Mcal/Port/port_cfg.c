#include "port_cfg.h"

const Port_ConfigDataType Port_CfgData[] = {
	{
		//On-board led configuration
		.PinId = PORT_A_PIN_5,
		.Pin_Mode = PORT_PIN_MODE_DO,
		.Pin_Direction = PORT_PIN_OUT,
		.Pin_Speed = PORT_PIN_MEDIUM_SPEED,
		.Pin_OutputType = PORT_PIN_OUT_OPEN_DRAIN,
		.Pin_ResistorType = PORT_PIN_RESISTOR_PULLUP,
		.DirectionChangable = TRUE,
		.ModeChangable = TRUE
	},
	{
		//MCO pin configuration 
		.PinId = PORT_A_PIN_8,
		.Pin_Mode = PORT_PIN_MODE_AF0,
		.Pin_Direction = PORT_PIN_OUT,
		.Pin_Speed = PORT_PIN_HIGH_SPEED,
		.Pin_OutputType = PORT_PIN_OUT_PUSH_PULL,
		.Pin_ResistorType = PORT_PIN_RESISTOR_DISABLE,
		.DirectionChangable = FALSE,
		.ModeChangable = FALSE
	}
};

const Port_ConfigType Port_Config = {
	.Port_ConfigData = Port_CfgData,
	.size = 1
};
