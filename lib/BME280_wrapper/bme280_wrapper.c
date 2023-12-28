#include "bme280_wrapper.h"

static uint8_t dev_addr;

BME280_INTF_RET_TYPE bme280_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len,
                                      void *intf_ptr)
{
    uint8_t dev_addr = *(uint8_t *)intf_ptr;

    return i2c_transmit(dev_addr, reg_addr, reg_data, len);
}

BME280_INTF_RET_TYPE bme280_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
    uint8_t dev_addr = *(uint8_t *)intf_ptr;
    return i2c_recv(dev_addr, reg_addr, reg_data, length);
}

int8_t get_temperature(uint32_t period, struct bme280_dev *dev)
{
    int8_t rslt = BME280_E_NULL_PTR;
    uint8_t status_reg;
    struct bme280_data comp_data;

    rslt = bme280_get_regs(BME280_REG_STATUS, &status_reg, 1, dev);

    if (status_reg & BME280_STATUS_MEAS_DONE)
    {
        /* Measurement time delay given to read sample */
        dev->delay_us(period, dev->intf_ptr);
        /* Read compensated data */
        rslt = bme280_get_sensor_data(BME280_TEMP, &comp_data, dev);

#ifndef BME280_DOUBLE_ENABLE
        comp_data.temperature = comp_data.temperature / 100;
#endif

#ifdef BME280_DOUBLE_ENABLE
        printf("Temperature:   %lf deg C\n", comp_data.temperature);
#else
        printf("Temperature:   %ld deg C\n", (long int)comp_data.temperature);
#endif
    }

    return rslt;
}

void bme280_delay_us(uint32_t period_us, void *intf_ptr)
{
    for (uint32_t i = 0; i < period_us; i++)
    {
        _delay_us(1);
    }
}

int8_t bme280_set_config_i2c(struct bme280_dev *dev)
{

    dev_addr = BME280_I2C_ADDR_PRIM;
    dev->intf_ptr = &dev_addr;
    dev->read = bme280_i2c_read; // funcion de i2c real ( ref)
    dev->write = bme280_i2c_write;
    dev->delay_us = bme280_delay_us;
    dev->intf = BME280_I2C_INTF;
    return 0;
}
