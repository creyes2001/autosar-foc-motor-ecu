#ifndef PORT_CFG_H
#define PORT_CFG_H

#include "Std_Types.h"
#include "Platform_Types.h"

#define PORT_PIN_MODE_AF0 ((Port_PinModeType)0x00)
#define PORT_PIN_MODE_AF1 ((Port_PinModeType)0x01)
#define PORT_PIN_MODE_AF2 ((Port_PinModeType)0x02)
#define PORT_PIN_MODE_AF3 ((Port_PinModeType)0x03)
#define PORT_PIN_MODE_AF4 ((Port_PinModeType)0x04)
#define PORT_PIN_MODE_AF5 ((Port_PinModeType)0x05)
#define PORT_PIN_MODE_AF6 ((Port_PinModeType)0x06)
#define PORT_PIN_MODE_AF7 ((Port_PinModeType)0x07)
#define PORT_PIN_MODE_AF8 ((Port_PinModeType)0x08)
#define PORT_PIN_MODE_AF9 ((Port_PinModeType)0x09)
#define PORT_PIN_MODE_AF10 ((Port_PinModeType)0x0A)
#define PORT_PIN_MODE_AF11 ((Port_PinModeType)0x0B)
#define PORT_PIN_MODE_AF12 ((Port_PinModeType)0x0C)
#define PORT_PIN_MODE_AF13 ((Port_PinModeType)0x0D)
#define PORT_PIN_MODE_AF14 ((Port_PinModeType)0x0E)
#define PORT_PIN_MODE_AF15 ((Port_PinModeType)0x0F)
#define PORT_PIN_MODE_DI ((Port_PinModeType)0x10)
#define PORT_PIN_MODE_DO ((Port_PinModeType)0x11)
#define PORT_PIN_MODE_ANALOG ((Port_PinModeType)0x12)

#define PORT_A_PIN_0 ((Port_PinType)0x00)
#define PORT_A_PIN_1 ((Port_PinType)0x01)
#define PORT_A_PIN_2 ((Port_PinType)0x02)
#define PORT_A_PIN_3 ((Port_PinType)0x03)
#define PORT_A_PIN_4 ((Port_PinType)0x04)
#define PORT_A_PIN_5 ((Port_PinType)0x05)
#define PORT_A_PIN_6 ((Port_PinType)0x06)
#define PORT_A_PIN_7 ((Port_PinType)0x07)
#define PORT_A_PIN_8 ((Port_PinType)0x08)
#define PORT_A_PIN_9 ((Port_PinType)0x09)
#define PORT_A_PIN_10 ((Port_PinType)0x0A)
#define PORT_A_PIN_11 ((Port_PinType)0x0B)
#define PORT_A_PIN_12 ((Port_PinType)0x0C)
#define PORT_A_PIN_13 ((Port_PinType)0x0D)
#define PORT_A_PIN_14 ((Port_PinType)0x0E)
#define PORT_A_PIN_15 ((Port_PinType)0x0F)

#define PORT_B_PIN_0 ((Port_PinType)0x10)
#define PORT_B_PIN_1 ((Port_PinType)0x11)
#define PORT_B_PIN_2 ((Port_PinType)0x12)
#define PORT_B_PIN_3 ((Port_PinType)0x13)
#define PORT_B_PIN_4 ((Port_PinType)0x14)
#define PORT_B_PIN_5 ((Port_PinType)0x15)
#define PORT_B_PIN_6 ((Port_PinType)0x16)
#define PORT_B_PIN_7 ((Port_PinType)0x17)
#define PORT_B_PIN_8 ((Port_PinType)0x18)
#define PORT_B_PIN_9 ((Port_PinType)0x19)
#define PORT_B_PIN_10 ((Port_PinType)0x1A)
#define PORT_B_PIN_11 ((Port_PinType)0x1B)
#define PORT_B_PIN_12 ((Port_PinType)0x1C)
#define PORT_B_PIN_13 ((Port_PinType)0x1D)
#define PORT_B_PIN_14 ((Port_PinType)0x1E)
#define PORT_B_PIN_15 ((Port_PinType)0x1F)

#define PORT_C_PIN_0 ((Port_PinType)0x20)
#define PORT_C_PIN_1 ((Port_PinType)0x21)
#define PORT_C_PIN_2 ((Port_PinType)0x22)
#define PORT_C_PIN_3 ((Port_PinType)0x23)
#define PORT_C_PIN_4 ((Port_PinType)0x24)
#define PORT_C_PIN_5 ((Port_PinType)0x25)
#define PORT_C_PIN_6 ((Port_PinType)0x26)
#define PORT_C_PIN_7 ((Port_PinType)0x27)
#define PORT_C_PIN_8 ((Port_PinType)0x28)
#define PORT_C_PIN_9 ((Port_PinType)0x29)
#define PORT_C_PIN_10 ((Port_PinType)0x2A)
#define PORT_C_PIN_11 ((Port_PinType)0x2B)
#define PORT_C_PIN_12 ((Port_PinType)0x2C)
#define PORT_C_PIN_13 ((Port_PinType)0x2D)
#define PORT_C_PIN_14 ((Port_PinType)0x2E)
#define PORT_C_PIN_15 ((Port_PinType)0x2F)

#define PORT_D_PIN_0 ((Port_PinType)0x30)
#define PORT_D_PIN_1 ((Port_PinType)0x31)
#define PORT_D_PIN_2 ((Port_PinType)0x32)
#define PORT_D_PIN_3 ((Port_PinType)0x33)

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

extern const Port_ConfigDataType Port_Config[];

#endif //PORT_CFG_H
