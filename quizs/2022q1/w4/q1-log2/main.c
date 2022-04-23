#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ilog2(n)                                                       \
    (__builtin_constant_p(n) ? ((n) < 2 ? 0 : 63 - __builtin_clzll(n)) \
     : (sizeof(n) <= 4)      ? __ilog2_u32(n)                          \
                             : __ilog2_u64(n))

// 最高位元 1 在哪
// log of 2
float ceil_log2(uint32_t x)
{
    uint32_t r, shift;

    float result = -HUGE_VALF;
    uint32_t resultMask = (-!x) & (*(uint32_t *) &result);  // 0 if x != 0

    x -= !resultMask;  // 先減 1 最後就只要無條件進位

    // 檢查最高位 1 在第 16 個位元之後
    r = (x > 0xFFFF) << 4;  // 找到的話 r == 16
    x >>= r;                // 對半切, 結果 = 16

    // 檢查最高位 1 在第 8 個位元之後
    shift = (x > 0xFF) << 3;  // 找到的話 shift == 8
    x >>= shift;              // 對半切
    r |= shift;               // 結果 + 8

    // 檢查最高位 1 在第 4 個位元之後
    shift = (x > 0xF) << 2;  // 找到的話 shift = 4
    x >>= shift;             // 對半切
    r |= shift;              // 結果 + 4

    // 檢查最高位 1 在第 2 個位元之後
    shift = (x > 0x3) << 1;  // 找到的話 shift = 2
    x >>= shift;             // 對半切


    // 結果加 shift 並檢查最高位 1 是否在第 1 位元後
    //  x-1 的最高位 1 的位置 +1 (無條件進位)
    result = (r | shift | x > 1) + !resultMask;
    resultMask |= *(uint32_t *) &result;

    // check huge val
    return *(float *) &resultMask;
}

static inline int fls(unsigned int x)
{
    uint32_t r, shift, notZero = !!x;

    // 檢查最高位 1 在第 16 個位元之後
    r = (x > 0xFFFF) << 4;  // 找到的話 r == 16
    x >>= r;                // 對半切, 結果 + 16 or 00

    // 檢查最高位 1 在第 8 個位元之後
    shift = (x > 0xFF) << 3;  // 找到的話 shift == 8
    x >>= shift;              // 對半切
    r |= shift;               // 結果 + 8 or 0

    // 檢查最高位 1 在第 4 個位元之後
    shift = (x > 0xF) << 2;  // 找到的話 shift = 4
    x >>= shift;             // 對半切
    r |= shift;              // 結果 + 4 or 0

    // 檢查最高位 1 在第 2 個位元之後
    shift = (x > 0x3) << 1;  // 找到的話 shift = 2
    x >>= shift;             // 對半切
    r |= shift;              // 結果 + 2 or 0

    // 檢查最高位 1 在第 1 個位元之後
    shift = (x > 0x1) << 0;  // 找到的話 shift = 1
    x >>= shift;             // 對半切 (多餘)
    r |= shift;              // 結果 + 1 or 0

    return r + notZero;  //  x 的最高位 1 的位置 +1 (1-based)
}

int main(int argc, char const *argv[])
{
    float result = ceil_log2(atoi(argv[1]));
    printf("res = %f, is -HUGE_VAL = %d", result, result == -HUGE_VALF);
    return 0;
}
