#pragma once

#include <cstddef>

/** @brief smoothly crossfade between an array of inputs */
namespace Wave_Scanner
{
    /** @brief  the maximum value for the crossfade control input */
    const int XFADE_MAX_VALUE = 0xFFFF;

    /**
     * @brief Smoothly crossfade between the waves in the input array.
     *
     * @param wave the array of inputs to crossfade between
     * @param num_waves the number of waves in the input to use, range: [2, wave.size - 1]
     * @param xfade the crossfade amount, small values favor waves early in the
     *              wave array, large values favor waves at the end of the array.
     *              range: [0, XFADE_MAX_VALUE]
     *
     * @return int the crossfaded result, will be a mix of two adjacent waves, or
     *         a single wave if the xfade parameter lands right in the middle of
     *         a wave
     */
    int crossfade(int *wave, int num_waves, int xfade);
}
