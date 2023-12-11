#ifndef _HAL_H_
#define _HAL_H_

#include <stdint.h>
#define TWINT 7
#define TWSTA 5 
#define TWEN  2

void status_reg_write(uint8_t value);
void baud_rate_reg_write(uint8_t value);
void control_reg_write(uint8_t value);
uint8_t status_reg_read(void);
uint8_t baud_rate_reg_read(void);
uint8_t control_reg_read(void);

#endif