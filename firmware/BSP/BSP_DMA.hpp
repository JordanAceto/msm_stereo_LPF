
#pragma once

/** @brief Direct Memory Access controller */
namespace BSP::dma
{
    /**
     * @brief Initialize the DMA controller.
     *
     * DMA transfers the raw ADC readings to a buffer.
     */
    void init(void);
}
