//
// Created by mrhowever on 06.04.2020.
//

#ifndef RIGHTWINDOW_REEDCONTACT_HH
#define RIGHTWINDOW_REEDCONTACT_HH


#include <stdint.h>

class ReedContact {
    volatile uint8_t* _port;
    volatile uint8_t* _dataReg;
    uint8_t _channel;
public:
    ReedContact(volatile uint8_t*, volatile uint8_t*,uint8_t);
    bool isOn();
};


#endif //RIGHTWINDOW_REEDCONTACT_HH
