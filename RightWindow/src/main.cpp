#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../lib/ADC/adc.hh"
#include "../lib/RainDetector/RainDetector.hh"
#include "../lib/SoilHumiditySensor/SoilHumiditySensor.hh"
#include "../lib/ReedContact/ReedContact.hh"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include "../lib/Uart2/uart.h"

#define RAIN_DETECTOR_CHANNEL 5
#define MOISTURE_SENSOR_CHANNEL 4
#define LEFT_REED_CHANNEL 7
#define RIGHT_REED_CHANNEL 0

#define RAIN_DETECTOR_TOPIC "right_window/rain_detector"
#define MOISTURE_SENSOR_TOPIC "right_window/moisture_sensor"
#define REED_CONTACT_TOPIC "right_window/reed_contact"
#define ERROR_TOPIC "right_window/error"

#define UART_BAUD_RATE 9600

Adc adc;
RainDetector rainDetector(adc,RAIN_DETECTOR_CHANNEL);
SoilMoistureSensor moistureSensor(adc,MOISTURE_SENSOR_CHANNEL);

ReedContact leftReed(&PORTD,&DDRD,LEFT_REED_CHANNEL);
ReedContact rightReed(&PORTB,&DDRB,RIGHT_REED_CHANNEL);

void handleInput(uint8_t instruction)
{
  char buf[128];

  switch(instruction)
  {
    case '1':
      sprintf(buf, "%s|%d\n", RAIN_DETECTOR_TOPIC, rainDetector.rainIntensity());
      break;
      
    case '2':
      sprintf(buf, "%s|%d\n", RAIN_DETECTOR_TOPIC, rainDetector.isRaining());
      break;

    case '3':
      sprintf(buf, "%s|%d\n", MOISTURE_SENSOR_TOPIC, moistureSensor.soilMoisture());
      break;

    case '4':
      sprintf(buf, "%s|%d\n", MOISTURE_SENSOR_TOPIC, moistureSensor.isMoist());
      break;

    case '5':
      sprintf(buf, "%s|%d\n", REED_CONTACT_TOPIC, rightReed.isOn());
      break;

    case '6':
      sprintf(buf, "%s|%d\n", REED_CONTACT_TOPIC, leftReed.isOn());
      break;
           
    default:
      return;
   }

  uart_puts(buf);
}

enum ModuleControl : uint8_t { RAIN_DETECTOR = 0x00, MOISTURE_SENSOR = 0x01, LEFT_REED = 0x02, RIGHT_REED = 0x03};

void handleString(char* str, uint8_t length)
{
  uint32_t value = atoi(str);
  uint8_t instructionType = value >> 24u;
  uint8_t instructionMainType = (instructionType & 0xF0) >> 4u;
  uint8_t instructionSubType = instructionType & 0x0F;
  uint32_t instruction = value & 0x00FFFFFF;
  
  switch(instructionMainType)
  {
    case RAIN_DETECTOR:
      rainDetector.calibrate(instructionSubType, instruction);
      break;
    case MOISTURE_SENSOR:
      moistureSensor.calibrate(instructionSubType, instruction);
      break;
    case LEFT_REED:
      break;
    case RIGHT_REED:
      break;
    default:
      break;
  };
}

void invalidString()
{
  uart_puts_P("Invalid string input!");
}

int main()
{
  char c;
  char state;
  uint16_t data;
  bool stringMode = false;
  char stringBuf[32];
  uint8_t stringIdx = 0;

  DDRD |= (1u << PORTD6);
  PORTD &= ~(1u << PORTD6);
  
  uart_init(UART_BAUD_SELECT(UART_BAUD_RATE, F_CPU));
  sei();
  
  while(1) {
    data = uart_getc();
    c = data & 0x00FF;
    state = data & 0xFF00;
    
    if(data & UART_NO_DATA) {
    } else {
      if (state & UART_FRAME_ERROR) {
	uart_puts_P("UART Frame Error: ");
      }
      if (state & UART_OVERRUN_ERROR) {
	uart_puts_P("UART Overrun Error: ");
      }
      if (state & UART_BUFFER_OVERFLOW) {
	uart_puts_P("Buffer overflow error: ");
      } else {
	if(c == '/') {
	  stringMode = !stringMode;
	  
	  if(stringIdx) {
	    stringBuf[stringIdx] = '\0';
	    handleString(stringBuf, stringIdx);
	    stringIdx = 0;
	  }
	} else if(stringMode) {
	  if(stringIdx == 31) {
	    stringMode = false;
	    stringIdx = 0;
	    invalidString();
	  } else {
	    stringBuf[stringIdx++] = c;
	  }
	} else {
	  handleInput(c);
	}
      }
    }
  };
}
