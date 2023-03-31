#pragma once

#include <stdint.h>

/**
 * @brief Pseudo Random Number Generator
 */
namespace PRNG
{
    /**
     * @brief Get the next pseudo random integer.
     *
     * @return uint32_t a pseudo random number
     */
    uint32_t nextRand(void);
}
