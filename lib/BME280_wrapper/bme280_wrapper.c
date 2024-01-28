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

int8_t get_temperature(uint32_t period, struct bme280_dev *dev,int32_t * temp)
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
        *temp = (long int)comp_data.temperature;
#endif
    }

    return rslt;
}

int8_t get_humidity(uint32_t period, struct bme280_dev *dev, uint32_t * humidity)
{
    int8_t rslt = BME280_E_NULL_PTR;
    uint8_t status_reg;
    struct bme280_data comp_data;
    rslt = bme280_get_regs(BME280_REG_STATUS, &status_reg, 1, dev);
    bme280_error_codes_print_result("bme280_get_regs", rslt);

    if (status_reg & BME280_STATUS_MEAS_DONE)
    {
        /* Measurement time delay given to read sample */
        dev->delay_us(period, dev->intf_ptr);

        /* Read compensated data */
        rslt = bme280_get_sensor_data(BME280_HUM, &comp_data, dev);
        bme280_error_codes_print_result("bme280_get_sensor_data", rslt);

#ifndef BME280_DOUBLE_ENABLE
        comp_data.humidity = comp_data.humidity / 1000;
#endif

#ifdef BME280_DOUBLE_ENABLE
        printf("Humidity:   %lf %%RH\n", comp_data.humidity);
#else
        printf("Humidity:   %lu %%RH\n", (long unsigned int)comp_data.humidity);
        *humidity =(long unsigned int)comp_data.humidity;

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

void bme280_error_codes_print_result(const char api_name[], int8_t rslt)
{
    if (rslt != BME280_OK)
    {
        printf("%s\t", api_name);

        switch (rslt)
        {
        case BME280_E_NULL_PTR:
            printf("Error [%d] : Null pointer error.", rslt);
            printf(
                "It occurs when the user tries to assign value (not address) to a pointer, which has been initialized to NULL.\r\n");
            break;

        case BME280_E_COMM_FAIL:
            printf("Error [%d] : Communication failure error.", rslt);
            printf(
                "It occurs due to read/write operation failure and also due to power failure during communication\r\n");
            break;

        case BME280_E_DEV_NOT_FOUND:
            printf("Error [%d] : Device not found error. It occurs when the device chip id is incorrectly read\r\n",
                   rslt);
            break;

        case BME280_E_INVALID_LEN:
            printf("Error [%d] : Invalid length error. It occurs when write is done with invalid length\r\n", rslt);
            break;

        default:
            printf("Error [%d] : Unknown error code\r\n", rslt);
            break;
        }
    }
}

void bme280_config_and_init(struct bme280_settings *settings, struct bme280_dev *dev, uint32_t *period)
{
    int8_t rslt = 0;
    rslt = bme280_set_config_i2c(dev);
    bme280_error_codes_print_result("bme280_set_config", rslt);

    rslt = bme280_init(dev);
    bme280_error_codes_print_result("bme280_init", rslt);

    rslt = bme280_get_sensor_settings(settings, dev);
    bme280_error_codes_print_result("bme280_get_sensor_settings", rslt);

    /* Configuring the over-sampling rate, filter coefficient and standby time */
    /* Overwrite the desired settings */
    settings->filter = BME280_FILTER_COEFF_2;

    /* Over-sampling rate for humidity, temperature and pressure */
    settings->osr_h = BME280_OVERSAMPLING_1X;
    settings->osr_p = BME280_OVERSAMPLING_1X;
    settings->osr_t = BME280_OVERSAMPLING_1X;

    settings->standby_time = BME280_STANDBY_TIME_0_5_MS;
    rslt = bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, settings, dev);
    bme280_error_codes_print_result("bme280_set_sensor_settings", rslt);

    /* Always set the power mode after setting the configuration */
    rslt = bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, dev);
    bme280_error_codes_print_result("bme280_set_power_mode", rslt);

    /* Calculate measurement time in microseconds */
    rslt = bme280_cal_meas_delay(period, settings);
    bme280_error_codes_print_result("bme280_cal_meas_delay", rslt);
}