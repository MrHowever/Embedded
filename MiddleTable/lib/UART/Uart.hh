//
// Created by mrhowever on 04.04.2020.
//

#ifndef RIGHTWINDOW_UART_HH
#define RIGHTWINDOW_UART_HH

#include <stdint.h>
#include <avr/interrupt.h>

#define SYSTEM_CLK 16000000UL
#define UART_RX_BUFFER_SIZE 32u
#define UART_TX_BUFFER_SIZE 32u

/* size of RX/TX buffers */
#define UART_RX_BUFFER_MASK (UART_RX_BUFFER_SIZE - 1)
#define UART_TX_BUFFER_MASK (UART_TX_BUFFER_SIZE - 1)

#define UART_RECEIVE_INTERRUPT   USART_RX_vect
#define UART_TRANSMIT_INTERRUPT  USART_UDRE_vect

#define UART_STATUS      UCSR0A
#define UART_CONTROL     UCSR0B
#define UART_CONTROLC    UCSR0C
#define UART_DATA        UDR0
#define UART_UDRIE       UDRIE0
#define UART_UBRRL       UBRR0L
#define UART_UBRRH       UBRR0H
#define UART_BIT_U2X     U2X0
#define UART_BIT_RXCIE   RXCIE0
#define UART_BIT_RXEN    RXEN0
#define UART_BIT_TXEN    TXEN0
#define UART_BIT_UCSZ0   UCSZ00
#define UART_BIT_UCSZ1   UCSZ01

#define UART_BUFFER_OVERFLOW  0x0200u              // Receive buffer overflow
#define UART_NO_DATA          0x0100u              // No data available

class Uart {
public:
    static volatile uint8_t _rxBuf[UART_RX_BUFFER_SIZE];
    static volatile uint8_t _txBuf[UART_TX_BUFFER_SIZE];
    static volatile uint8_t _rxHead, _rxTail;
    static volatile uint8_t _txHead, _txTail;
    static volatile uint8_t _lastRxError;

    Uart(uint32_t);
    uint16_t read();
    void write(uint8_t);
    void write(const char*);
};

ISR(UART_TRANSMIT_INTERRUPT);
ISR(UART_RECEIVE_INTERRUPT);

#endif //RIGHTWINDOW_UART_HH
