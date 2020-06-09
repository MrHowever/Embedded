//
// Created by mrhowever on 06.04.2020.
//

#include "ReedContact.hh"

ReedContact::ReedContact(volatile uint8_t* port, volatile uint8_t* dataReg, uint8_t channel) :
                                                                        _port(port),
                                                                        _dataReg(dataReg),
                                                                        _channel(channel)
{
    *_port |= (1u << _channel);
}

bool ReedContact::isOn()
{
    return (*_dataReg >> _channel) & 1u;
}
