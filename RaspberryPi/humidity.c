#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <math.h>
#include "humidity.h"
#include "adc.h"

double get_humidity()
{
    const u_int8_t* data = read_channel(ADC_CHANNEL);

    const unsigned int curr_temp = 25;                //TODO get from temperature.sh
    const double delta_temp = BASE_TEMP - curr_temp;

    unsigned int voltage_val = ((data[1] << 8u) | (data[2])) >> 4u;  // Digital value

    free(data);

    double voltage = (voltage_val / RANGE) * INPUT_VOLTAGE;                           // Analog value
    double resistance = ((voltage * RESISTOR) / (INPUT_VOLTAGE - voltage)) / 1000.0;  // From voltage divider

    // From equation y = e^(10.4504 - 0.1123*x) where y = Sensor resistance and x = Relative humidity, additional resistance offset from temperature characteristics
    return (log(resistance + (TEMPERATURE_OFFSET_PER_ONE_DEGREE_C * delta_temp)) - 10.4504) / -0.1123;
}
