#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline bool is_divisible(uint32_t n, uint64_t M)
{
    return n * M <= M - 1;
}

static uint64_t M3 = UINT64_C(0xFFFFFFFFFFFFFFFF) / 3 + 1;
static uint64_t M5 = UINT64_C(0xFFFFFFFFFFFFFFFF) / 5 + 1;

int q7()
{
    for (size_t i = 1; i <= 100; i++) {
        uint8_t div3 = is_divisible(i, M3);
        uint8_t div5 = is_divisible(i, M5);
        unsigned int length = (2 << div3) << div5;

        char fmt[9];
        strncpy(fmt, &"FizzBuzz%u"[(9 >> div5) >> (div3 << 2)], length);
        fmt[length] = '\0';

        printf(fmt, i);
        printf("\n");
    }
    return 0;
}

char **fizzBuzz(int n, int *returnSize)
{
    *returnSize = n;
    char **res = (char **) malloc(n * sizeof(char *));

    for (int i = 0, num = 1; i < n; ++i, ++num) {
        bool div3 = is_divisible(num, M3), div5 = is_divisible(num, M5);

        int length = (2 << (div3 + div5));

        char fmt[9] = {0};
        strncpy(fmt, &"FizzBuzz%d"[(8 >> div5) >> (div3 << 2)], length);

        res[i] = calloc(10, sizeof(char));
        sprintf(res[i], fmt, num);
    }
    return res;
}

int main(int argc, char **argv)
{
    char **res = fizzBuzz(10);
    for (int i = 0; i < 100; ++i)
        printf("%d : %s", i, res[i]);
    return 0;
}