//
// Created by mrhowever on 20.04.2020.
//

#ifndef RIGHTWINDOW_TOUCHSENSOR_HH
#define RIGHTWINDOW_TOUCHSENSOR_HH

#include <stdint.h>

class TouchSensor {
    volatile uint8_t* _dirReg;
    volatile uint8_t* _port;
    uint8_t _pin;

public:
    TouchSensor(volatile uint8_t*, volatile uint8_t*, uint8_t);
    bool touchDetected();
};

#endif //RIGHTWINDOW_TOUCHSENSOR_HH
