#include "hal.h"

void status_reg_write(uint8_t value)
{
    TWSR = value;
}
void baud_rate_reg_write(uint8_t value)
{
    TWBR = value;
}
void control_reg_write(uint8_t value)
{
    TWCR = value;
}
void data_reg_write(uint8_t value)
{
    TWDR = value;
}
uint8_t data_reg_read()
{
    return TWDR;
}
bool control_reg_int_is_set(void)
{
    return TWCR & (1 << TWINT);
}
uint8_t status_reg_read()
{
    return TWSR;
}

uint8_t baud_rate_reg_read(void)
{
    return TWBR;
}
uint8_t control_reg_read(void)
{
    return TWCR;
}