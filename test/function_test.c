#include <main.h>
#include <function.h>
#include <ctest.h>

CTEST(arithmetic_suite, income_second_if_dataFirst)
{
    const int income_test = 100;
    const int data_test = 10;
    const int result = calc(income_test, data_test);
    const float expected = 90;
    ASSERT_DBL_NEAR_TOL(expected, result, 1);
}
