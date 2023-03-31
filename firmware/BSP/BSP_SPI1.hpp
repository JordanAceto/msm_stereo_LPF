
#pragma once

#include <stdint.h>

/** @brief Serial Peripheral Interface 1 */
namespace BSP::spi1
{
    /**
     * @brief Initialize SPI1.
     *
     * SPI is setup as master with 16 bit data frames.
     */
    void init(void);

    /**
     * @brief Transmit the given value via SPI1.
     *
     * @param value the value to transmit
     */
    void transmit(uint16_t value);
}
