//
// Created by mrhowever on 04.04.2020.
//

#include <stdint.h>
#include <avr/io.h>
#include "adc.hh"

Adc::Adc()
{
    // Select reference voltage to AVref
    ADMUX |= (1u << REFS0);

    // Set prescaler to 128 and enable ADC
    ADCSRA |= (1u << ADPS2) | (1u << ADPS1) | (1u << ADPS0) | (1u << ADEN);
}

uint16_t Adc::getValue(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF0u) | (channel & 0x0Fu);    // Select ADC channel
    ADCSRA |= (1u << ADSC);                         // Single conversion mode
    while(ADCSRA & (1u << ADSC));                   // Wait until conversion is complete
    return ADC;
}

double Adc::toVolts(uint16_t value)
{
    return value * (V_REF / ADC_RANGE);
}
