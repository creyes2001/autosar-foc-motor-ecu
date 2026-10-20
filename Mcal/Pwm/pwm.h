#ifndef PWM_H
#define PWM_H

#include "pwm_cfg.h"
#include "stm32g431xx.h"

void Pwm_Init(const Pwm_ConfigType* ConfigPtr);
void Pwm_Start(Pwm_TimHwUnitType PwmTimHwUnit);
void Pwm_Stop(Pwm_TimHwUnitType PwmTimHwUnit);
void Pwm_SetDutyCycle(Pwm_TimHwUnitType PwmTimHwUnit,Pwm_ChannelType ChannelNumber,uint16 DutyCycle);
void Pwm_SetPeriodAndDuty(Pwm_TimHwUnitType PwmTimHwUnit,Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle);

#endif //PWM_H
