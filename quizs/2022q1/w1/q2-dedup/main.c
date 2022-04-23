#include "doubly-recur.c"

int main(int argc, char const *argv[])
{
    Node *head, **phead = &head;

    int vals[] = {1, 1, 2, 3, 4, 4, 5, 6, 7, 7};

    for (int i = 0; i < (sizeof(vals) / sizeof(vals[0])); ++i) {
        Node *n = malloc(sizeof(Node));
        n->val = vals[i];
        n->next = NULL;

        *phead = n;
        phead = &(*phead)->next;
    }

    deleteDuplicates(head);
    return 0;
}
