//
// Created by mrhowever on 06.04.2020.
//

#include "HumiditySensor.hh"
#include <math.h>

HumiditySensor::HumiditySensor(Adc& adc, TemperatureSensor& temp, uint8_t channel) : _adc(adc), _temp(temp), _channel(channel) {}

double HumiditySensor::getHumidity()
{
    double sensorVoltage = Adc::toVolts(_adc.getValue(_channel));
    double temperature_delta = BASE_TEMP - _temp.getTemperature();
    double sensorResistance = ((sensorVoltage * RESISTOR) / (V_REF - sensorVoltage)) / 1000.0;

    // From equation y = e^(10.4504 - 0.1123*x) where y = Sensor resistance and x = Relative humidity, additional resistance offset from temperature characteristics
    return (log(sensorResistance + (TEMP_OFFSET_PER_DEGREE * temperature_delta)) - 10.4504) / -0.1123;
}

