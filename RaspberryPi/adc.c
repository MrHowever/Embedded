//
// Created by mrhowever on 19.03.2020.
//

#include "adc.h"
#include <stdio.h>

u_int8_t* read_channel(unsigned int channel)
{
    if(channel > 8) {
        printf("\nInvalid ADC channel\n");
        exit(1);
    }

    unsigned int request = channel | 0x18u;
    u_int8_t* buff = (u_int8_t*) malloc(sizeof(u_int8_t) * 3);
    buff[0] = request;
    buff[1] = 0;
    buff[2] = 0;

    wiringPiSPIDataRW(0,buff,3);

    return buff;
}