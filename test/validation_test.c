#include <string.h>
#include <function.h>
#include <ctest.h>

CTEST(arithmetic_suite, income_second_if_dataFwasd)
{
    const int income_test = 100;
    const int data_test = 555;
    const int result = calc(income_test, data_test);
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}
