#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
#include "bme280_wrapper.h"
#include "ssd1306.h"

int main(void)
{
  init_uart(115200);
  i2c_init();
  int32_t temp=0;
  char data_buffer[10];
  int8_t rslt = 0;
  uint32_t period;
  struct bme280_dev dev;
  struct bme280_settings settings;
  bme280_config_and_init(&settings, &dev, &period);
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
  
  printf("Display information: size %d x %d\n",ssd1306_displayWidth(),ssd1306_displayHeight());

  while (1)
  {
    temp++;
    rslt = get_temperature(period, &dev);
    //rslt = get_temperature(period, &dev,temp);
    //printf("data temp : %d\n",temp);
    bme280_error_codes_print_result("bme280_get_temperature", rslt);
    rslt = get_humidity(period, &dev);
    bme280_error_codes_print_result("bme280_get_humidity", rslt);
    snprintf(data_buffer , sizeof(data_buffer),"%ld",temp);
    ssd1306_printFixed(0,10, data_buffer, STYLE_NORMAL);
    _delay_ms(1000);
  }

  return 0;
}
