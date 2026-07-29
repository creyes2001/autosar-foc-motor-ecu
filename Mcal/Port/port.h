#ifndef PORT_H
#define PORT_H

#include "stm32g431xx.h"
#include "port_cfg.h"

void Port_Init(const Port_ConfigType* ConfigPtr);
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
void Port_RefreshPortDirection(void);
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode);

#endif //PORT_H
