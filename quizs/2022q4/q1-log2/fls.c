#include <stdio.h>
#include <stdlib.h>

static int fls(unsigned int x)
{
    int r;
    asm("bsrl %1,%0" : "=r"(r) : "rm"(x), "0"(-1));
    return r + 1;
}

int main(int argc, char const *argv[])
{
    printf("fls(%s) = %d", argv[1], fls(atoi(argv[1])));
    return 0;
}
