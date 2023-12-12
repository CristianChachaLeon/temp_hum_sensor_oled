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
    status_reg_write(0x08);
    uint8_t res = i2c_write_start();
    TEST_ASSERT_EQUAL(control_reg_read()& 0xA4,0xA4);
    TEST_ASSERT_EQUAL(res,0);
}

void test_i2c_write_address(){
    status_reg_write(MT_SLA_ACK);
    uint8_t address= 1;
    uint8_t res = i2c_write_address(address);
    TEST_ASSERT_EQUAL(data_reg_read(),address<<1);
    TEST_ASSERT_EQUAL(control_reg_read() & 0xB4,0x84);
    TEST_ASSERT_EQUAL(res,0);
}
void test_i2c_write(){
    uint8_t data=10;
    uint8_t  address= 1;
    i2c_init();
    i2c_write(address,data);
    TEST_FAIL_MESSAGE("Fail");
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_i2c_freq_100k);
    RUN_TEST(test_i2c_start);
    RUN_TEST(test_i2c_write_address);
    RUN_TEST(test_i2c_write);

    UNITY_END();
}