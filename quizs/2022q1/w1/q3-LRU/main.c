#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


struct list_head {
    struct list_head *prev;
    struct list_head *next;
};

#define container_of(ptr, type, member)                            \
    __extension__({                                                \
        const __typeof__(((type *) 0)->member) *__pmember = (ptr); \
        (type *) ((char *) __pmember - offsetof(type, member));    \
    })

static inline void INIT_LIST_HEAD(struct list_head *head)
{
    head->next = head;
    head->prev = head;
}

static inline void list_add(struct list_head *node, struct list_head *head)
{
    struct list_head *next = head->next;

    next->prev = node;
    node->next = next;
    node->prev = head;
    head->next = node;
}

static inline void list_del(struct list_head *node)
{
    struct list_head *next = node->next;
    struct list_head *prev = node->prev;

    next->prev = prev;
    prev->next = next;
}

static inline void list_move(struct list_head *node, struct list_head *head)
{
    list_del(node);
    list_add(node, head);
}

#define list_entry(node, type, member) container_of(node, type, member)

#define list_last_entry(head, type, member) \
    list_entry((head)->prev, type, member)


#define list_for_each_entry(entry, head, member)                       \
    for (entry = list_entry((head)->next, __typeof__(*entry), member); \
         &entry->member != (head);                                     \
         entry = list_entry(entry->member.next, __typeof__(*entry), member))

#define list_for_each_entry_safe(entry, safe, head, member)                \
    for (entry = list_entry((head)->next, __typeof__(*entry), member),     \
        safe = list_entry(entry->member.next, __typeof__(*entry), member); \
         &entry->member != (head); entry = safe,                           \
        safe = list_entry(safe->member.next, __typeof__(*entry), member))



//
//
//



#define HASH(key, cache) ((key) % (cache->capacity))

typedef struct {
    int capacity, count;
    struct list_head dhead;  // 指向
    struct list_head hheads[];
} LRUCache;

typedef struct {
    int key, value;
    struct list_head dlink;
    struct list_head hlink;
} LRUNode;


LRUCache *lRUCacheCreate(int capacity)
{
    LRUCache *cache;

    // 利用 GNU C Extension 建立可變大小的 LRUCache 結構體物件
    // REF : https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html
    cache = malloc(sizeof(LRUCache) + capacity * sizeof(struct list_head));
    cache->capacity = capacity;
    cache->count = 0;

    // 初始化 dhead 以及雜湊表
    INIT_LIST_HEAD(&cache->dhead);
    for (int i = 0; i < capacity; ++i)
        INIT_LIST_HEAD(&cache->hheads[i]);
    return cache;
}


/**
 * @brief 從 LRU Cache 取得資料
 *
 * 透過 HASH(key) 計算出雜湊表的欄位索引
 * 接著到該欄位尋找目標的 key
 * 而不是走訪 dhead 中所有節點尋找 key
 *
 * @param cache
 * @param key
 * @return int
 */
int lRUCacheGet(LRUCache *cache, int key)
{
    LRUNode *node;
    // MMM2
    list_for_each_entry (node, &cache->hheads[HASH(key, cache)], hlink)
        if (node->key == key) {
            list_move(&node->dlink, &cache->dhead);
            return node->value;
        }
    return -1;
}


/**
 * @brief 新增一資料 (key,value) 到快取中
 *
 * TRICK :
 *  新增的資料並非放到原 LRU 節點所在的欄位
 *  實際上與雜湊表概念相同
 *  是將資料放在第 HASH(key) 個欄位
 *  而實際的 Cache 存取紀錄則是由 LRUCache 的 dhead 管理
 *  透過使用雜湊表 hhead 搭配「額外的」環狀雙向鏈結串列 dhead
 *
 *  - 新增資料：
 *      - 加入（資料不存在，Cache 未滿）：
 *          1. 計算 HASH(key) 並將資料加入雜湊表
 *          2. 將該節點加入到 dhead 串列
 *
 *      - 取代（資料不存在，Cache 已滿）：
 *          1. 將 LRU 從 hhead 中移除
 *          2. 將 LRU 從 dhead 中移除
 *          3. 計算 HASH(key) 並將新資料加到雜湊表
 *          4. 將新資料的節點加到 dhead 串列
 *
 *      - 更新（資料存在）：
 *          1. 從雜湊表中尋找該資料的節點
 *          2. 將該節點提昇至 dhead 首位（移除再加入）
 *
 *  - 取得資料：
 *      1. 從雜湊表中尋找該資料的節點
 *      2. 若有找到該資料則將該節點提昇至 dhead 首位
 *      3. 回傳節點
 *
 * @param cache LRUCache 物件的地址
 * @param key 欲新增資料的 key
 * @param value 欲新增資料的 value
 */
void lRUCachePut(LRUCache *cache, int key, int value)
{
    int hash = HASH(key, cache);
    LRUNode *node, *next;

    // MMM3, 只是 move 不需要使用到 safe
    list_for_each_entry (node, &cache->hheads[hash], hlink) {
        if (node->key == key) {
            // 更新該 key 的 value
            node->value = value;
            // 提昇至 dhead 首位
            list_move(&node->dlink, &cache->dhead);
            return;
        }
    }

    // 未滿，直接新增節點
    if (cache->count < cache->capacity) {
        node = malloc(sizeof(LRUNode));
        ++cache->count;
    }

    // 已滿，移除 dhead 中的 LRU
    else {
        // MMM4
        node = list_last_entry(&cache->dhead, LRUNode, dlink);
        list_del(&node->dlink);
        list_del(&node->hlink);
    }

    // 分別將資料加入到雜湊表以及 dhead
    node->key = key;
    node->value = value;
    list_add(&node->dlink, &cache->dhead);
    list_add(&node->hlink, &cache->hheads[hash]);
}


/**
 * @brief 清除 LRU Cache
 *
 * 雖然快取紀錄是由 dhead 管理
 * 但 LRUNode 同時包含 dlink 以及 hlink
 * 分別用來指向 dhead 及 hhead 的前後節點
 * 因此實際上 dhead 中的節點與 hhead 中的節點相同
 * 只須刪除一邊的節點即可
 *
 * @param cache
 */
void lRUCacheFree(LRUCache *cache)
{
    LRUNode *node, *next;
    // MMM 1
    list_for_each_entry_safe (node, next, &cache->dhead, dlink) {
        list_del(&node->dlink);
        free(node);
    }
    free(cache);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);

 * lRUCachePut(obj, key, value);

 * lRUCacheFree(obj);
*/

static inline void GET_AND_SHOW(LRUCache *cache, int key)
{
    int value = lRUCacheGet(cache, key);
    printf("GET (%d,%d)\n", key, value);
}

int main(int argc, char const *argv[])
{
    LRUCache *cache = lRUCacheCreate(2);

    lRUCachePut(cache, 1, 1);
    lRUCachePut(cache, 1, 1);

    GET_AND_SHOW(cache, 1);
    lRUCachePut(cache, 3, 3);
    GET_AND_SHOW(cache, 2);
    lRUCachePut(cache, 4, 4);
    GET_AND_SHOW(cache, 1);
    GET_AND_SHOW(cache, 3);
    GET_AND_SHOW(cache, 4);

    lRUCacheFree(cache);
    return 0;
}
