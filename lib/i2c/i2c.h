#ifndef _I2C_H_
#define _I2C_H_


#ifdef PIO_UNIT_TESTING
#include "hal_fake.h"
#else
#include "hal.h"
#endif

/// @brief init i2c driver, set freq 100k
/// @param
void i2c_init();

int8_t i2c_write(uint8_t address, uint8_t data);

#endif
