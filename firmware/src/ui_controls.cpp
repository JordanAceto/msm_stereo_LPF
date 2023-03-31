#include "BSP_ADC1.hpp"
#include "BSP_GPIO.hpp"
#include "LFO.hpp"
#include "MCP4822.hpp"
#include "ui_controls.hpp"

UI::UI() : sweep_mode_sw_1(BSP::gpio::pin_t::PA9, Debounced_Switch::ACTIVE_LOW, switch_debounce_count),
           sweep_mode_sw_2(BSP::gpio::pin_t::PA10, Debounced_Switch::ACTIVE_LOW, switch_debounce_count),
           invert_b_sw(BSP::gpio::pin_t::PC14, Debounced_Switch::ACTIVE_LOW, switch_debounce_count),
           fast_a_sw(BSP::gpio::pin_t::PC15, Debounced_Switch::ACTIVE_LOW, switch_debounce_count)
{
}

int UI::get_control_signal_val(analog_control_signal control_sig)
{
    int retval;

    switch (control_sig)
    {
    case LFO_A_FREQ:
        /* the frequency controls index into a 10 bit wide LUT, shift down to 10 bits */
        retval = BSP::adc1::getInput(BSP::adc1::PA0) >> 6;
        break;
    case LFO_B_FREQ:
        retval = BSP::adc1::getInput(BSP::adc1::PA3) >> 6;
        break;
    case LFO_A_SHAPE:
        retval = BSP::adc1::getInput(BSP::adc1::PA1);
        break;
    case LFO_B_SHAPE:
        retval = BSP::adc1::getInput(BSP::adc1::PA4);
        break;
    case LFO_A_LEVEL:
        retval = BSP::adc1::getInput(BSP::adc1::PA2);
        break;
    case LFO_B_LEVEL:
        retval = BSP::adc1::getInput(BSP::adc1::PB1);
        break;
    }

    return retval;
}

int UI::scale_bipolar_signal(int signal, int control)
{
    signal *= control;
    signal /= (BSP::adc1::FULL_SCALE + 1);

    return signal;
}

int UI::condition_bipolar_signal_for_DAC(int signal)
{
    // center the signal around FULL_SCALE/2
    signal += LFO::OUTPUT_MAX_VAL;

    // clamp the signal if it's out of bounds
    if (signal < 0)
    {
        signal = 0;
    }
    if (MCP4822::FULL_SCALE < signal)
    {
        signal = MCP4822::FULL_SCALE;
    }

    return signal;
}

UI::sweep_mode UI::get_sweep_mode()
{
    const Debounced_Switch::state_t sw1 = sweep_mode_sw_1.poll();
    const Debounced_Switch::state_t sw2 = sweep_mode_sw_2.poll();

    if (sw1 == Debounced_Switch::LOW && sw2 == Debounced_Switch::HIGH)
    {
        return sweep_mode::INDEPENDENT;
    }
    else if (sw1 == Debounced_Switch::LOW && sw2 == Debounced_Switch::LOW)
    {
        return sweep_mode::SYNC_TO_A;
    }
    else
    {
        return sweep_mode::ADD;
    }
}

UI::lfo_b_mode UI::get_lfo_b_mode()
{
    return invert_b_sw.poll() == Debounced_Switch::HIGH ? lfo_b_mode::NORMAL : lfo_b_mode::INVERT;
}

UI::lfo_a_mode UI::get_lfo_a_mode()
{
    return fast_a_sw.poll() == Debounced_Switch::HIGH ? lfo_a_mode::NORMAL : lfo_a_mode::FAST;
}
