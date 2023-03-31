
#include "BSP_GPIO.hpp"
#include "stm32l031xx.h"

namespace BSP::gpio
{
    static void enable_GPIO_clock_control(void);

    static void set_switch_pins_to_input_pullup(void);

    static void setup_spi_pins(void);

    void init()
    {
        enable_GPIO_clock_control();
        set_switch_pins_to_input_pullup();
        setup_spi_pins();
    }

    bool getPinState(pin_t pin)
    {
        bool retval = 0;
        switch (pin)
        {
        case pin_t::PA9:
            retval = (GPIOA->IDR >> 9u) & 1u;
            break;
        case pin_t::PA10:
            retval = (GPIOA->IDR >> 10u) & 1u;
            break;
        case pin_t::PC14:
            retval = (GPIOC->IDR >> 14u) & 1u;
            break;
        case pin_t::PC15:
            retval = (GPIOC->IDR >> 15u) & 1u;
            break;
        }

        return retval;
    }

    void enable_GPIO_clock_control(void)
    {
        RCC->IOPENR |= RCC_IOPENR_IOPAEN | RCC_IOPENR_GPIOBEN | RCC_IOPENR_GPIOCEN;
    }

    void set_switch_pins_to_input_pullup(void)
    {
        // set pins to inputs
        GPIOA->MODER &= ~GPIO_MODER_MODE9_Msk;
        GPIOA->MODER &= ~GPIO_MODER_MODE10_Msk;
        GPIOC->MODER &= ~GPIO_MODER_MODE14_Msk;
        GPIOC->MODER &= ~GPIO_MODER_MODE15_Msk;

        // enable pullups
        GPIOA->PUPDR |= GPIO_PUPDR_PUPD9_0;
        GPIOA->PUPDR |= GPIO_PUPDR_PUPD10_0;
        GPIOC->PUPDR |= GPIO_PUPDR_PUPD14_0;
        GPIOC->PUPDR |= GPIO_PUPDR_PUPD15_0;
    }

    void setup_spi_pins(void)
    {
        // set spi SCK and MOSI to special function
        GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
        GPIOA->MODER &= ~GPIO_MODER_MODE7_Msk;
        GPIOA->MODER |= GPIO_MODER_MODE5_1;
        GPIOA->MODER |= GPIO_MODER_MODE7_1;

        // set spi CS pin to output
        GPIOA->MODER &= ~GPIO_MODER_MODE6_Msk;
        GPIOA->MODER |= GPIO_MODER_MODE6_0;

        // write the CS pin high
        GPIOA->BSRR = GPIO_BSRR_BS_6;
    }
}
