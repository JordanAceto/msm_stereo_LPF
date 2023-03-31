#include "trapezoid.hpp"
#include "wave_scanner.hpp"
#include <stdint.h>

namespace Wave_Scanner
{
    int crossfade(int *wave, int num_waves, int xfade)
    {
        const int num_segments = (num_waves * 2) - 1;
        const int trap_width = Trapezoid::MAX_VALUE / num_segments;
        const int trap_slope = num_segments;

        int result = 0;

        for (int i = 0; i < num_waves; i++)
        {
            const int center_i = (trap_width / 2) + (i * trap_width * 2);

            const int wave_contrib = wave[i] * Trapezoid::process(xfade, center_i, trap_width, trap_slope) >> Trapezoid::NUM_BITS;
            result += wave_contrib;
        }

        return result;
    }
}
