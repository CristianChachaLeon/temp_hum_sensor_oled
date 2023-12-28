#ifndef _HAL_H_
#define _HAL_H_

#include <stdint.h>
#include <stdbool.h>
#define TWINT 7
#define TWSTA 5
#define TWEN 2
#define TWEA 6
#define TWSTO 4

#define TW_MT_SLA_ACK 0x18
#define TW_MT_DATA_ACK 0x28
#define TW_START 0x08
#define TW_MR_SLA_ACK 0x40
#define TW_MR_SLA_NACK 0x48
#define TW_MR_DATA_ACK 0x50
#define TW_REP_START 0x10
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