//
// Created by mrhowever on 04.04.2020.
//

#include <avr/io.h>
#include <util/delay.h>
#include "led.hh"

Led::Led(volatile uint8_t* port, volatile uint8_t* dirReg, uint8_t pin) : _dirReg(dirReg), _port(port), _pin(pin)
{
    (*_port) &= ~(1u << _pin);
    (*_dirReg) |= 1u << _pin;
}

void Led::on()
{
    (*_port) |= 1u << (_pin);
}

void Led::off()
{
    (*_port) &= ~(1u << _pin);
}

void Led::short_blink()
{
    on();
    _delay_ms(SHORT_BLINK_DUR);
    off();
    _delay_ms(SHORT_BLINK_DUR);
}

void Led::long_blink()
{
    on();
    _delay_ms(LONG_BLINK_DUR);
    off();
    _delay_ms(LONG_BLINK_DUR);
}