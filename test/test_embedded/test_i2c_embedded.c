#include <unity.h>
#include "i2c.h"

void setUp(void)
{
    // set stuff up here
    // control_reg_write(0);
    i2c_init();
}

void tearDown(void)
{
    // clean stuff up here
}

void test_init_i2c_freq_100k_embedded()
{
    i2c_init();
    TEST_ASSERT_EQUAL(status_reg_read() & 1, 0);
    TEST_ASSERT_EQUAL(baud_rate_reg_read(), 72);
}

void test_i2c_start_embedded()
{
    // printf("control_reg: %d\n", control_reg_read());
    TEST_ASSERT_EQUAL(control_reg_read() & 0xB4, 0);
    uint8_t res = i2c_write_start();
    TEST_ASSERT_EQUAL(control_reg_read() & 0xB4, 0xA4);
    TEST_ASSERT_EQUAL(res, 0);
    i2c_stop();
    //_delay_ms(1000);
}

void test_i2c_address_to_transmit_embedded()
{
    uint8_t address = 0x76;
    uint8_t res = 0;
    // TEST_ASSERT_EQUAL(control_reg_read() & 0xB4, 128);
    res = i2c_write_start();
    res = i2c_write_address(address);
    TEST_ASSERT_EQUAL(data_reg_read(), address << 1);
    TEST_ASSERT_EQUAL(control_reg_read() & 0xB4, 0x84);
    TEST_ASSERT_EQUAL(res, 0);
    i2c_stop();
}

void test_i2c_read_data_embedded()
{
    uint8_t dev_addr = 0x76;
    uint8_t res = 0;
    uint8_t reg_addr = 0xD0;
    uint8_t data = 0;
    res = i2c_write_start();
    TEST_ASSERT_EQUAL(res, 0);
    res = i2c_write_address(dev_addr);
    TEST_ASSERT_EQUAL(res, 0);
    res = i2c_write_byte(reg_addr);
    TEST_ASSERT_EQUAL(res, 0);
    res = i2c_repStart();
    TEST_ASSERT_EQUAL(res, 0);
    res = i2c_address_receive(dev_addr);
    TEST_ASSERT_EQUAL(res, 0);
    res = i2c_read_byte(&data);
    TEST_ASSERT_EQUAL(res, 0);
    TEST_ASSERT_EQUAL(data, 0x60);
    i2c_stop();
}
void test_i2c_receive_one_byte_embedded()
{
    uint8_t dev_addr = 0x76;
    uint8_t res = 0;
    uint8_t reg_addr = 0xD0;
    uint8_t data = 0;
    res = i2c_recv_byte(dev_addr, reg_addr, &data);
    TEST_ASSERT_EQUAL(res, 0);
    TEST_ASSERT_EQUAL(data, 0x60);
}

void test_i2c_receive_more_than_one_byte_embedded()
{

    uint8_t dev_addr = 0x76;
    uint8_t reg_addr = 0xE0;
    uint8_t res = 0;
    // uint8_t data[10] = 0;

    TEST_FAIL_MESSAGE("Fail read more than one byte");
}

void test_i2c_write_data_embedded()
{
    uint8_t dev_addr = 0x76;
    uint8_t reg_addr = 0xE0;
    uint8_t res = 0;
    uint8_t data = 0xB6;

    res = i2c_write_start();
    TEST_ASSERT_EQUAL(res, 0);
    res = i2c_write_address(dev_addr);
    TEST_ASSERT_EQUAL(res, 0);
    res = i2c_write_byte(reg_addr);
    TEST_ASSERT_EQUAL(res, 0);
    res = i2c_write_byte(data);
    TEST_ASSERT_EQUAL(res, 0);
    i2c_stop();
    // TEST_FAIL_MESSAGE("Fail write one byte");
}

void test_i2c_transmit_one_byte()
{
    uint8_t dev_addr = 0x76;
    uint8_t reg_addr = 0xE0;
    uint8_t res = 0;
    uint8_t data = 0xB6;
    res = i2c_transmit(dev_addr, reg_addr, &data, 1);
    TEST_ASSERT_EQUAL(res, 0);
}
int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_i2c_freq_100k_embedded);
    RUN_TEST(test_i2c_start_embedded);
    RUN_TEST(test_i2c_address_to_transmit_embedded);
    RUN_TEST(test_i2c_read_data_embedded);
    RUN_TEST(test_i2c_receive_one_byte_embedded);
    // RUN_TEST(test_i2c_receive_more_than_one_byte_embedded);
    RUN_TEST(test_i2c_write_data_embedded);
    RUN_TEST(test_i2c_transmit_one_byte);

    UNITY_END();
}