#include "trapezoid.hpp"

namespace Trapezoid
{
    int process(int input, int center, int width, int slope)
    {
        const int plateau_start = center - (width / 2);
        const int plateau_end   = center + (width / 2);

        int output = 0;

        if (input < plateau_end) // it's either going up or it's in the plateau, clamping will fix overshoot
        {
            output = slope * (input - plateau_start) + MAX_VALUE;
        }
        else // it's descending back down after the end of the plateau
        {
            output = slope * (plateau_end - input) + MAX_VALUE;
        }

        // clamp the trapezoid between min and max values allowed
        if (output < MIN_VALUE)
        {
            output = MIN_VALUE;
        }
        if (MAX_VALUE < output)
        {
            output = MAX_VALUE;
        }

        return output;
    }
}
