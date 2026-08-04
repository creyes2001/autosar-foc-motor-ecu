#ifndef PORT_CFG_H
#define PORT_CFG_H

#include "Std_Types.h"
#include "Platform_Types.h"

//Ports table
//Modes table

typedef uint8 Port_PinType;
typedef uint8 Port_PinModeType;

typedef enum {
	PORT_PIN_IN = 0,
	PORT_PIN_OUT = 1
}Port_PinDirectionType;

typedef enum{
	PORT_PIN_LOW_SPEED = 0,
	PORT_PIN_MEDIUM_SPEED = 1,
	PORT_PIN_FAST_SPEED = 2,
	PORT_PIN_HIGH_SPEED = 3,
}Port_PinSpeedType;

typedef enum{
	PORT_PIN_OUT_PUSH_PULL = 0,
	PORT_PIN_OUT_OPEN_DRAIN = 1
}Port_PinOutputType;

typedef enum{
	PORT_PIN_RESISTOR_PULLUP = 0,
	PORT_PIN_RESISTOR_PULLDOWN =1,
	PORT_PIN_RESISTOR_DISABLE = 2
}Port_PinResistorType;

typedef struct {
	Port_PinType			PinId;
	Port_PinModeType		Pin_Mode;
	Port_PinDirectionType	Pin_Direction;
	Port_PinSpeedType		Pin_Speed;
	Port_PinOutputType		Pin_OutputType;
	Port_PinResistorType	Pin_ResistorType;
	boolean					DirectionChangable;
	boolean					ModeChangable;
}Port_ConfigDataType;

typedef struct {
	Port_ConfigDataType* Port_ConfigData;
	uint32 size;
}Port_ConfigType;

extern const Port_ConfigType Port_Config[];

#endif //PORT_CFG_H
