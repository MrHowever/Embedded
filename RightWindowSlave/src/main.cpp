#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <util/twi.h>
#include <avr/interrupt.h>
//#include <Wire.h>

/* I2C clock in Hz */
#define SCL_CLOCK  100000L
#define I2C_ADDRESS 0x21

void led_on(uint8_t led)
{
    PORTD |= 1u << led;
}

void led_off(uint8_t led)
{
    PORTD &= ~(1u << led);
}

void blink_led_short(uint8_t led)
{
    led_on(led);
    _delay_ms(500);
    led_off(led);
    _delay_ms(500);
}

void I2C_init(uint8_t address)
{
    cli();
    // load address into TWI address register
    TWAR = address << 1;
    // set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
    TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
    sei();
}

void I2C_stop(void)
{
    // clear acknowledge and enable bits
    cli();
    TWCR = 0;
    TWAR = 0;
    sei();
}

volatile uint8_t data;

ISR(TWI_vect)
{
    switch(TW_STATUS)
    {
        case TW_SR_DATA_ACK:
            // received data from master, call the receive callback
            data = TWDR;
            TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
            if(data == 'X')
                blink_led_short(0);
            break;
        case TW_ST_SLA_ACK:
            // master is requesting data, call the request callback
            TWDR = data;
            TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
            break;
        case TW_ST_DATA_ACK:
            // master is requesting data, call the request callback
            TWDR = data;
            TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
            break;
        case TW_BUS_ERROR:
            // some sort of erroneous state, prepare TWI to be readdressed
            TWCR = 0;
            TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
            break;
        default:
            TWCR = (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN);
            break;
    }
}

//volatile int x = 0;
//
//void receiveEvent(int howMany)
//{
//    blink_led_short(0);
//    while(1 < Wire.available()) {
//        Wire.read();
//        x++;
//    }
//
//    Wire.read();
//    x++;
//}

int main()
{
    DDRD = 1u;
    DDRD |= 1u << 1;

    I2C_init(I2C_ADDRESS);

    while(1)
    {
        blink_led_short(1);
    };

//    Wire.begin(70);
//    Wire.onReceive(receiveEvent);
//
//    while(1) {
//        if(x) {
//            blink_led_short(0);
//            x--;
//        }
//
//        blink_led_short(1);
//    }
}
