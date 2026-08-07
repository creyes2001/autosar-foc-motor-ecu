#include "port_cfg.h"

const Port_ConfigDataType Port_Config[] = {
	{
		.PinId = PORT_A_PIN_5,
		.Pin_Mode = PORT_PIN_MODE_DO,
		.Pin_Direction = PORT_PIN_OUT,
		.Pin_Speed = PORT_PIN_MEDIUM_SPEED,
		.Pin_OutputType = PORT_PIN_OUT_OPEN_DRAIN,
		.Pin_ResistorType = PORT_PIN_RESISTOR_DISABLE,
		.DirectionChangable = TRUE,
		.ModeChangable = TRUE
	}
};
