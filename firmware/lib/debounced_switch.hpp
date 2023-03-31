#pragma once

#include "BSP_GPIO.hpp"
#include "stm32l031xx.h"
#include <stdint.h>

class Debounced_Switch
{
public:
    enum state_t
    {
        RISING,
        FALLING,
        LOW,
        HIGH
    };

    enum polarity_t
    {
        ACTIVE_HIGH,
        ACTIVE_LOW
    };

    Debounced_Switch(
        BSP::gpio::pin_t pin_,
        polarity_t polarity_,
        int debounce_count_);

    state_t poll();

private:
    const BSP::gpio::pin_t pin;
    const polarity_t polarity;
    const int debounce_count;

    int low_count;
    int high_count;
    state_t state;
};
