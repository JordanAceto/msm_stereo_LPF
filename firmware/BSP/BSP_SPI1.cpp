
#include "BSP_SPI1.hpp"
#include "stm32l031xx.h"

namespace BSP::spi1
{
    void init(void)
    {
        RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

        // make sure GPIO port A is enabled
        RCC->IOPENR |= RCC_IOPENR_IOPAEN;

        // SS output enabled in master mode
        SPI1->CR2 |= SPI_CR2_SSOE;

        SPI1->CR1 |= SPI_CR1_DFF | // data frame formal = 16 bits
                    SPI_CR1_BR_1 | // prescaler = divide by 8
                    SPI_CR1_MSTR | // master mode
                    SPI_CR1_SPE;   // enable SPI1
    }

    void transmit(uint16_t value)
    {
        __disable_irq();

        // chip select low
        GPIOA->BSRR = GPIO_BSRR_BR_6;

        // write the value to the data register
        SPI1->DR = value;

        while (!(SPI1->SR & SPI_SR_TXE))
        {
            // wait for TX buffer to be empty
        }

        while (SPI1->SR & SPI_SR_BSY)
        {
            // wait for transmission to complete
        }

        // chip select high
        GPIOA->BSRR = GPIO_BSRR_BS_6;

        __enable_irq();
    }
}
