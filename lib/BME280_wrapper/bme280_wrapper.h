#ifndef _BME280_WRAPPER_H
#define _BME280_WRAPPER_H
#include "bme280.h"

BME280_INTF_RET_TYPE bme280_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len,
                                      void *intf_ptr);
#endif