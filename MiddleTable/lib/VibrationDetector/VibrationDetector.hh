//
// Created by mrhowever on 20.04.2020.
//

#ifndef RIGHTWINDOW_VIBRATIONDETECTOR_HH
#define RIGHTWINDOW_VIBRATIONDETECTOR_HH

#include <stdint.h>

class VibrationDetector {
    volatile uint8_t* _dirReg;
    volatile uint8_t* _port;
    uint8_t _pin;

public:
    VibrationDetector(volatile uint8_t*, volatile uint8_t*, uint8_t);
    bool vibrationsDetected();
};


#endif //RIGHTWINDOW_VIBRATIONDETECTOR_HH
