#include <unity.h>
#define TESTING_ON
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
    TEST_ASSERT_EQUAL(baud_rate_reg_read(), 73);
}

/*void test_write_byte_i2c()
{
    uint8_t address = 1;
    uint8_t data = 10;
    int8_t res;
    res = i2c_write(address, data);
    TEST_ASSERT_EQUAL(res, 0);
}*/

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_init_i2c_freq_100k);
    // RUN_TEST(test_write_byte_i2c);

    UNITY_END();
}