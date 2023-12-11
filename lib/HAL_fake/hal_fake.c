#include "hal_fake.h"

static uint8_t _twsr_reg;
static uint8_t _twbr_reg;
static uint8_t _twsr_reg;

void status_reg_write(uint8_t value)
{
    _twsr_reg = value;
}
void baud_rate_reg_write(uint8_t value)
{
    _twbr_reg = value;
}

void control_reg_write(uint8_t value)
{
    _twsr_reg |=value;
}

uint8_t status_reg_read()
{
    return _twsr_reg;
}

uint8_t baud_rate_reg_read()
{
    return _twbr_reg;
}

uint8_t control_reg_read(void)
{
    return _twsr_reg;
}