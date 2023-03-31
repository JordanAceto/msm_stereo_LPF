#pragma once

#include <stdint.h>

/** @brief 12 bit SPI DAC */
namespace MCP4822
{
    /** @brief the number of bits in the DAC */
    const int NUM_BITS = 12;

    /** @brief the maximum value of the DAC */
    const int FULL_SCALE = (1 << NUM_BITS) - 1;

    /** @brief enumeration of the MCP4822 channels */
    enum Channel
    {
        A = 0u,
        B = 1u
    };

    /**
     * @brief Write the given 12 bit value to the DAC.
     *
     * @param value_ui12 the 12 bit value to write
     * @param channel the enumerated channel to write to, A or B
     */
    void write(int value_ui12, Channel channel);
}
