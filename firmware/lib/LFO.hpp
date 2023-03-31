#pragma once

#include <stdint.h>

/** @brief Low Frequency Oscillator */
class LFO
{
public:
    /** @brief the number of effective bits of output range used by the LFO */
    static const int OUTPUT_NUM_BITS = 12u;

    /** @brief the maximum value for the LFO outputs */
    static const int OUTPUT_MAX_VAL = ((1 << (OUTPUT_NUM_BITS - 1)) - 1);

    /** @brief the minimum value for the LFO outputs */
    static const int OUTPUT_MIN_VAL = -OUTPUT_MAX_VAL;

    /** @brief enumeration of the inputs used by the LFO */
    enum Input_t
    {
        FREQ_mHz,  // range: [1, sample_rate/2]
        WAVE_SCAN, // range: [0, 0xFFFF]

        NUM_LFO_INPUTS
    };

    /** @brief enumeration of the ouput waveshaped provided by the LFO */
    enum Shape_t
    {
        TRIANGLE,
        SINE,
        SQUARE,
        RANDOM,
        CROSSFADED,

        NUM_LFO_SHAPES
    };

    /**
     * @brief Construct a new LFO object
     *
     * @param sample_rate the sample rate for the LFO, in Hertz
     */
    LFO(uint32_t sample_rate_);

    /**
     * @brief Tick the LFO.
     *
     * This function must be called at the frequency held by the sample rate.
     */
    void tick(void);

    /**
     * @brief Set the given input.
     *
     * @param input_type the input type to set
     * @param value the value to set the input to
     */
    void setInput(Input_t input_type, int value);

    /**
     * @brief Get the specified ouput wave.
     *
     * @param output the output waveshape to get
     * @return int the current sample of the specified output wave
     */
    int getOutput(Shape_t output);

private:
    /** @brief array of LFO inputs */
    int input[NUM_LFO_INPUTS];

    /** @brief array of LFO output waveshapes */
    int output[NUM_LFO_SHAPES];

    /** @brief the phase accumulator, LFO is generated via DDS */
    uint32_t phase_accumulator;

    /** @brief used in generating the random sample-and-hold output */
    uint32_t last_double_time_accum;

    /** @brief the tuning word for the phase accumulator */
    uint32_t tuning_word;

    /** @brief the sample rate for the LFO */
    const uint32_t sample_rate;

    /** @brief the width of the phase accumulator */
    static const uint32_t ACCUMULATOR_BIT_WIDTH = 32u;

    /** @brief the number of index bits used, for indexing into lookup tables */
    static const uint32_t NUM_INDEX_BITS_IN_ACCUMULATOR = 10u;

    /** @brief the number of fractional bits, for linear interpolation */
    static const uint32_t NUM_FRACTIONAL_BITS_IN_ACCUMULATOR = ACCUMULATOR_BIT_WIDTH - NUM_INDEX_BITS_IN_ACCUMULATOR;

    /** @brief the full scale value of the phase accumulator */
    static const uint32_t ACCUMULATOR_FULL_SCALE = 0xFFFFFFFFu;

    /** @brief the half scale value of the phase accumulator */
    static const uint32_t ACCUMULATOR_HALF_SCALE = ACCUMULATOR_FULL_SCALE >> 1u;

    /** @brief the quarter scale value of the phase accumulator */
    static const uint32_t ACCUMULATOR_QUARTER_SCALE = ACCUMULATOR_HALF_SCALE >> 1u;

    /** @brief a mask for the fractional part of the phase accumulator */
    static const uint32_t ACCUMULATOR_FRACTION_MASK = ~((1u << NUM_FRACTIONAL_BITS_IN_ACCUMULATOR) - 1u);

    /** @brief the size of the sine wave lookup table */
    static const uint32_t SINE_LOOKUP_TABLE_SIZE = 1u << NUM_INDEX_BITS_IN_ACCUMULATOR;

    /** @brief update the tuning word for the phase accumulator */
    void updateTuningWord(void);

    /** @brief update the current samples of the waveshapes of the LFO */
    void updateWaveshapes(void);
    void updateTriangle(void);
    void updateSine(void);
    void updateSquare(void);
    void updateRandom(void);
    void updateCrossfade(void);

    /**
     * @brief Perform linear interpolation.
     *
     * @param y1 the first value
     * @param y2 the second value
     * @param fraction the phase accumulator fraction
     * @return int the linearly interpolated value between y1 and y2
     */
    static int linearInterpolation(int y1, int y2, uint32_t fraction);
};
