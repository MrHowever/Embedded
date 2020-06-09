//
// Created by mrhowever on 19.03.2020.
//

#ifndef RASPBERRYPI_HUMIDITY_H
#define RASPBERRYPI_HUMIDITY_H

#define ADC_CHANNEL 0u
#define INPUT_VOLTAGE 3.3
#define RESISTOR 10000u
#define BASE_TEMP 25u
#define TEMPERATURE_OFFSET_PER_ONE_DEGREE_C 400.0

double get_humidity();

#endif //RASPBERRYPI_HUMIDITY_H
