//
// Created by mrhowever on 06.04.2020.
//

#ifndef RIGHTWINDOW_HUMIDITYSENSOR_HH
#define RIGHTWINDOW_HUMIDITYSENSOR_HH

#include <stdint.h>
#include "adc.hh"
#include "../TemperatureSensor/TemperatureSensor.hh"

#define BASE_TEMP 25u
#define TEMP_OFFSET_PER_DEGREE 400.0
#define RESISTOR 10000u

class HumiditySensor {
    Adc& _adc;
    TemperatureSensor& _temp;
    uint8_t _channel;
public:
    HumiditySensor(Adc&,TemperatureSensor&,uint8_t);
    double getHumidity();
};


#endif //RIGHTWINDOW_HUMIDITYSENSOR_HH
