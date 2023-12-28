#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
// #include "common/common.h"
//  #include "./examples/common/common.h"
#include "bme280.h"
#define LED_PIN PB5 // Assuming you're using the Arduino UNO board, where the built-in LED is connected to Pin 13 (PB5)
#include "i2c.h"

#define SAMPLE_COUNT UINT8_C(50)

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
void bme280_delay_us(uint32_t period_us, void *intf_ptr)
{
  for (uint32_t i = 0; i < period_us; i++)
  {
    _delay_us(1);
  }
}

static int8_t get_temperature(uint32_t period, struct bme280_dev *dev)
{
  int8_t rslt = BME280_E_NULL_PTR;
  int8_t idx = 0;
  uint8_t status_reg;
  struct bme280_data comp_data;

  while (idx < 1)
  {
    rslt = bme280_get_regs(BME280_REG_STATUS, &status_reg, 1, dev);
    printf("bme280_get_regs %d\n", rslt);

    if (status_reg & BME280_STATUS_MEAS_DONE)
    {
      /* Measurement time delay given to read sample */
      dev->delay_us(period, dev->intf_ptr);
      /* Read compensated data */
      rslt = bme280_get_sensor_data(BME280_TEMP, &comp_data, dev);
      printf("bme280_get_sensor_data %d\n", rslt);

#ifndef BME280_DOUBLE_ENABLE
      comp_data.temperature = comp_data.temperature / 100;
#endif

#ifdef BME280_DOUBLE_ENABLE
      printf("Temperature[%d]:   %lf deg C\n", idx, comp_data.temperature);
#else
      printf("Temperature[%d]:   %ld deg C\n", idx, (long int)comp_data.temperature);
#endif
      idx++;
    }
  }

  return rslt;
}

int main(void)
{
  init_uart(115200);
  i2c_init();
  printf("Scanner I2C\n");
  int8_t rslt = 0;
  uint32_t period;
  struct bme280_dev dev;
  struct bme280_settings settings;

  static uint8_t dev_addr;
  dev_addr = BME280_I2C_ADDR_PRIM;
  dev.intf_ptr = &dev_addr;
  dev.read = bme280_i2c_read; // funcion de i2c real ( ref)
  dev.write = bme280_i2c_write;
  dev.delay_us = bme280_delay_us;
  dev.intf = BME280_I2C_INTF;

  rslt = bme280_init(&dev);
  printf("bme280_init %d\n", rslt);

  rslt = bme280_get_sensor_settings(&settings, &dev);
  printf("bme280_get_sensor_settings %d\n", rslt);

  /* Configuring the over-sampling rate, filter coefficient and standby time */
  /* Overwrite the desired settings */
  settings.filter = BME280_FILTER_COEFF_2;

  /* Over-sampling rate for humidity, temperature and pressure */
  settings.osr_h = BME280_OVERSAMPLING_1X;
  settings.osr_p = BME280_OVERSAMPLING_1X;
  settings.osr_t = BME280_OVERSAMPLING_1X;

  settings.standby_time = BME280_STANDBY_TIME_0_5_MS;
  rslt = bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, &settings, &dev);
  printf("bme280_set_sensor_settings %d\n", rslt);

  /* Always set the power mode after setting the configuration */
  rslt = bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, &dev);
  printf("bme280_set_power_mode %d\n", rslt);

  /* Calculate measurement time in microseconds */
  rslt = bme280_cal_meas_delay(&period, &settings);
  printf("bme280_cal_meas_delay %d\n", rslt);

  printf("\nTemperature calculation (Data displayed are compensated values)\n");
  printf("Measurement time : %lu us\n\n", (long unsigned int)period);

  rslt = get_temperature(period, &dev);
  printf("get_temperature %d\n", rslt);

  //   bme280_error_codes_print_result("bme280_init", rslt);
  //  Set the LED pin as an output
  DDRB |= (1 << LED_PIN);
  printf("init i2c module\n");
  uint8_t num_devices = 0;
  while (1)
  {
    // Toggle the LED
    PORTB ^= (1 << LED_PIN);
    printf("blink\n");
    for (size_t i = 0; i < 127; i++)
    {
      i2c_write_start();
      rslt = i2c_write_address(i);
      if (rslt == 0)
      {
        num_devices++;
        printf("Found device 0x%X\n", i);
      }
      i2c_stop();
    }

    // Delay for 1 second (adjust as needed)
    _delay_ms(1000);
  }

  return 0;
}
