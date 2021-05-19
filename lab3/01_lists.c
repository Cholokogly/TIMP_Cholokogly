#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    struct node *next;
} node;

typedef struct list
{
    node* head;
    node* tail;
} list;

void init(list *l)
{
    l->head = NULL;
    l->tail = NULL;
}

bool is_empty(list *l) {
    if (l == NULL) {
        return true;
    }

    return l->head == NULL;
}

void clean(list *l)
{
    if (l == NULL) {
        return;
    }

    if (!is_empty(l)) {
        node *pNextNode = l->head;
        node *pNode;

        while (pNextNode != NULL) {
            pNode = pNextNode;
            pNextNode = pNode->next;

            free(pNode);
        }
    }
}

node* find(list *l, int value)
{
    if (l == NULL) {
        return NULL;
    }

    if (is_empty(l)) {
        return NULL;
    }

    node *pNode = l->head;

    while (pNode) {
        if (pNode->value == value) {
            return pNode;
        }

        pNode = pNode->next;
    }

    return NULL;
}

int push_front(list *l, int value)
{
    if (l == NULL) {
        return -1;
    }

    node* pNode = (node*)malloc(sizeof(node));

    pNode->value = value;
    pNode->next = l->head;

    if (l->head == NULL) {
        l->tail = pNode;
    }

    l->head = pNode;

    return 0;
}

int push_back(list *l, int value)
{
    if (l == NULL) {
        return -1;
    }

    if (is_empty(l)) {
        return push_front(l, value);
    }

    node* pNode = (node*)malloc(sizeof(node));

    pNode->value = value;
    pNode->next = NULL;

    l->tail->next = pNode;
    l->tail = pNode;

    return 0;
}

int insert_after(node *n, int value)
{
    if (n == NULL) {
        return -1;
    }

    node* pNode = (node*)malloc(sizeof(node));

    pNode->value = value;
    pNode->next = n->next;

    n->next = pNode;

    return 0;
}

int remove_node(list *l, int value)
{
    if (l == NULL) {
        return -1;
    }

    if (is_empty(l)) {
        return -1;
    }

    node *pNode = l->head;
    node *pPreNode = pNode;

    while (pNode != NULL) {
        if (pNode->value == value) {
            if (pPreNode == l->head) {
                l->head = pNode->next;
            } else if (!pNode->next) {
                l->tail = pPreNode;
            }

            pPreNode->next = pNode->next;

            free(pNode);

            return 0;
        }

        pPreNode = pNode;
        pNode = pNode->next;
    }

    return -1;
}

void print(list *l)
{
    if (l == NULL) {
        return;
    }

    if (is_empty(l)) {
        return;
    }

    node *pNode = l->head;

    while (pNode != NULL)
    {
        printf("%d ", pNode->value);

        pNode = pNode->next;
    }

    printf("\n");
}

node* get(list* l, unsigned int index)
{
    if (index == 0) {
        index = 1;
    }

    if (l == NULL) {
        return NULL;
    }

    if (is_empty(l))
    {
        return NULL;
    }

    node* pNode = l->head;

    unsigned int i = 1;

    while (pNode != NULL)
    {
        if (i == index) {
            return pNode;
        }

        pNode = pNode->next;
        ++i;
    }

    return NULL;
}

int main()
{
    unsigned int n;

    int args = scanf("%u", &n);

    if (args != 1 || n == 0) {
        return 1;
    }

    list *linkedList = (list*)malloc(sizeof(list));

    init(linkedList);

    int a;

    for (unsigned int i = 0; i < n; ++i) {
        args = scanf("%d", &a);

        if (args != 1) {
            return 2;
        }

        push_back(linkedList, a);
    }

    print(linkedList);

    int k[3];

    for (unsigned int i = 0; i < 3; ++i)
    {
        args = scanf("%d", &k[i]);

        if (args != 1) {
            return 3;
        }
    }

    for (unsigned int i = 0; i < 3; ++i) {
        printf("%d ", find(linkedList, k[i]) != NULL);
    }

    printf("\n");

    int m;

    args = scanf("%d", &m);

    if (args != 1) {
        return 4;
    }

    push_back(linkedList, m);

    print(linkedList);

    int t;

    args = scanf("%d", &t);

    if (args != 1) {
        return 5;
    }

    push_front(linkedList, t);

    print(linkedList);

    unsigned int j;

    args = scanf("%u", &j);

    if (args != 1) {
        return 6;
    }

    int x;

    args = scanf("%d", &x);

    if (args != 1) {
        return 7;
    }

    node* pNode = get(linkedList, j);

    if (pNode == NULL) {
        return 8;
    }

    insert_after(pNode, x);

    if (pNode == linkedList->tail) {
        linkedList->tail = pNode->next;
    }

    print(linkedList);

    int z;

    args = scanf("%d", &z);

    if (args != 1) {
        return 9;
    }

    if (pNode != NULL) {
        remove_node(linkedList, z);
    }

    print(linkedList);

    clean(linkedList);

    free(linkedList);

    return 0;
}
