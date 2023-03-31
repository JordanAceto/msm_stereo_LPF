
#pragma once

/** @brief system initialization */
namespace BSP::system_init
{
    /**
     * @brief Initialize the STM32 peripherals.
     *
     * This function calls all of the various BSP init functions and puts
     * the system hardare in a state that is ready to execute the main
     * application.
     *
     * This function must be called before using any system peripherals.
     */
    void init(void);
}
