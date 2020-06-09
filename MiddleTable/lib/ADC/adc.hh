//
// Created by mrhowever on 04.04.2020.
//

#ifndef RIGHTWINDOW_ADC_HH
#define RIGHTWINDOW_ADC_HH

#define V_REF 5.0
#define ADC_RANGE 1024

class Adc
{
public:
    Adc();
    uint16_t getValue(uint8_t);
    static double toVolts(uint16_t);
};

#endif //RIGHTWINDOW_ADC_HH
