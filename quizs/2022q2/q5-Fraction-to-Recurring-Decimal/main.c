#include "list.h"

#define MAX_LEN 10000
#define TABLE_SIZE (1 << 10)

#define mod(dvd, dvs) ((dvd) % (dvs))
#define div(dvd, dvs) ((dvd) / (dvs))
#define HASH(key) mod(key, TABLE_SIZE)

struct rem_node {
    int key;
    int index;
    struct list_head link;
};

static inline int find(struct list_head *heads, int key)
{
    struct rem_node *entry;
    list_for_each_entry (entry, &heads[HASH(key)], link)
        if (entry->key == key)
            return entry->index;
    return -1;
}

static inline void add(struct list_head *heads, int key, int pos)
{
    // new node
    struct rem_node *node = malloc(sizeof(*node));
    node->key = key;
    node->index = pos;

    // add node
    list_add(&node->link, &heads[HASH(key)]);
}

static inline void delete_table(struct list_head *heads)
{
    for (int i = 0; i < TABLE_SIZE; ++i) {
        struct rem_node *entry, *next;
        list_for_each_entry_safe (entry, next, &heads[i], link) {
            list_del(&entry->link);
            free(entry);
        }
    }
}

char *fractionToDecimal(int numerator, int denominator)
{
    // init result string
    char *result = calloc(1, MAX_LEN + 1), *ptr = result;

    // 分母不應為 0
    if (!denominator)
        return result;

    // 分子也不應為 0（必須先檢查，不然可能會被加負號）
    if (!numerator) {
        *ptr++ = '0';
        return result;
    }


    // 檢查答案正負以及分子分母取絕對值
    int n_mask = (numerator >> 31), d_mask = (denominator >> 31);
    uint32_t n = (uint32_t)(n_mask ^ numerator) - n_mask;
    uint32_t d = (uint32_t)(d_mask ^ denominator) - d_mask;

    if (n_mask ^ d_mask)
        *ptr++ = '-';


    // 整數部份
    uint64_t rem = mod(n, d), quo = div(n, d);
    sprintf(ptr, "%lu", quo);

    // 是否整除
    if (!rem)
        return result;

    // 無法整除需要加小數點
    ptr = &result[strlen(result)];
    *ptr++ = '.';


    // 小數部份需要另外存以及雜湊表來處理循環部份
    int frac_len = MAX_LEN - (ptr - result) + 1;
    char *fraction = calloc(1, frac_len), *fptr = fraction;

    struct list_head heads[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; ++i)
        INIT_LIST_HEAD(&heads[i]);

    for (int i = 0; rem; ++i) {
        // 檢查是否循環（找得到重複餘數）
        int pos = find(heads, rem);
        if (~pos) {
            // 不循環部份
            fptr = fraction;
            while (pos-- > 0)
                *ptr++ = *fptr++;

            // 循環部份
            *ptr++ = '(';
            while (*fptr)
                *ptr++ = *fptr++;
            *ptr++ = ')';

            goto release;
        }

        // 無循環，新增到雜湊表
        add(heads, rem, i);

        // 新增商到 fraction 並重新檢查餘數
        *fptr++ = div(rem * 10, d) + '0';
        rem = mod(rem * 10, d);
    }
    strncpy(ptr, fraction, frac_len);

release:
    delete_table(heads);
    free(fraction);
    return result;
}

int main(int argc, char const *argv[])
{
    char *res = fractionToDecimal(atoi(argv[1]), atoi(argv[2]));
    printf("%s", res);
    free(res);
    return 0;
}
