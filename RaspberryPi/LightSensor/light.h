//
// Created by mrhowever on 19.03.2020.
//

#ifndef RASPBERRYPI_LIGHT_H
#define RASPBERRYPI_LIGHT_H

#include <stdint.h>
#define COMMAND_START 0x80u
#define TRANSACTION   0X40u

// Register addresses

// Write registers
#define CONTROL   0x00u
#define TIMING    0x01u
#define INTERRUPT 0x02u
#define ANALOG    0X07u

// Read-only registers
#define DATA0LOW  0X14u
#define DATA0HIGH 0X15u
#define DATA1LOW  0X16u
#define DATA1HIGH 0X17u

// Transactions
#define ADC_EN          0X02u
#define CONTROL_POWERON 0X01u
#define INTR_INTER_MODE 0X18u

// Integration time
#define INTEGRATION_TIME_Manual 0x00u
#define INTEGRATION_TIME_2Z7MS  0xFFu
#define INTEGRATION_TIME_5Z7MS  0xFEu
#define INTEGRATION_TIME_51Z3MS 0XEDu
#define INTEGRATION_TIME_100MS  0XDBu
#define INTEGRATION_TIME_200MS  0XB6u
#define INTEGRATION_TIME_400MS  0X6Cu
#define INTEGRATION_TIME_688MS  0X01u

//Gains
#define GAIN_1X   0X00u
#define GAIN_8X   0X01u
#define GAIN_16X  0X02u
#define GAIN_111X 0X03u

//Scales
#define LUX_SCALE   16u
#define RATIO_SCALE 9u

#define CH_SCALE           16u // Scale channel values by 16
#define DEFAULT_INT_CYCLES 148u
#define CH0GAIN128X        107u  // 128x gain scalar for channel 0
#define CH1GAIN128X        115u  // 128x gain scalar for channel 1

#define K1C 0x009Au
#define B1C 0x2148u
#define M1C 0X3D71u
#define K2C 0x00c3u
#define B2C 0x2a37u
#define M2C 0x5b30u
#define K3C 0x00e6u
#define B3C 0x18efu
#define M3C 0x2db9u
#define K4C 0x0114u
#define B4C 0x0fdfu
#define M4C 0x199au
#define K5C 0x0114u
#define B5C 0x0000u
#define M5C 0x0000u

#define TSL2581_ADDR 0x39u

void tsl2581_init();

// R/W functions
void __device_write(uint8_t, uint8_t);   // Write data to TSL2581 sensor register
uint8_t __device_read(uint8_t);          // Read data from TSL2581 sensor register
void __read_adc(uint32_t*, uint32_t*);   // Read data from two A/D Converters of TSL2581 sensor

// Helper functions
void __calculate_scaling(uint32_t*, uint32_t*, uint8_t, uint32_t);       // Calculate scaling factors for each channel
void __calculate_lux_factors(uint16_t*, uint16_t*, uint32_t, uint32_t);  // Calculate the b and m factors from Channel1/Channel0 ratio

uint32_t get_lux(uint8_t, uint32_t);     // Get current lux value

#endif //RASPBERRYPI_LIGHT_H
