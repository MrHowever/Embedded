//
// Created by mrhowever on 06.04.2020.
//

#ifndef RIGHTWINDOW_RAINDETECTOR_HH
#define RIGHTWINDOW_RAINDETECTOR_HH

#include <stdint.h>
#include "adc.hh"

#define VOLTAGE_SCALE 0.7       // Voltage output at maximum (100%) rain intensity (or fully submerged in water)
#define MIN_OUT_VOLTAGE 4.3     // Voltage output at minimum (0%) rain intensity or fully dry sensor
#define RAIN_THRESHOLD 10u      // Default percentage of rain intensity at which it is considered a "rain"

class RainDetector {
    Adc& _adc;
    uint8_t _channel;
    uint8_t _threshold;
public:
    RainDetector(Adc&,uint8_t);
    double rainIntensity();
    bool isRaining();
    void setRainThreshold(uint8_t);
};


#endif //RIGHTWINDOW_RAINDETECTOR_HH
