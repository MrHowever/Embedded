//
// Created by mrhowever on 21.04.2020.
//

#ifndef MIDDLETABLE_TEMPERATURESENSOR_HH
#define MIDDLETABLE_TEMPERATURESENSOR_HH


#include <stdint.h>

class TemperatureSensor {
    volatile uint8_t* _dirReg;
    volatile uint8_t* _port;
    volatile uint8_t* _portIn;
    volatile uint8_t _pin;

public:
    TemperatureSensor(volatile uint8_t*,volatile uint8_t*,volatile uint8_t*,uint8_t);
    double getTemperature();
};


#endif //MIDDLETABLE_TEMPERATURESENSOR_HH
