//
// Created by mrhowever on 04.04.2020.
//

#include "Uart.hh"

ISR(UART_RECEIVE_INTERRUPT)
{
    uint8_t tmpHead;
    uint8_t data;
    uint8_t usr;
    uint8_t lastRxError;
    
    // Read UART status register and UART data register
    usr = UART_STATUS;
    data = UART_DATA;

    // Get FEn (Frame Error) DORn (Data OverRun) UPEn (USART Parity Error) bits
    lastRxError = usr & ((1u << FE0) | (1u << DOR0) | (1u << UPE0));

    // Calculate buffer index
    tmpHead = (Uart::_rxHead + 1) & UART_RX_BUFFER_MASK;

    if (tmpHead == Uart::_rxTail) {
        lastRxError = UART_BUFFER_OVERFLOW >> 8u;    // Receive buffer overflow
    } else {
        Uart::_rxHead = tmpHead;                     // Store new index
        Uart::_rxBuf[tmpHead] = data;                // Store received data in buffer
    }

    Uart::_lastRxError |= lastRxError;
}

ISR(UART_TRANSMIT_INTERRUPT)
{
    uint8_t tmpTail;

    if (Uart::_txHead != Uart::_txTail) {
        tmpTail = (Uart::_txTail + 1) & UART_TX_BUFFER_MASK;    // Calculate and store new buffer index
        Uart::_txTail = tmpTail;
        UART_DATA = Uart::_txBuf[tmpTail];                      // Get one byte from buffer and write it to UART
    }
    else {
        UART_CONTROL &= ~(1u << UART_UDRIE);                    // Transmit buffer empty, disable UDRE interrupt
    }
}

Uart::Uart(uint32_t baudrate)
{
    Uart::_txHead = 0;
    Uart::_txTail = 0;
    Uart::_rxHead = 0;
    Uart::_rxTail = 0;

    // Set baud rate
    if (baudrate & 0x8000)
        UART_STATUS = (1u << UART_BIT_U2X);  //Enable 2x speed

    UART_UBRRH = (uint8_t) ((baudrate >> 8u) & 0x80u);
    UART_UBRRL = (uint8_t) (baudrate & 0x00FFu);

    // Enable USART receiver and transmitter and receive complete interrupt
    UART_CONTROL = (1u << UART_BIT_RXCIE) | (1u << UART_BIT_RXEN) | (1u << UART_BIT_TXEN);

    // Set frame format: asynchronous, 8data, no parity, 1stop bit
    UART_CONTROLC = (1u << UART_BIT_UCSZ1) | (1u << UART_BIT_UCSZ0);
}

uint16_t Uart::read()
{
    uint8_t tmpTail;
    uint8_t data;
    uint8_t lastRxError;

    if(Uart::_rxHead == Uart::_rxTail)
        return UART_NO_DATA;

    // Calculate buffer index
    tmpTail = (Uart::_rxTail + 1) & UART_RX_BUFFER_MASK;

    // Get data from receive buffer
    data = Uart::_rxBuf[tmpTail];
    lastRxError = Uart::_lastRxError;

    // Update buffer index
    Uart::_rxTail = tmpTail;
    Uart::_lastRxError = 0;

    return (lastRxError << 8u) + data;
}

void Uart::write(uint8_t data)
{
    uint8_t tmpHead;

    // Calculate buffer index
    tmpHead  = (Uart::_txHead + 1) & UART_TX_BUFFER_MASK;

    // If transmit buffer is full, wait for a byte to be sent
    while (tmpHead == Uart::_txTail);

    // Send data to transmit buffer
    Uart::_txBuf[tmpHead] = data;
    Uart::_txHead = tmpHead;

    /* enable UDRE interrupt */
    UART_CONTROL |= (1u << UART_UDRIE);
}

void Uart::write(const char *s)
{
    while(*s)
        write(*s++);
}