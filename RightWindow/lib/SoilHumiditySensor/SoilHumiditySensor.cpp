//
// Created by mrhowever on 06.04.2020.
//

#include <math.h>
#include "SoilHumiditySensor.hh"

SoilMoistureSensor::SoilMoistureSensor(Adc& adc, uint8_t channel) : _adc(adc), _channel(channel) {}

double SoilMoistureSensor::soilMoisture()
{
    double soilMoisture = Adc::toVolts(_adc.getValue(_channel));
    double scaledMoisture = soilMoisture * MOISTURE_SCALE;
    return round(scaledMoisture);
}

uint8_t SoilMoistureSensor::isMoist()
{
    double moisture = soilMoisture();

    if(moisture < 300) {
        return 0;           // Dry soil
    }
    else if(moisture < 700) {
        return 1;           // Humid soil
    }
    else {
        return 2;           // Water
    }
}
