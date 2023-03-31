#include "BSP_GPIO.hpp"
#include "debounced_switch.hpp"

Debounced_Switch::Debounced_Switch(
    BSP::gpio::pin_t pin_,
    polarity_t polarity_,
    int debounce_count_) : pin(pin_),
                           polarity(polarity_),
                           debounce_count(debounce_count_),
                           low_count(0),
                           high_count(0),
                           state(state_t::LOW)
{
}

Debounced_Switch::state_t Debounced_Switch::poll()
{
  // return BSP::gpio::getPinState(pin) ? Debounced_Switch::LOW : Debounced_Switch::HIGH;
  const bool active_level = polarity == polarity_t::ACTIVE_HIGH ? 1 : 0;

  const bool pin_state = BSP::gpio::getPinState(pin);

  if (pin_state == active_level)
  {
    this->high_count++;
    this->low_count = 0;
  }
  else
  {
    this->low_count++;
    this->high_count = 0;
  }

  if (high_count == debounce_count)
  {
    this->state = state_t::RISING;
  }
  else if (low_count == debounce_count)
  {
    this->state = state_t::FALLING;
  }
  else if (debounce_count < high_count)
  {
    this->state = state_t::HIGH;
  }
  else if (debounce_count < low_count)
  {
    this->state = state_t::LOW;
  }

  return this->state;
}
