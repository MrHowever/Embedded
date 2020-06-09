//
// Created by mrhowever on 28.03.2020.
//

#include "uart.h"
#include "avr/io.h"
#include "util/delay.h"

#define UART_PORT PORTD
#define RX_PIN 1u
#define TX_PIN 2u

#define SET_HIGH(port,pin) port |= (1u << pin)
#define SET_LOW(port,pin) port &= ~(1u << pin)
#define SET(port,pin,value) port = (port & ~(1UL << pin)) | (value << pin)
#define TOGGLE(port,pin) port ^= (1u << pin);


int init()
{
    //TODO Set TX_PIN as output and RX_PIN as input here
    SET_HIGH(UART_PORT,TX_PIN);
}

void write(uint8_t data, uint32_t baud_rate)
{
    uint8_t i = 8;
    double bit_delay = 1000000.0 / baud_rate;   // Pause between pulses in us

    // Send start bit
    SET_LOW(UART_PORT,TX_PIN);  
    _delay_us(bit_delay);

    // Send data bit by bit
    for(; --i; data >>= 1u) {
        SET(UART_PORT,TX_PIN,data & 1u);
        _delay_us(bit_delay);
    }

    // Send stop bit
    SET_HIGH(UART_PORT,TX_PIN);
    _delay_us(2*bit_delay);
}