#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ilog2(n) \
    (__builtin_constant_p(n) ? ((n) < 2 ? 0 : 63 - __builtin_clzll(n)) : fls(n))

static __always_inline int fls(unsigned int x)
{
    int r = 32;

    if (!x)
        return 0;
    if (!(x & 0xffff0000u)) {
        x <<= 16;
        r -= 16;
    }
    if (!(x & 0xff000000u)) {
        x <<= 8;
        r -= 8;
    }
    if (!(x & 0xf0000000u)) {
        x <<= 4;
        r -= 4;
    }
    if (!(x & 0xc0000000u)) {
        x <<= 2;
        r -= 2;
    }
    if (!(x & 0x80000000u)) {
        x <<= 1;
        r -= 1;
    }
    return r;
}

#define var_log2_is_const(var)                                           \
    ({                                                                   \
        bool _res = __builtin_constant_p(ilog2(var)) ? true : false;     \
        printf("%s(%d) \tis%sconst\n", #var, var, _res ? " " : " not "); \
    })


int main(int argc, char const *argv[])
{
    var_log2_is_const(156);

    int var1 = 343;
    var_log2_is_const(var1);

    const int var2 = 465;
    var_log2_is_const(var2);

    static int var3 = 546;
    var_log2_is_const(var3);

    int var4 = atoi(argv[1]);
    var_log2_is_const(var4);

    return 0;
}
