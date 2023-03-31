
#include "BSP_ADC1.hpp"
#include "BSP_DMA.hpp"
#include "BSP_GPIO.hpp"
#include "BSP_RCC.hpp"
#include "BSP_SPI1.hpp"
#include "BSP_system_init.hpp"
#include "BSP_TIM2.hpp"


namespace BSP::system_init
{
    void init(void)
    {
        BSP::rcc::init();
        BSP::tim2::init();
        BSP::gpio::init();
        BSP::spi1::init();
        BSP::adc1::init();
        BSP::dma::init();
    }
}
