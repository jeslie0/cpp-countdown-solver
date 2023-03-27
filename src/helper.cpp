#include "helper.hpp"

auto factorial(unsigned int n) -> unsigned int
{
    unsigned int result = 1;
    for (unsigned int j = 1; j <= n; j++)
    {
        result = result * j;
    }
    return result;
}
