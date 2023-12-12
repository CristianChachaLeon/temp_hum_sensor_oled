#ifndef _HAL_H_
#define _HAL_H_

#include <stdint.h>
#include <stdbool.h>
#define TWINT 7
#define TWSTA 5 
#define TWEN  2

#define MT_SLA_ACK   0x18
void status_reg_write(uint8_t value);
void baud_rate_reg_write(uint8_t value);
void control_reg_write(uint8_t value);
void data_reg_write(uint8_t value);

uint8_t status_reg_read(void);
uint8_t baud_rate_reg_read(void);
uint8_t control_reg_read(void);
uint8_t data_reg_read(void);

bool control_reg_int_is_set(void);

#endif