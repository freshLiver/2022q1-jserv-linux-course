#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t gcd64_loop(uint64_t u, uint64_t v)
{
    if (!u || !v)
        return u | v;

    int shift;
    for (shift = 0; !((u | v) & 1); shift++) {
        u /= 2, v /= 2;
    }
    while (!(u & 1))
        u /= 2;
    do {
        while (!(v & 1))
            v /= 2;
        if (u < v) {
            v -= u;
        } else {
            uint64_t t = u - v;
            u = v;
            v = t;
        }
    } while (v);
    return u << shift;
}

#define min(a, b) ((a) ^ (((a) ^ (b)) & -((a) > (b))));

uint64_t gcd64_ctz(uint64_t u, uint64_t v)
{
    if (!u || !v)
        return u | v;

    int utz = __builtin_ctzll(u);
    int vtz = __builtin_ctzll(v);
    u >>= utz;

    do {
        v >>= __builtin_ctzll(v);

        if (u < v) {
            v -= u;
        } else {
            uint64_t t = u - v;
            u = v;
            v = t;
        }
    } while (v);
    return u << min(utz, vtz);
}

int main(int argc, char const *argv[])
{
    uint64_t res;
    for (uint64_t a = S; a < E; ++a)
        for (uint64_t b = S; b < E; ++b)
            res = FUNC(a, b);
    return 0;
}