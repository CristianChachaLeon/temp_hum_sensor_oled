#include "hal.h"

static uint8_t _twsr_reg;
static uint8_t _twbr_reg;

void status_reg_write(uint8_t value)
{
    TWSR = value;
}
void baud_rate_reg_write(uint8_t value)
{
    TWBR = value;
}

uint8_t status_reg_read()
{
    return TWSR;
}

uint8_t baud_rate_reg_read()
{
    return TWBR;
}