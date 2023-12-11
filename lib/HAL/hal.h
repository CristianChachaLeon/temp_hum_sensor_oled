#ifndef _HAL_H_
#define _HAL_H_
#include <stdio.h>
#include <util/twi.h>
void status_reg_write(uint8_t value);
void baud_rate_reg_write(uint8_t value);
#endif