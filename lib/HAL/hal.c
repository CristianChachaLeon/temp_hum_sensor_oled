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

bool control_reg_int_is_set(void)
{
    return TWCR & (1 << TWINT);
}
uint8_t status_reg_read()
{
    return TWSR;
}