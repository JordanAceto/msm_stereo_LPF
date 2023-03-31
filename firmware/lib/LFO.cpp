#include "LFO.hpp"
#include "lookup_tables.hpp"
#include "PRNG.hpp"
#include "wave_scanner.hpp"

LFO::LFO(uint32_t sample_rate_) : sample_rate(sample_rate_) {}

void LFO::tick(void)
{
    phase_accumulator += tuning_word;
    updateWaveshapes();
}

void LFO::setInput(Input_t input_type, int value)
{
    input[input_type] = value;

    if (input_type == FREQ_mHz)
    {
        updateTuningWord();
    }
}

int LFO::getOutput(Shape_t output_type)
{
    return output[output_type];
}

void LFO::updateTuningWord(void)
{
    /*
     * In DDS, the tuning word M = (2^N * f_out)/(f_c), where N is the number of
     * bits in the accumulator, f_out is the desired output frequency, and f_c
     * is the sample rate.
     *
     * Since the LFO frequency is measured in milli Hertz, this becomes
     * M = (2^N * f_out_mHz)/(f_c * 1000)
     *
     * Note that the ACCUMULATOR_FULL_SCALE value is actually equal to 2^N - 1,
     * but this off-by-one does not meaningfully impact the calculation.
     */
    const uint32_t two_to_the_N = ACCUMULATOR_FULL_SCALE;
    const uint32_t f_c = sample_rate;
    const uint32_t f_out_mHz = input[FREQ_mHz];
    const uint32_t mSec_per_sec = 1000u;

    const uint32_t M = (two_to_the_N / (f_c * mSec_per_sec)) * f_out_mHz;

    tuning_word = M;
}

void LFO::updateWaveshapes(void)
{
    updateTriangle();
    updateSine();
    updateSquare();
    updateRandom();
    updateCrossfade();
}

void LFO::updateSine(void)
{
    const uint32_t lut_idx = phase_accumulator >> NUM_FRACTIONAL_BITS_IN_ACCUMULATOR;
    const uint32_t next_idx = (lut_idx + 1u) % SINE_LOOKUP_TABLE_SIZE;
    const uint32_t fraction = phase_accumulator & ACCUMULATOR_FRACTION_MASK;

    output[SINE] = linearInterpolation(Lookup_Tables::SINE_LUT[lut_idx], Lookup_Tables::SINE_LUT[next_idx], fraction);
}

void LFO::updateTriangle(void)
{
    // keep the tri in phase with the sine
    const uint32_t phase_shifted_accum = phase_accumulator + ACCUMULATOR_QUARTER_SCALE;

    // derive the triangle directly from the phase accumulator
    if (phase_shifted_accum <= ACCUMULATOR_HALF_SCALE)
    {
        output[TRIANGLE] = (phase_shifted_accum >> (ACCUMULATOR_BIT_WIDTH - OUTPUT_NUM_BITS - 1u)) - OUTPUT_MAX_VAL;
    }
    else
    {
        output[TRIANGLE] = ((ACCUMULATOR_FULL_SCALE - phase_shifted_accum) >> (ACCUMULATOR_BIT_WIDTH - OUTPUT_NUM_BITS - 1u)) - OUTPUT_MAX_VAL;
    }
}

void LFO::updateSquare(void)
{
    output[SQUARE] = phase_accumulator < ACCUMULATOR_HALF_SCALE ? OUTPUT_MAX_VAL : OUTPUT_MIN_VAL;
}

void LFO::updateRandom(void)
{
    // the LFO "feels" better if the random signal updates at twice the base frequency
    const uint32_t double_time_accum = phase_accumulator << 1u;

    const bool accum_rolled_over = double_time_accum < last_double_time_accum;

    if (accum_rolled_over)
    {
        // get a random sample in the bounds of the LFO range, centered around zero
        const int random_sample = (PRNG::nextRand() & ((1 << OUTPUT_NUM_BITS) - 1)) - OUTPUT_MAX_VAL;
        output[RANDOM] = random_sample;
    }

    last_double_time_accum = double_time_accum;
}

void LFO::updateCrossfade(void)
{
    output[CROSSFADED] = Wave_Scanner::crossfade(output, NUM_LFO_SHAPES - 1, input[WAVE_SCAN]);
}

int LFO::linearInterpolation(int y1, int y2, uint32_t fraction)
{
    return y1 + (fraction * (y2 - y1)) / ACCUMULATOR_FRACTION_MASK;
}
