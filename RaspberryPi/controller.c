//
// Created by mrhowever on 19.03.2020.
//

#include <stdlib.h>
#include "expander.h"
#include "LightSensor/light.h"

int init()
{
    if(wiringPiSetup() == -1) {
        printf("Init error");
        exit(1);
    }

    if(wiringPiSPISetup(0,4*1000*1000) == -1) {
        printf("Spi init failed");
        return 1;
    }

    mcp23017_init();
    tsl2581_init();

    return 0;
}
