#include "BSP_RCC.hpp"
#include "BSP_TIM2.hpp"
#include "stm32l031xx.h"

namespace BSP::tim2
{
    void init(void)
    {
        // enable clock control
        RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

        // set master mode selection to update TRGO
        TIM2->CR2 |= TIM_CR2_MMS_1;

        // set the frequency to the desired value
        TIM2->PSC = 100u - 1u;
        TIM2->ARR = ((BSP::rcc::SYSTEM_CORE_CLOCK / 100u) / FREQUENCY_Hz)  - 1u;

        // enable the timer
        TIM2->CR1 |= TIM_CR1_CEN;
    }

    bool getTimeout(void)
    {
        // if it timed out
        if (TIM2->SR & TIM_SR_UIF)
        {
            // clear the flag and return true
            TIM2->SR &= ~TIM_SR_UIF;
            return true;
        }
        return false;
    }
}
