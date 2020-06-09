#include <stdint.h>
#include "../lib/ADC/adc.hh"
#include "../lib/RainDetector/RainDetector.hh"
#include "../lib/SoilHumiditySensor/SoilHumiditySensor.hh"
#include "../lib/ReedContact/ReedContact.hh"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Arduino.h>
#include "../lib/Uart2/uart.h"

#define RAIN_DETECTOR_CHANNEL 5
#define MOISTURE_SENSOR_CHANNEL 4
#define LEFT_REED_CHANNEL 7
#define RIGHT_REED_CHANNEL 0
#define SERIAL_BAUDRATE 9600

#define RAIN_DETECTOR_TOPIC "right_window/rain_detector"
#define MOISTURE_SENSOR_TOPIC "right_window/moisture_sensor"
#define REED_CONTACT_TOPIC "right_window/reed_contact"
#define ERROR_TOPIC "right_window/error"

Adc adc;
RainDetector rainDetector(adc,RAIN_DETECTOR_CHANNEL);
SoilMoistureSensor moistureSensor(adc,MOISTURE_SENSOR_CHANNEL);

ReedContact leftReed(&PORTD,&DDRD,LEFT_REED_CHANNEL);
ReedContact rightReed(&PORTB,&DDRB,RIGHT_REED_CHANNEL);

void send_message(const char* topic, const char* message)
{
    char query[128];
    strcpy(query,topic);
    strcat(strcat(strcat(query,"|"), message), "\n\0");

    String q(query);
    uart_puts(q.c_str());
}

void handleInput(const char* input)
{
    uint8_t instruction = strtol(input,nullptr,10);
    char* errMsg = "Invalid input: ";

    if(instruction >= 100 && instruction <= 200) {
        rainDetector.setRainThreshold(instruction - 100);
        return;
    }

    switch(instruction)
    {
        case 1:
            send_message(RAIN_DETECTOR_TOPIC, String(rainDetector.rainIntensity()).c_str());
            break;

        case 2:
            send_message(RAIN_DETECTOR_TOPIC, String(rainDetector.isRaining()).c_str());
            break;

        case 3:
            send_message(MOISTURE_SENSOR_TOPIC, String(moistureSensor.soilMoisture()).c_str());
            break;

        case 4:
            send_message(MOISTURE_SENSOR_TOPIC, String(moistureSensor.isMoist()).c_str());
            break;

        case 5:
            send_message(REED_CONTACT_TOPIC, String(rightReed.isOn()).c_str());
            break;

        case 6:
            send_message(REED_CONTACT_TOPIC, String(leftReed.isOn()).c_str());
            break;

        case 0:
        default:
            send_message(ERROR_TOPIC, String(strcat(errMsg,input)).c_str());
            break;
    }
}

void uart_read_s(char* buf)
{
    int i = 0;
    do {
        buf[i++] = (char) uart_getc();
    } while(buf[i-1] != '\0' && i < 20);
}

int main()
{
    uart_init(UART_BAUD_SELECT(SERIAL_BAUDRATE,F_CPU));
    sei();
    char buf[128];

    while(1) {
        uart_read_s(buf);

        if(strlen(buf) > 0) {
            handleInput(buf);
        }

        _delay_ms(100);
    };
}
