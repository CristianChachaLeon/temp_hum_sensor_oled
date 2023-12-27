#ifndef _I2C_H_
#define _I2C_H_

#undef PIO_UNIT_TESTING

#ifdef PIO_UNIT_TESTING
#include "hal_fake.h"
#else
#include "hal.h"
#endif

/// @brief init i2c driver, set freq 100k
/// @param
void i2c_init(void);
void i2c_stop(void);
uint8_t i2c_write_start(void);
uint8_t i2c_write_address(uint8_t address);
uint8_t i2c_write_byte(uint8_t data);
int8_t i2c_write(uint8_t address, uint8_t data);

int8_t i2c_write_data(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len);
int8_t i2c_address_receive(uint8_t address);
int8_t i2c_read_byte(uint8_t *data_register);

int8_t i2c_recv_byte(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data);
int8_t i2c_recv_data(uint8_t reg_addr, uint8_t *reg_data, uint32_t length);
int8_t i2c_repStart(void);

int8_t i2c_transmit(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);
#endif
