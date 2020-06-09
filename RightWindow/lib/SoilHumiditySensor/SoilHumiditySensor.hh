//
// Created by mrhowever on 06.04.2020.
//

#ifndef RIGHTWINDOW_SOILHUMIDITYSENSOR_HH
#define RIGHTWINDOW_SOILHUMIDITYSENSOR_HH

#include <stdint.h>
#include <adc.hh>

#define MOISTURE_SCALE 10000.0

class SoilMoistureSensor {
    Adc& _adc;
    uint8_t _channel;
public:
    SoilMoistureSensor(Adc&,uint8_t);
    double soilMoisture();
    uint8_t isMoist();
};


#endif //RIGHTWINDOW_SOILHUMIDITYSENSOR_HH
