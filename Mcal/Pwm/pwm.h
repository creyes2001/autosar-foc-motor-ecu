#ifndef PWM_H
#define PWM_H

#include "pwm_cfg.h"
#include "stm32g431xx.h"

void Pwm_Init(const Pwm_ConfigType* ConfigPtr);
void Pwm_Start(PwmTimHwUnitType PwmTimHwUnit);
void Pwm_Stop(PwmTimHwUnitType PwmTimHwUnit);
void Pwm_SetDutyCycle(PwmTimHwUnitType PwmTimHwUnit,Pwm_ChannelType ChannelNumber,uint16 DutuCycle);
void Pwm_SetPeriodAndDuty(PwmTimHwUnitType PwmTimHwUnit,Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCyle);

#endif //PWM_H
