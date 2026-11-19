#ifndef GPT_H
#define GPT_H

#include "gpt_cfg.h"
#include "stm32g431xx.h"
#include "gpt_irq.h"

void Gpt_Init(const Gpt_ConfigType* ConfigPtr);
void Gpt_SetTriggerCompare(Gpt_ChannelType Channel,uint16 compare);
void Gpt_EnableHwTrigger(Gpt_ChannelType Channel);
void Gpt_DisableHwTrigger(Gpt_ChannelType Channel);

#endif //GPT_H
