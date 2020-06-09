//
// Created by mrhowever on 19.03.2020.
//

#ifndef RASPBERRYPI_EXPANDER_H
#define RASPBERRYPI_EXPANDER_H

#include <stdlib.h>

#define A_BLOCK_MODE_REG_ADDR 0x00u
#define B_BLOCK_MODE_REG_ADDR 0x00u
#define A_BLOCK_STATE_REG_ADDR 0x12
#define B_BLOCK_STATE_REG_ADDR 0x13

#define MCP23017_READ 1
#define MCP23017_WRITE 0

#define MCP23017_ADDR 0x20

int mcp23017_i2c_handle;

void mcp23017_init();

u_int8_t __set_nth_bit(u_int8_t, u_int8_t, u_int8_t);

void mcp23017_set_channel_mode(unsigned int, u_int8_t);
u_int8_t mcp23017_read(unsigned int);
void mcp23017_write(unsigned int, u_int8_t);

#endif //RASPBERRYPI_EXPANDER_H
