#include <stdio.h>
#include <stdlib.h>

static inline __attribute__((const)) unsigned long __roundup_pow_of_two(
    unsigned long n)
{
    return 1UL << fls_long(n - 1);
}

#define roundup_pow_of_two(n)                                                  \
    (__builtin_constant_p(n) ? (((n) == 1) ? 1 : (1UL << (ilog2((n) -1) + 1))) \
                             : __roundup_pow_of_two(n))


int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
