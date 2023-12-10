#ifndef _HAL_H_
#define _HAL_H_
#include <stdio.h>
#include <util/twi.h>
void status_reg_write(uint8_t value);
void baud_rate_reg_write(uint8_t value);
uint8_t status_reg_read(void);
uint8_t baud_rate_reg_read(void);
#endif