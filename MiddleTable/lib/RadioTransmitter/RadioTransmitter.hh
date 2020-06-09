//
// Created by mrhowever on 21.04.2020.
//

#ifndef MIDDLETABLE_RADIOTRANSMITTER_HH
#define MIDDLETABLE_RADIOTRANSMITTER_HH

#include "VirtualWire.h"

#define RADIO_PIN 7
#define TRANSMISSION_SPEED 2000u

class RadioTransmitter {

public:
    RadioTransmitter();
    void send(uint8_t*,uint8_t);
};


#endif //MIDDLETABLE_RADIOTRANSMITTER_HH
