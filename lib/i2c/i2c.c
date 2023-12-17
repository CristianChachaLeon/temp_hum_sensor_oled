#include "i2c.h"
#ifndef ARDUINO_AVR_UNO
#define F_CPU 16000000
#define TWINT 7
#define TWEN 2
#define TWSTA 5
#endif
uint8_t i2c_write_start(void);
uint8_t i2c_write_address(uint8_t address);
void i2c_init()
{
    status_reg_write(0); // TW_SR = 0 => prescaler = 1
    baud_rate_reg_write((F_CPU / 100000UL - 16) / 2);
}

int8_t i2c_write(uint8_t address, uint8_t data)
{
    int8_t ret = -1;

    // send start condition
    //*cr_address |= (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
    /*while (!(*cr_address & (1 << TWINT)))


        ;*/
    // i2c_write_start();
    // while (!control_reg_int_is_set());
    // load_slade_add(address);
    return ret;
}

uint8_t i2c_write_start()
{
    uint8_t res = 0;
    control_reg_write((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));
    while (!control_reg_int_is_set())
        ;

    if ((status_reg_read() & 0xF8) != 0x08)
    {
        res = -1;
    }
    return res;
}

/*void load_slade_add(uint8_t add){
    data_register_write();
}*/

uint8_t i2c_write_address(uint8_t address)
{
    uint8_t res = 0;
    data_reg_write(address << 1);
    control_reg_write((1 << TWINT) | (1 << TWEN));
    while (!control_reg_int_is_set())
        ;
    if ((status_reg_read() & 0xF8) != TW_MT_SLA_ACK)
    {
        res = -1;
    }
    return res;
}

uint8_t i2c_write_byte(uint8_t data)
{
    uint8_t res = 0;
    data_reg_write(data);
    control_reg_write((1 << TWINT) | (1 << TWEN));

    while (!control_reg_int_is_set())
        ;
    if ((status_reg_read() & 0xF8) != TW_MT_DATA_ACK)
    {
        res = -1;
    }
    return res;
}