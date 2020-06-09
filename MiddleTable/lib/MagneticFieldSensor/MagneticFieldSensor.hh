//
// Created by mrhowever on 20.04.2020.
//

#ifndef RIGHTWINDOW_MAGNETICFIELDSENSOR_HH
#define RIGHTWINDOW_MAGNETICFIELDSENSOR_HH

#include <stdint.h>
#include "../ADC/adc.hh"

class MagneticFieldSensor {
    Adc& _adc;
    uint8_t _channel;

public:
    MagneticFieldSensor(Adc&, uint8_t);
    double magneticFieldLevel();
};


#endif //RIGHTWINDOW_MAGNETICFIELDSENSOR_HH
