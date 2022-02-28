#include "list.h"
struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct ListNode Node;

bool q_delete_dup(struct list_head *head)
{
    if (!head)
        return false;

    LIST_HEAD(duplist);

    bool prev = false;
    element_t *ptr = list_entry(head->next, element_t, list), *next = ptr;

    for (bool same; next->list.next != head; ptr = next) {
        next = list_entry(ptr->list.next, element_t, list);
        same = ptr->value == next->value;
        if (same || prev)
            list_move(&ptr->list, &duplist);
        prev = same;
    }

    // don't forget last node
    if (prev)
        list_move(&ptr->list, &duplist);

    return true;
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

    q_delete_dup(&doubly);

    // back to singly
    Node *new = NULL, **pnew = &new;

    element_t *ptr;
    list_for_each_entry (ptr, &doubly, list) {
        Node *n = malloc(sizeof(Node));
        n->val = ptr->value;
        n->next = NULL;

        *pnew = n;
        pnew = &(*pnew)->next;
    }

    return new;
}