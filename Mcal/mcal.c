#include "mcal.h"

void Mcal_DelayUs(uint32 us)
{
    volatile uint32 count = (SystemCoreClock / 4000000UL) * us;
    while (count--) {
        __NOP();
    }
}

Std_ReturnType Mcal_WaitBitTimeout(volatile uint32 *Reg, uint32 Mask, uint32 ExpectedValue, uint32 TimeoutUs){
	uint32 elapsed = 0U;
    	while((*Reg & Mask) != ExpectedValue){
        	Mcal_DelayUs(1);
        	elapsed++;
        	if(elapsed >= TimeoutUs){
            	return E_NOT_OK;
        	}
    	}
    	return E_OK;
}
