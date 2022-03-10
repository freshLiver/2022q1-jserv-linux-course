#include <stdint.h>

uint32_t average_div(uint32_t low, uint32_t high)
{
    return low + (high - low) / 2;
}

uint32_t average_bw1(uint32_t a, uint32_t b)
{
    return (a >> 1) + (b >> 1) + (a & b & 1);
}

uint32_t average_bw2(uint32_t a, uint32_t b)
{
    return (a & b) + ((a ^ b) >> 1);
}

int main(int argc, char const *argv[])
{
    uint32_t res;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            res = FUNC(i, j);
    return 0;
}
