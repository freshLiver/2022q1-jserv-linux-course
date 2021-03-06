/* Memory cleanup for lock-free deletes
 *
 * Several data structures such as `hashmap_del` will remove data; however, it
 * may not be possible to free data until later. For example, if many threads
 * are using the same hashmap, more than one may be using a reference when
 * `hashmap_del` is called. The solution here is to have `hashmap_del` register
 * data that can be deleted later and let the application notify when worker
 * threads are done with old references.
 *
 * `free_later(void *var, void release(void *))` will register a pointer to have
 * the `release` method called on it later, when it is safe to free memory.
 *
 * `free_later_init()` must be called before using `free_later`, and
 * `free_later_exit()` should be called before application termination. It'll
 * ensure all registered vars have their `release()` callback invoked.
 *
 * `free_later_stage()` should be called before a round of work starts. It'll
 * stage all buffered values to a list that can't be updated, and make a new
 * list to register any new `free_later()` invocations. After all worker threads
 * have progressed with work, call `free_later_run()` to have every value in the
 * staged buffer released.
 */

#ifndef _FREE_LATER_H_
#define _FREE_LATER_H_

#ifdef BENCHMARK
#define THREAD_CONTENTION_MIN
#define VOLATILE_BM volatile
#define INC_ERROR_CNT(var) __atomic_fetch_add(var, 1, __ATOMIC_SEQ_CST)
#else
#define VOLATILE_BM
#define INC_ERROR_CNT(var) var += 1
#endif

#include <stdio.h>
#define dma_wrap(dma, ...)                                            \
    ({                                                                \
        void *_p = dma(__VA_ARGS__);                                  \
        if (!_p) {                                                    \
            printf("%s failed in %s:%d\n", #dma, __func__, __LINE__); \
            exit(1);                                                  \
        }                                                             \
        _p;                                                           \
    })

/* _init() must be called before use and _exit() once at the end */
int free_later_init(void);
int free_later_exit(void);

/* add a var to the cleanup later list */
void free_later(void *var, void release(void *var));
void free_later_run();

#endif