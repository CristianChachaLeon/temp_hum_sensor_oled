#ifndef _BME280_WRAPPER_H
#define _BME280_WRAPPER_H
#include "bme280.h"
#include "i2c.h"
#include <util/delay.h>

int8_t bme280_set_config_i2c(struct bme280_dev *dev);

BME280_INTF_RET_TYPE bme280_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len,
                                      void *intf_ptr);

BME280_INTF_RET_TYPE bme280_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr);

void bme280_delay_us(uint32_t period_us, void *intf_ptr);

int8_t get_temperature(uint32_t period, struct bme280_dev *dev);

int8_t get_humidity(uint32_t period, struct bme280_dev *dev);

void bme280_error_codes_print_result(const char api_name[], int8_t rslt);

void bme280_config_and_init(struct bme280_settings *settings, struct bme280_dev *dev, uint32_t *period);

#endif
