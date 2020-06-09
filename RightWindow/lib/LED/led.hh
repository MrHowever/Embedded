//
// Created by mrhowever on 04.04.2020.
//

#ifndef RIGHTWINDOW_LED_HH
#define RIGHTWINDOW_LED_HH

#define SHORT_BLINK_DUR 400
#define LONG_BLINK_DUR 2000

class Led
{
    volatile uint8_t* _dirReg;
    volatile uint8_t* _port;
    uint8_t _pin;

public:
    Led(volatile uint8_t*, volatile uint8_t*, uint8_t);

    void on();
    void off();
    void short_blink();
    void long_blink();
};

#endif //RIGHTWINDOW_LED_HH
