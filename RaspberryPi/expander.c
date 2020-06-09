#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include "controller.h"
#include "expander.h"

void mcp23017_init()
{
    mcp23017_i2c_handle = wiringPiI2CSetup(MCP23017_ADDR);

    if(mcp23017_i2c_handle == -1) {
        printf("\nI2C setup failed for MCP23017.\n");
        exit(1);
    }
}

u_int8_t __set_nth_bit(u_int8_t bits, u_int8_t n, u_int8_t value)
{
    return (bits & ~(1UL << n)) | ((!!value) << n);
}

void mcp23017_write(unsigned int channel, u_int8_t state)
{
    u_int8_t register_addr;
    u_int8_t current_state;

    if(channel < 8) {
        register_addr = A_BLOCK_STATE_REG_ADDR;
    }
    else if(channel < 16) {
        register_addr = B_BLOCK_STATE_REG_ADDR;
        channel -= 8;
    }
    else {
        printf("\nInvalid expander channel\n");
        exit(1);
    }

    // Read current states of all A or B block I/O pins
    current_state = wiringPiI2CReadReg8(mcp23017_i2c_handle, register_addr);

    // Set nth bit to selected state
    current_state = set_nth_bit(current_state,channel,state);

    // Write updated states to register
    wiringPiI2CWriteReg8(mcp23017_i2c_handle,register_addr, current_state);
}

u_int8_t mcp23017_read(unsigned int channel)
{
    u_int8_t register_addr;

    if(channel < 8) {
        register_addr = A_BLOCK_STATE_REG_ADDR;
    }
    else if(channel < 16) {
        register_addr = B_BLOCK_STATE_REG_ADDR;
        channel -= 8;
    }
    else {
        printf("\nInvalid expander channel\n");
        exit(1);
    }

    // Read current modes of all A or B block I/O pins
    return (wiringPiI2CReadReg8(mcp23017_i2c_handle, register_addr) >> channel) & 1UL;
}

void mcp23017_set_channel_mode(unsigned int channel, u_int8_t mode)
{
    u_int8_t register_addr;
    u_int8_t current_state;
    
    if(channel < 8) {
        register_addr = A_BLOCK_MODE_REG_ADDR;
    }
    else if(channel < 16) {
        register_addr = B_BLOCK_MODE_REG_ADDR;
        channel -= 8;
    }
    else {
        printf("\nInvalid expander channel\n");
        exit(1);
    }

    // Read current modes of all A or B block I/O pins
    current_state = wiringPiI2CReadReg8(mcp23017_i2c_handle, register_addr);

    // Set nth bit to mode, where mode = 0 = 0 and mode != 0 = 1, which sets mode for channel (0 write, 1 read)
    current_state = set_nth_bit(current_state,channel,mode);

    // Write updated modes to register
    wiringPiI2CWriteReg8(mcp23017_i2c_handle,register_addr, current_state);
}
