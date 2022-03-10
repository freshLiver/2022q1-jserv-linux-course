#include <stdio.h>
#include <stdlib.h>
#define swap(a, b) \
        do { typeof(a) __tmp = (a); (a) = (b); (b) = __tmp; } while (0)

unsigned long gcd(unsigned long a, unsigned long b)
{
    unsigned long r = a | b;

    if (!a || !b)
        return r;

    /* Isolate lsbit of r */
    r &= -r;

    while (!(b & r))
        b >>= 1;
    if (b == r)
        return r;

    for (;;) {
        while (!(a & r))
            a >>= 1;
        if (a == r)
            return r;
        if (a == b)
            return a;

        if (a < b)
            swap(a, b);
        a -= b;
    }
}

int main(int argc, char const *argv[])
{
    unsigned long res = gcd(atoi(argv[1]), atoi(argv[2]));
    printf("gcd(%s, %s) = %lu\n", argv[1], argv[2], res);
    return 0;
}
