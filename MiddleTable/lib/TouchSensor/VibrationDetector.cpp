//
// Created by mrhowever on 20.04.2020.
//

#include "TouchSensor.hh"

TouchSensor::TouchSensor(volatile uint8_t* dirReg, volatile uint8_t* port, uint8_t pin) : _dirReg(dirReg),
                                                                                                          _port(port),
                                                                                                          _pin(pin)
{

}

bool TouchSensor::touchDetected()
{
    return (*_port >> _pin) & 1u;
}
