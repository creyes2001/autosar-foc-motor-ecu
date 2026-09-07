#include "mcal.h"

void Mcal_DelayUs(uint32_t us)
{
    volatile uint32_t count = (SystemCoreClock / 4000000UL) * us;
    while (count--) {
        __NOP();
    }
}
