
#include "BSP_RCC.hpp"
#include "stm32l031xx.h"

namespace BSP::rcc
{
    void init(void)
    {
        // turn on the HSI clock
        RCC->CR |= RCC_CR_HSION;

        while (!(RCC->CR & RCC_CR_HSIRDY))
        {
            // wait for the HSI clock to be ready
        }

        // use the HSI clock as the clock source
        RCC->CFGR |= RCC_CFGR_SW_HSI;

        while (!(RCC->CFGR & RCC_CFGR_SWS_HSI))
        {
            // wait for the switch to take effect
        }

        // turn the PLL off
        RCC->CR &= ~RCC_CR_PLLON;

        while (RCC->CR & RCC_CR_PLLRDY)
        {
            // wait for the PLL to turn off
        }

        // set the flash latency to 1 wait state
        FLASH->ACR |= FLASH_ACR_LATENCY;

        // set the PLL frequency to HSI * 4 / 2 = 32MHz
        RCC->CFGR |= RCC_CFGR_PLLSRC_HSI | RCC_CFGR_PLLMUL4 | RCC_CFGR_PLLDIV2;

        // turn the PLL back on
        RCC->CR |= RCC_CR_PLLON;

        while (!(RCC->CR & RCC_CR_PLLRDY))
        {
            // wait for the PLL to be ready
        }

        // set the PLL as the clock source
        RCC->CFGR |= RCC_CFGR_SW_PLL;

        while (!(RCC->CFGR & RCC_CFGR_SWS_PLL))
        {
            // wait for the PLL clock switch to come on
        }
    }
}
