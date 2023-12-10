#include "i2c.h"
#ifndef ARDUINO_AVR_UNO
#define F_CPU 16000000
#define TWINT 7
#define TWEN 2
#define TWSTA 5
#endif

void i2c_init()
{
    status_reg_write(0); // TW_SR = 0 => prescaler = 1
    baud_rate_reg_write((F_CPU / 100000UL - 16) / 2);
}

int8_t i2c_write(uint8_t address, uint8_t data)
{
    int8_t ret = -1;

    // send start condition
    //*cr_address |= (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
    /*while (!(*cr_address & (1 << TWINT)))
        ;*/

    return ret;
}
