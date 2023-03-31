#pragma once

/** @brief Transform linear inputs into trapezoids */
namespace Trapezoid
{
    /** @brief the number of bits used by the trapezoid generator */
    const int NUM_BITS = 16;

    /** @brief the full scale max value for the trapezoid */
    const int MAX_VALUE = (1 << NUM_BITS) - 1;

    /** @brief the minimum value the trapezoid can take */
    const int MIN_VALUE = 0;

    /**
     * @brief Transform the linear input into a trapezoid.
     *
     * The linear input is converted to a trapezoid which clamps at a low value, then
     * rises towards a plateau. When the plateau is reached the signal flatlines at
     * the maximum value. When the input moves past the end of the plateau the output
     * falls towards the minimum value, and clamps at the min value when it is reached.
     *
     * The plateau is defined by a center and a width.
     *
     * @param input the input to transform
     * @param center the center of the trapezoid
     * @param width the width of the trapezoid plateau
     * @param slope the slope of the trapezoid when it is rising and falling
     * @return int the linear input transformed into a trapezoid in the range [MIN_VALUE, MAX_VALUE]
     */
    int process(int input, int center, int width, int slope);
}
