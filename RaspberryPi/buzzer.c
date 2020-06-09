#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <math.h>
#include "expander.h"
#include "buzzer.h"

void buzzer_on()
{
    mcp23017_write(EXPANDER_CHANNEL, 1);
}

void buzzer_off()
{
    mcp23017_write(EXPANDER_CHANNEL, 0);
}

void buzzer_on_for(u_int32_t duration)
{
    mcp23017_write(EXPANDER_CHANNEL, 1);
    delay(duration);
    mcp23017_write(EXPANDER_CHANNEL, 0);
}

void buzzer_off_for(u_int32_t duration)
{
    mcp23017_write(EXPANDER_CHANNEL, 0);
    delay(duration);
    mcp23017_write(EXPANDER_CHANNEL, 1);
}