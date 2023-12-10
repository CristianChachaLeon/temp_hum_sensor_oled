#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
// #include "common/common.h"
//  #include "./examples/common/common.h"
// #include "bme280.h"
#define LED_PIN PB5 // Assuming you're using the Arduino UNO board, where the built-in LED is connected to Pin 13 (PB5)
#include "i2c.h"
int main(void)
{
  init_uart(115200);
  printf("uart for ATMEGA 328p -test bme280 lib\n");
  int8_t rslt = 0;
  // struct bme280_dev dev;
  //  dev.read = bme280_i2c_read; //funcion de i2c real ( ref)
  //  dev.write = bme280_i2c_write;
  //  dev.intf = BME280_I2C_INTF;
  //   rslt = bme280_interface_selection(&dev, BME280_I2C_INTF);
  //  rslt = bme280_init(&dev);
  //  bme280_error_codes_print_result("bme280_init", rslt);
  printf("%d\n", rslt);
  // Set the LED pin as an output
  DDRB |= (1 << LED_PIN);

  while (1)
  {
    // Toggle the LED
    PORTB ^= (1 << LED_PIN);

    // Delay for 1 second (adjust as needed)
    _delay_ms(500);
  }

  return 0;
}
