#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
// #include "common/common.h"
//  #include "./examples/common/common.h"
#include "bme280.h"
#define LED_PIN PB5 // Assuming you're using the Arduino UNO board, where the built-in LED is connected to Pin 13 (PB5)
#include "i2c.h"
BME280_INTF_RET_TYPE bme280_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len,
                                      void *intf_ptr)
{
  uint8_t dev_addr = *(uint8_t *)intf_ptr;

  return i2c_transmit(dev_addr, reg_addr, reg_data, len);
}

BME280_INTF_RET_TYPE bme280_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
  uint8_t dev_addr = *(uint8_t *)intf_ptr;
  return i2c_recv_byte(dev_addr, reg_addr, reg_data);
}
void bme280_delay_us(uint32_t period_us, void *intf_ptr)
{
  for (uint32_t i = 0; i < period_us; i++)
  {
    _delay_us(1);
  }
}

int main(void)
{
  init_uart(115200);
  i2c_init();
  printf("Scanner I2C\n");
  int8_t rslt = 0;
  struct bme280_dev dev;
  static uint8_t dev_addr;
  dev_addr = BME280_I2C_ADDR_PRIM;
  dev.intf_ptr = &dev_addr;
  dev.read = bme280_i2c_read; // funcion de i2c real ( ref)
  dev.write = bme280_i2c_write;
  dev.delay_us = bme280_delay_us;
  dev.intf = BME280_I2C_INTF;

  rslt = bme280_init(&dev);
  
  printf("bme280 %d\n", dev.intf_rslt);
  //   bme280_error_codes_print_result("bme280_init", rslt);
  printf("result: %d\n", rslt);
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
