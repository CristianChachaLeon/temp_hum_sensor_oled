#include "bme280_wrapper.h"
BME280_INTF_RET_TYPE bme280_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len,
                                      void *intf_ptr)
{
    uint8_t dev_addr = *(uint8_t *)intf_ptr;

    return i2c_transmit(dev_addr, reg_addr, reg_data, len);
}