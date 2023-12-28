#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
#include "bme280_wrapper.h"
#define LED_PIN PB5 // Assuming you're using the Arduino UNO board, where the built-in LED is connected to Pin 13 (PB5)

int main(void)
{
  init_uart(115200);
  i2c_init();
  int8_t rslt = 0;
  uint32_t period;
  struct bme280_dev dev;
  struct bme280_settings settings;

  rslt = bme280_set_config_i2c(&dev);
  bme280_error_codes_print_result("bme280_set_config", rslt);

  rslt = bme280_init(&dev);
  bme280_error_codes_print_result("bme280_init", rslt);

  rslt = bme280_get_sensor_settings(&settings, &dev);
  bme280_error_codes_print_result("bme280_get_sensor_settings", rslt);

  /* Configuring the over-sampling rate, filter coefficient and standby time */
  /* Overwrite the desired settings */
  settings.filter = BME280_FILTER_COEFF_2;

  /* Over-sampling rate for humidity, temperature and pressure */
  settings.osr_h = BME280_OVERSAMPLING_1X;
  settings.osr_p = BME280_OVERSAMPLING_1X;
  settings.osr_t = BME280_OVERSAMPLING_1X;

  settings.standby_time = BME280_STANDBY_TIME_0_5_MS;
  rslt = bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, &settings, &dev);
  bme280_error_codes_print_result("bme280_set_sensor_settings", rslt);

  /* Always set the power mode after setting the configuration */
  rslt = bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, &dev);
  bme280_error_codes_print_result("bme280_set_power_mode", rslt);

  /* Calculate measurement time in microseconds */
  rslt = bme280_cal_meas_delay(&period, &settings);
  bme280_error_codes_print_result("bme280_cal_meas_delay", rslt);

  // printf("\nTemperature calculation (Data displayed are compensated values)\n");
  // printf("Measurement time : %lu us\n\n", (long unsigned int)period);

  while (1)
  {
    rslt = get_temperature(period, &dev);
    if (rslt != BME280_OK)
    {
      bme280_error_codes_print_result("get_temperature", rslt);
    }
    _delay_ms(1000);
  }

  return 0;
}
