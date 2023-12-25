#include "i2c.h"
#ifndef ARDUINO_AVR_UNO
#define F_CPU 16000000
#define TWINT 7
#define TWEN 2
#define TWSTA 5
#endif
uint8_t i2c_write_start(void);
uint8_t i2c_write_address(uint8_t address);
uint8_t i2c_write_byte(uint8_t data);
void i2c_stop(void);
void i2c_init()
{
    status_reg_write(0); // TW_SR = 0 => prescaler = 1
    baud_rate_reg_write((F_CPU / 100000UL - 16) / 2);
}

int8_t i2c_write(uint8_t address, uint8_t data)
{
    int8_t ret = -1;
    ret = i2c_write_start();
    if (ret != 0)
    {
        return -1; // error code i2c_start
    }
    ret = i2c_write_address(address);
    if (ret != 0)
    {
        return -2; // error code i2c_address
    }
    ret = i2c_write_byte(data);
    if (ret != 0)
    {
        return -3; // error code i2c_write byte
    }
    i2c_stop();
    return ret;
}

uint8_t i2c_write_start()
{
    uint8_t res = 0;
    control_reg_write((1 << TWINT) | (1 << TWSTA) | (1 << TWEN));
    while (!control_reg_int_is_set())
        ;

    if ((status_reg_read() & 0xF8) != TW_START)
    {
        res = -1;
    }
    return res;
}
int8_t i2c_address_receive(uint8_t address)
{
    int8_t res = 0;
    data_reg_write(address << 1 | 1);
    control_reg_write((1 << TWINT) | (1 << TWEN));
    while (!control_reg_int_is_set())
        ;
    if ((status_reg_read() & 0xF8) != TW_MR_SLA_ACK)
    {
        res = -1;
    }
    return res;
}

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

void i2c_stop(void)
{
    control_reg_write((1 << TWINT) | (1 << TWEN) | (1 << TWSTO));
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

int8_t i2c_read_byte(uint8_t *data_register)
{
    int8_t res = 0;
    while (!control_reg_int_is_set())
        ;
    *data_register = data_reg_read();
    if ((status_reg_read() & 0xF8) != TW_MR_DATA_ACK)
    {
        res = -1;
    }
    return res;
}

int8_t i2c_write_data(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len)
{
    int8_t res = 0;
    res = i2c_write_start();
    if (res == 0)
    {
        res = i2c_write_address(reg_addr);
    }
    if (res == 0)
    {
        for (uint8_t i = 0; i < len; i++)
        {
            res = i2c_write_byte(*reg_data++);
            if (res != 0)
            {
                break;
            }
        }
    }
    i2c_stop();
    return res;
}

int8_t i2c_recv_data(uint8_t reg_addr, uint8_t *reg_data, uint32_t length)
{
    int8_t res = 0;
    res = i2c_write_start();
    if (res == 0)
    {
        res = i2c_address_receive(reg_addr);
    }
    if (res == 0)
    {
        for (uint8_t i = 0; i < length; i++)
        {
            res = i2c_read_byte(*reg_data++);
            if (res != 0)
            {
                break;
            }
        }
    }
    return res;
}