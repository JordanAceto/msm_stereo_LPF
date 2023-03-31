#pragma once

#include "debounced_switch.hpp"

class UI
{
public:
    UI();

    /** @brief enumeration of the analog input channels */
    enum analog_control_signal
    {
        LFO_A_LEVEL,
        LFO_A_FREQ,
        LFO_A_SHAPE,

        LFO_B_LEVEL,
        LFO_B_FREQ,
        LFO_B_SHAPE
    };

    /**
     * @brief Get the value of the analog control signal
     *
     * @param sig the analog signal to get
     * @return int
     */
    int get_control_signal_val(analog_control_signal control_sig);

    /**
     * @brief scale the given signal by the control value
     *
     * @param signal the signal to scale
     * @param control the control signal to scale the input with
     * @return uint
     */
    int scale_bipolar_signal(int signal, int control);

    /**
     * @brief clamp and center the given signal for the 12 bit DAC
     *
     * @param signal the signal
     * @return int
     */
    int condition_bipolar_signal_for_DAC(int signal);

    /**
     * The sweep mode switch has three position:
     * - UP position: the LFOs act independently
     * - MIDDLE position: both outputs sync to the value of LFO A
     * - DOWN position: both ouputs take the sum of (LFO A) + (LFO B)
     * */
    enum class sweep_mode
    {
        INDEPENDENT,
        SYNC_TO_A,
        ADD
    };

    /**
     * @brief poll the sweep mode switches and return the current
     * sweep mode based on the user settings.
     *
     * @return sweep_mode
     */
    sweep_mode get_sweep_mode();

    /**
     * @brief The rate A control has a push-pull switch
     *  - pushed DOWN: LFO A is in normal rate mode
     *  - pulled UP: LFO A is in fast rate mode
     */
    enum class lfo_a_mode
    {
        NORMAL,
        FAST
    };

    /**
     * @brief poll the lfo a normal/fast switch and return the current
     * lfo a mode based on the user settings
     *
     * @return lfo_a_mode
     */
    lfo_a_mode get_lfo_a_mode();

    /**
     * The invert B switch has two position:
     * - UP position: LFO B is not inverted
     * - DOWN position: LFO B is inverted
     */
    enum class lfo_b_mode
    {
        NORMAL,
        INVERT
    };

    /**
     * @brief poll the invert/normal lfo b switch and return the current
     * lfo b mode based on the user settings
     *
     * @return lfo_b_mode
     */
    lfo_b_mode get_lfo_b_mode();

private:
    Debounced_Switch sweep_mode_sw_1;
    Debounced_Switch sweep_mode_sw_2;
    Debounced_Switch invert_b_sw;
    Debounced_Switch fast_a_sw;

    /* the debounce count to use for the switches */
    static const int switch_debounce_count = 10u;
};
