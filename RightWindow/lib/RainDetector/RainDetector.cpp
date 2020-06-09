//
// Created by mrhowever on 06.04.2020.
//

#include "RainDetector.hh"
#include <math.h>

RainDetector::RainDetector(Adc& adc, uint8_t channel) : _adc(adc), _channel(channel), _threshold(RAIN_THRESHOLD) {}

double RainDetector::rainIntensity()
{
    double rainIntensity = Adc::toVolts(_adc.getValue(_channel));
    double scaledIntensity = rainIntensity - VOLTAGE_SCALE;
    return round(100.0 - ((scaledIntensity / MIN_OUT_VOLTAGE) * 100.0));
}

bool RainDetector::isRaining()
{
    return rainIntensity() > _threshold;
}

void RainDetector::setRainThreshold(uint8_t threshold)
{
    _threshold = threshold;
}
