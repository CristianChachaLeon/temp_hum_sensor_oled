#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
#include "bme280_wrapper.h"

int main(void)
{
  init_uart(115200);
  i2c_init();
  int8_t rslt = 0;
  uint32_t period;
  struct bme280_dev dev;
  struct bme280_settings settings;
  bme280_config_and_init(&settings, &dev, &period);

  while (1)
  {
    rslt = get_temperature(period, &dev);
    bme280_error_codes_print_result("get_temperature", rslt);
    _delay_ms(1000);
  }

  return 0;
}
