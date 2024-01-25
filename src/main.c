#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
#include "bme280_wrapper.h"
#include "HMI_oled.h"

int main(void)
{
  int32_t temp=0;
  uint32_t humidity=0;
  int8_t rslt = 0;
  uint32_t period;
  struct bme280_dev dev;
  struct bme280_settings settings;
  
  init_uart(115200);
  i2c_init();
  
  bme280_config_and_init(&settings, &dev, &period);
  set_Font_oled(comic_sans_font24x32_123);
  init_oled();
  
  
  printf("Display information: size %d x %d\n",ssd1306_displayWidth(),ssd1306_displayHeight());

  while (1)
  {
    rslt = get_temperature(period, &dev,&temp);
    bme280_error_codes_print_result("bme280_get_temperature", rslt);

    rslt = get_humidity(period, &dev,&humidity);
    bme280_error_codes_print_result("bme280_get_humidity", rslt);

    show_temp_and_hum_oled(temp,humidity);
    _delay_ms(1000);
  }

  return 0;
}
