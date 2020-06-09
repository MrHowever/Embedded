//
// Created by mrhowever on 21.04.2020.
//

#include "RadioTransmitter.hh"
#include "VirtualWire.h"

RadioTransmitter::RadioTransmitter()
{
    vw_set_tx_pin(RADIO_PIN);
    vw_setup(TRANSMISSION_SPEED);
}

void RadioTransmitter::send(uint8_t* data, uint8_t length)
{
    vw_send(data,length);
    vw_wait_tx();
}