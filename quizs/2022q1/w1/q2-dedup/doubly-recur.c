#include "list.h"
struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct ListNode Node;

#define assign_and_cmp(ptr, next, p_ptr_entry, p_next_entry) \
    ({                                                       \
        p_ptr_entry = list_entry(ptr, element_t, list);      \
        p_next_entry = list_entry(next, element_t, list);    \
        p_ptr_entry->value == p_next_entry->value;           \
    })

struct list_head *q_delete_dup(struct list_head *head)
{
    if (!head)
        return NULL;

    element_t *ptr, *next;
    if (head->next && assign_and_cmp(head, head->next, ptr, next)) {
        while (head->next && assign_and_cmp(head, head->next, ptr, next))
            head = head->next;
        return q_delete_dup(head->next);
    }

    head->next = q_delete_dup(head->next);
    if (head->next)
        head->next->prev = head;
    return head;
}

struct ListNode *deleteDuplicates(struct ListNode *head)
{
    if (!head)
        return NULL;

    // build doubly-linked list
    struct list_head doubly;
    INIT_LIST_HEAD(&doubly);

    for (Node *ptr = head; ptr; ptr = ptr->next) {
        element_t *e = malloc(sizeof(element_t));
        e->value = ptr->val;
        e->list.next = NULL;

        list_add_tail(&e->list, &doubly);
    }

    // break circular
    doubly.prev->next = NULL;

    // head do not contain data, start from first node
    doubly.next = q_delete_dup(doubly.next);
    if (doubly.next)
        doubly.next->prev = &doubly;

    // make circular
    struct list_head *ptr;
    for (ptr = &doubly; ptr->next; ptr = ptr->next)
        ;
    ptr->next = &doubly;
    doubly.prev = ptr;

    // back to singly
    Node *new = NULL, **pnew = &new;

    list_for_each (ptr, &doubly) {
        element_t *entry = list_entry(ptr, element_t, list);
        Node *n = malloc(sizeof(Node));
        n->val = entry->value;
        n->next = NULL;

        *pnew = n;
        pnew = &(*pnew)->next;
    }

    return new;
}
