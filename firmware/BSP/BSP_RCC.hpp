
#pragma once

#include <stdint.h>

/** @brief Reset and Clock Controller */
namespace BSP::rcc
{
    /** @brief system clock speed, in Hertz */
    const uint32_t SYSTEM_CORE_CLOCK = 32000000u;

    /**
     * @brief Initialize the system clock.
     *
     * The clock is set to the specified SYSTEM_CORE_CLOCK speed using the
     * high speed internal clock and the PLL.
     */
    void init(void);
}
