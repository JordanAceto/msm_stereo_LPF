
#include "MCP4822.hpp"
#include "BSP_SPI1.hpp"

namespace MCP4822
{
    void write(int value_ui12, Channel channel)
    {
        // limit the input to 12 bits, select channel, set gain to 1x, and enable vout
        const uint16_t word_to_write = (uint16_t)((value_ui12 & FULL_SCALE) | (channel << 15u) | (1u << 13u) | (1u << 12u));
        BSP::spi1::transmit(word_to_write);
    }
}
