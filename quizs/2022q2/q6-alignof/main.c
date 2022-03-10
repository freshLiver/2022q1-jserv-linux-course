#include <stdint.h>
#include <stdio.h>

#define __ALIGN_KERNEL_MASK(x, mask) (((x) + (mask)) & ~(mask))
#define __ALIGN_KERNEL(x, a) __ALIGN_KERNEL_MASK(x, (typeof(x)) (a) -1)

#define ALIGN(x, a) __ALIGN_KERNEL((x), (a))
#define ALIGN_DOWN(x, a) __ALIGN_KERNEL((x) - ((a) -1), (a))
#define ALIGN_UP(x, align_to) (((x) + ((align_to) -1)) & ~((align_to) -1))

// clang-format off
#define ALIGNOF(t) ((char *)(&((struct { char c; t _h; } *)0)->_h) - (char *)0)
// clang-format on

typedef struct {
    int64_t b;
    int a;
} TEST;


int main(int argc, char const *argv[])
{
    printf("%ld\n", ALIGNOF(uint8_t));
    printf("%ld\n", ALIGNOF(uint16_t));
    printf("%ld\n", ALIGNOF(uint32_t));
    printf("%ld\n", ALIGNOF(uint64_t));
    printf("%ld\n", ALIGNOF(char));
    printf("%ld\n", ALIGNOF(TEST));
    return 0;
}
