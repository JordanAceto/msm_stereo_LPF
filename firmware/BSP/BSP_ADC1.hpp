
#pragma once

#include <stdint.h>

/** @brief onboard STM32 analog to digital converter */
namespace BSP::adc1
{
    /** @brief the number of bits in the ADC conversions */
    const int NUM_BITS = 16;

    /** @brief the maximum value of the signals converted by the ADC */
    const int FULL_SCALE = (1 << NUM_BITS) - 1;

    /** @brief enumeration of the ADC input channels.
     * The order of the channels is based on the PCB layout.
     * */
    enum pin_t
    {
        PB1,
        PA0,
        PA1,

        PA2,
        PA3,
        PA4,

        NUM_INPUTS
    };

    /**
     * @brief Initialize the ADC.
     *
     * The ADC reads the signals continuously and stores the values via DMA.
     * Oversampling is configured to create 16 bit conversions.
     */
    void init(void);

    /**
     * @brief Get the specified input channel.
     *
     * ADC conversions are 16 bits wide.
     *
     * @param input the input channel to get
     * @return uint16_t the converted analog value of the specified channel
     */
    uint16_t getInput(pin_t input_type);

    /**
     * @brief Get a pointer to the raw input buffer, used only by the DMA controller.
     *
     * @return uint32_t* pointer to the buffer holding the analog conversions.
     */
    uint32_t *getPtrToRawInputArray(void);
}
