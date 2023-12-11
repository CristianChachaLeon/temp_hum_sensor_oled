#include "hal.h"

void status_reg_write(uint8_t value)
{
    TWSR = value;
}
void baud_rate_reg_write(uint8_t value)
{
    TWBR = value;
}
