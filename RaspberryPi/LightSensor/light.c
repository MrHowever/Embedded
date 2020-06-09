#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include "light.h"

int tsl2581_i2c_handler = 0;

void tsl2581_init()
{
    // Initialize the TSL2581 sensor
    tsl2581_i2c_handler = wiringPiI2CSetup(TSL2581_ADDR);

    __device_write(COMMAND_START | CONTROL, CONTROL_POWERON);                // Send PowerOn command
    delay(2000);                                                                   // Wait for power on
    __device_write(COMMAND_START | TIMING, INTEGRATION_TIME_400MS);          // Set integration time
    __device_write(COMMAND_START | CONTROL, ADC_EN | CONTROL_POWERON);  // Enable AD Converters
    __device_write(COMMAND_START | INTERRUPT, INTR_INTER_MODE);              // Test mode
    __device_write(COMMAND_START | ANALOG, GAIN_16X);                        // Set gain
}

// Write to one of the registers in TSL2581 sensor
void __device_write(uint8_t addr, uint8_t data)
{
  if(!fd) {
    printf("\nCannot write to uninitialized device.\n");
    exit(1);
  }
  
  wiringPiI2CWriteReg8(fd,addr,data);
}

// Read from one of the TSL2581 sensors
uint8_t __device_read(uint8_t addr)
{
  if(!fd) {
    printf("\nCannot read from uninitialized device.\n");
    exit(1);
  }
  
  return wiringPiI2CReadReg8(fd,addr);
}

// Read data from two ADC channels
void __read_adc(uint32_t* channel0, uint32_t* channel1)
{
  uint8_t data_low, data_high;

  // Read high and low byte for channel 0
  data_low = __device_read(COMMAND_START | TRANSACTION | DATA0LOW);
  data_high = __device_read(COMMAND_START | TRANSACTION | DATA0HIGH);
  *channel0 = 256 * data_high + data_low;

  // Read high and low byte for channel 1
  data_low = __device_read(COMMAND_START | TRANSACTION | DATA1LOW);
  data_high = __device_read(COMMAND_START | TRANSACTION | DATA1HIGH);
  *channel1 = 256 * data_high + data_low;
}

void __calculate_scaling(uint32_t* channel0_scale, uint32_t* channel1_scale, uint8_t gain, uint32_t integration_cycles)
{
    // Adjust the scale according to given integration cycles count
    if(integration_cycles == DEFAULT_INT_CYCLES)
        *channel0_scale = (1u << CH_SCALE);
    else
        *channel0_scale = (DEFAULT_INT_CYCLES << CH_SCALE) / integration_cycles;

    // Select the scale according to given gain
    switch(gain)
    {
        case 0:
            *channel1_scale = *channel0_scale;
            break;

        case 1:
            *channel0_scale = *channel0_scale >> 3u;
            *channel1_scale = *channel0_scale;
            break;

        case 2:
            *channel0_scale = *channel0_scale >> 4u;
            *channel1_scale = *channel0_scale;
            break;

        case 3:
            *channel1_scale = *channel0_scale / CH1GAIN128X;
            *channel0_scale = *channel0_scale / CH0GAIN128X;
            break;

        default:
            printf("\nInvalid Gain parameter\n");
            exit(1);
    }
}

// Calculate the b and m factors from Channel1/Channel0 ratio
void __calculate_lux_factors(uint16_t* b, uint16_t* m, uint32_t channel0, uint32_t channel1)
{
    uint32_t ratio_comp = 0;
    uint32_t ratio;

    if(channel0 != 0)
        ratio_comp = (channel1 << (RATIO_SCALE + 1u)) / channel0;

    ratio = (ratio_comp + 1u) >> 1u;

    if((ratio >= 0x00) && (ratio <= K1C)) {
        *b = B1C;
        *m = M1C;
    }
    else if(ratio <= K2C) {
        *b = B2C;
        *m = M2C;
    }
    else if(ratio <= K3C) {
        *b = B3C;
        *m = M3C;
    }
    else if(ratio <= K4C) {
        *b = B4C;
        *m = M4C;
    }
    else if(ratio <= K5C) {
        *b = B5C;
        *m = M5C;
    }
    else {
        printf("\nUnknown conversion error\n");
        exit(1);
    }
}

// Get current lux value
uint32_t get_lux(uint8_t gain, uint32_t integration_cycles)
{
  uint32_t channel0_scale;
  uint32_t channel1_scale;
  uint32_t channel0;
  uint32_t channel1;
  uint16_t b, m;

  // Calculate scaling for each channel
  __calculate_scaling(&channel0_scale, &channel1_scale, gain, integration_cycles);

  // Read data from both ADC channels
    __read_adc(&channel0, &channel1);

  // Scale the values
  channel0 = (channel0 * channel0_scale) >> CH_SCALE;
  channel1 = (channel1 * channel1_scale) >> CH_SCALE;

  // Calculate the b and m factors
  __calculate_lux_factors(&b,&m,channel0, channel1);

  // Calculate the lux value
  return ((channel0 * b) - (channel1 * m) + (1u << (LUX_SCALE - 1u))) >> LUX_SCALE;
}