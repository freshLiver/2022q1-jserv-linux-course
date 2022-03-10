#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int32_t max(int32_t a, int32_t b)
{
    return a ^ ((a ^ b) & -(a < b));
}

static uint32_t rol32(uint32_t word, uint32_t shift)
{
    uint32_t neg_shift = -shift;
    return (word << (shift & 31)) | (word >> (neg_shift & 31));
}

int main(int argc, char const *argv[])
{
    int32_t a = 0xC0000000;
    int32_t b = 5;

    uint32_t res = rol32(a, b);
    return 0;
}
