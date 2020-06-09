#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "TouchSensor.hh"
#include "../lib/TemperatureSensor/TemperatureSensor.hh"
#include "../lib/MagneticFieldSensor/MagneticFieldSensor.hh"
#include "../lib/HumiditySensor/HumiditySensor.hh"
#include "../lib/RadioTransmitter/RadioTransmitter.hh"
#include "../lib/VibrationDetector/VibrationDetector.hh"

#define VIBRATION_DETECTOR_PIN 1
#define MAGNETIC_FIELD_SENSOR_CH 2
#define HUMIDITY_SENSOR_CH 3
#define TOUCH_SENSOR_PIN 0

Adc adc;
VibrationDetector vibrationDetector(&DDRB, &PORTB, VIBRATION_DETECTOR_PIN);
RadioTransmitter radioTransmitter;
TemperatureSensor temperatureSensor(&DDRD, &PORTD, &PIND, 2);
HumiditySensor humiditySensor(adc,temperatureSensor,HUMIDITY_SENSOR_CH);
MagneticFieldSensor magneticFieldSensor(adc, MAGNETIC_FIELD_SENSOR_CH);
TouchSensor touchSensor(&DDRB, &PORTB, TOUCH_SENSOR_PIN);

int main()
{
    const char* txt = "Elo\0";
    uint8_t xd = 5;

    pinMode(6,OUTPUT);

    vw_set_tx_pin(RADIO_PIN);
    vw_setup(TRANSMISSION_SPEED);

    while(1) {
    //    radioTransmitter.send((uint8_t*) txt, 4);
    vw_send(&xd,1);

    digitalWrite(6,HIGH);
    vw_wait_tx();
    digitalWrite(6,LOW);

    _delay_ms(100);
    };
}
