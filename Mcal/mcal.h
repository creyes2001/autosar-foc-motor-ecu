#ifndef MCAL_h
#define MCAL_H

#include "Std_Types.h"
#include "Platform_Types.h"
#include "stm32g431xx.h"

void Mcal_DelayUs(uint32 us);
Std_ReturnType Mcal_WaitBitTimeout(volatile uint32 *Reg, uint32 Mask, uint32 ExpectedValue, uint32 TimeoutUs);

#endif //MCAL_H
