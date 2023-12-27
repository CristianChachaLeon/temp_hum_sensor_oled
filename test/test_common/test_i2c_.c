#include <unity.h>
#include "i2c.h"
void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_init_i2c_freq_100k()
{
    i2c_init();
    TEST_ASSERT_EQUAL(status_reg_read() & 1, 0);
    TEST_ASSERT_EQUAL(baud_rate_reg_read(), 72);
}

void test_i2c_start()
{
    status_reg_write(TW_START);
    uint8_t res = i2c_write_start();
    TEST_ASSERT_EQUAL(control_reg_read() & 0xA4, 0xA4);
    TEST_ASSERT_EQUAL(res, 0);
}

void test_i2c_address_to_transmit()
{
    status_reg_write(TW_MT_SLA_ACK);
    control_reg_write(0);
    uint8_t address = 1;
    uint8_t res = i2c_write_address(address);
    TEST_ASSERT_EQUAL(data_reg_read(), address << 1);
    TEST_ASSERT_EQUAL(control_reg_read() & 0xB4, 0x84);
    TEST_ASSERT_EQUAL(res, 0);
}

void test_i2c_write_data()
{
    status_reg_write(TW_MT_DATA_ACK);
    control_reg_write(0);
    uint8_t data = 55;
    uint8_t res = i2c_write_byte(data);
    TEST_ASSERT_EQUAL(data_reg_read(), data);
    TEST_ASSERT_EQUAL(control_reg_read() & 0xB4, 0x84);
    TEST_ASSERT_EQUAL(res, 0);
}
void test_i2c_stop()
{
    status_reg_write(0);
    control_reg_write(0);
    i2c_stop();
    TEST_ASSERT_EQUAL(control_reg_read() & 0xB4, 0);
}
void test_i2c_write_address_and_data()
{
    uint8_t data = 10;
    uint8_t address = 1;
    uint8_t dev_reg = 5;
    i2c_init();
    status_reg_write(TW_START);
    uint8_t res = i2c_write_start();
    TEST_ASSERT_EQUAL(res, 0);
    status_reg_write(TW_MT_SLA_ACK);
    res = i2c_write_address(address);
    TEST_ASSERT_EQUAL(res, 0);
    status_reg_write(TW_MT_DATA_ACK);
    res = i2c_write_byte(dev_reg);
    TEST_ASSERT_EQUAL(res, 0);
    status_reg_write(TW_MT_DATA_ACK);
    res = i2c_write_byte(data);
    i2c_stop();
    TEST_ASSERT_EQUAL(res, 0);
}
void test_i2c_write_multiple_data()
{
    uint8_t data[5] = {1, 2, 3, 4, 5};
    uint8_t address = 0x10;
    i2c_init();
    status_reg_write(TW_START);
    int8_t res = 0;
    // int8_t res = i2c_write_data(address, data, sizeof(data) / sizeof(data[0]));
    res = i2c_write_start();
    status_reg_write(TW_MT_SLA_ACK);
    if (res == 0)
    {
        res = i2c_write_address(address);
    }
    if (res == 0)
    {
        for (uint8_t i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        {
            status_reg_write(TW_MT_DATA_ACK);
            res = i2c_write_byte(data[i]);
            if (res != 0)
            {
                break;
            }
        }
    }
    i2c_stop();
    TEST_ASSERT_EQUAL(res, 0);
}
void test_i2c_address_to_read()
{
    int8_t res = 0;
    uint8_t address = 10;
    status_reg_write(TW_MR_SLA_ACK);
    control_reg_write(0);
    res = i2c_address_receive(address);
    TEST_ASSERT_EQUAL(data_reg_read(), address << 1 | 1);
    TEST_ASSERT_EQUAL(control_reg_read() & 0xB4, 0x84);
    TEST_ASSERT_EQUAL(res, 0);
}

void test_i2c_read_byte()
{
    int8_t res = 0;
    uint8_t data = 55;
    uint8_t data_readed;
    status_reg_write(TW_MR_DATA_ACK);
    data_reg_write(data);
    res = i2c_read_byte(&data_readed);
    TEST_ASSERT_EQUAL(data_readed, data);
    TEST_ASSERT_EQUAL(res, 0);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_i2c_freq_100k);
    RUN_TEST(test_i2c_start);
    RUN_TEST(test_i2c_address_to_transmit);
    RUN_TEST(test_i2c_write_data);
    RUN_TEST(test_i2c_stop);
    RUN_TEST(test_i2c_write_address_and_data);
    RUN_TEST(test_i2c_write_multiple_data);
    RUN_TEST(test_i2c_address_to_read);
    RUN_TEST(test_i2c_read_byte);

    UNITY_END();
}