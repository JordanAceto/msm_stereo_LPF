
#pragma once

#include <stdint.h>

/** @brief general purpose timer 2 */
namespace BSP::tim2
{
    /** @brief the frequency of the timer, in Hertz */
    const uint32_t FREQUENCY_Hz = 10000u;

    /**
     * @brief Initialize the timer.
     *
     * The timer is setup as a periodic stopwatch that rolls over at the
     * specified frequency.
     */
    void init(void);

    /**
     * @brief Check the rolling timer stopwatch.
     *
     * If a timer has occured, the timer update flag is reset and the timer
     * continues.
     *
     * This means that this function will return true ONLY ONCE per timer period,
     * you must save the result of this function if you want to check it more
     * than once in a given context.
     *
     * @return true if the timer has timed out
     * @return false otherwise
     */
    bool getTimeout(void);
}
