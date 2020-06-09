//
// Created by mrhowever on 21.04.2020.
//

#include "TemperatureSensor.hh"
#include "../DS18B20/ds18b20.h"
#include <avr/delay.h>

TemperatureSensor::TemperatureSensor(volatile uint8_t* dirReg, volatile uint8_t* port, volatile uint8_t* portIn, uint8_t pin) :
                                    _dirReg(dirReg),
                                    _port(port),
                                    _portIn(portIn),
                                    _pin(pin)
{

}

double TemperatureSensor::getTemperature()
{
    int16_t temp;

    // Tell the sensor to start reading the temperature
    ds18b20convert(_port,_dirReg,_portIn,(1u << _pin), nullptr);
    // Wait for the result
    _delay_ms(1000);
    // Read the result
    ds18b20read(_port,_dirReg,_portIn,(1u << _pin), nullptr, &temp);

    return temp / 1000.0;
}
