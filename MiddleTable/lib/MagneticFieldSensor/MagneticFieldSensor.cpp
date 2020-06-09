//
// Created by mrhowever on 20.04.2020.
//

#include "MagneticFieldSensor.hh"

MagneticFieldSensor::MagneticFieldSensor(Adc& adc, uint8_t channel) : _adc(adc), _channel(channel)
{

}

double MagneticFieldSensor::magneticFieldLevel()
{
    double sensorVoltage = Adc::toVolts(_adc.getValue(_channel));
    return (sensorVoltage - 2.5f) / 0.015f;
}
