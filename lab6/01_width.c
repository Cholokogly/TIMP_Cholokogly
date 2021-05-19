#include <stdio.h>
#include <stdlib.h>

typedef struct tree
{
    struct node *root;
    int count;
} tree;

typedef struct node
{
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
} node;

void init(tree* t) {
    t->root = NULL;
    t->count = 0;
}

int insert(tree* t, int value) {
    
    node *nodeNew = (node*) malloc(sizeof(node));
    node *node1 = t->root, *node2 = NULL;
    while (node1 != NULL) {
        node2 = node1;
        if (value < node1->key) {
            node1 = node1->left;
        } else if (value == node1->key) {
            return 1;
        } else {
            node1 = node1->right;
        }
    }
    nodeNew->key = value;
    nodeNew->left = NULL;
    nodeNew->right = NULL;
    nodeNew->parent = node2;
    
    if (t->root == NULL) {
        t->root = nodeNew;
    }

    if (node2 != NULL) {
        if (value < node2->key) {;
            node2->left = nodeNew;
        } else  {
            node2->right = nodeNew;
        }
    }
    t->count++;
    return 0;
}

typedef struct struct_item{
    void *payload;
    struct struct_item* next;
} item;

typedef struct struct_queue{
    item* begin;
    item* end;
}queue;

queue* create_queue(){
    queue* res = malloc(sizeof(queue));
    res->begin = NULL;
    res->end = NULL;
    return res;
}

void queue_push(queue* q, void *payload){
    item *i = malloc(sizeof(item));
    i->next = NULL;
    i->payload = payload;

    if(q->end == NULL){
        q->begin = i;
        q->end = i;
    }else{
        q->end->next = i;
        q->end = i;
    }
}

void* queue_pop(queue *q){
    if(q->begin == NULL) return NULL;
    item *current = q->begin;
    q->begin = q->begin->next;
    if(q->begin == NULL) q->end = NULL;
    void* payload = current->payload;
    free(current);
    return payload;
}

void print(tree* t, node* root){
    queue* q_current = NULL;
    queue* q_next = create_queue();
    queue_push(q_next, (void *) root);
    
    if (t->count == 0) {
        printf("-");
        printf("\n");
        return;
    }
    int isNotLastLevel;
    do {
        free(q_current);
        q_current = q_next;
        q_next = create_queue();
        void* payload;

        isNotLastLevel = 0;
        while(q_current->begin != NULL){
            payload = queue_pop(q_current);
            if(payload != NULL){
                node* n = (node *)payload;
                printf("%d ", n->key);
                queue_push(q_next, n->left);
                queue_push(q_next, n->right);
                isNotLastLevel = isNotLastLevel || n->left || n->right;
            }else{
                queue_push(q_next, NULL);
                queue_push(q_next, NULL);
            }
        }
    } while(isNotLastLevel);

    free(q_current);
    while(q_next->begin != NULL) queue_pop(q_next);
    free(q_next);
}

void print_tree(tree* t) {
    print(t, t->root);
}

int main()
{
    tree t;
    init(&t);
    int a, a1, a2, a3, a4, a5, a6;
    
    scanf("%d %d %d %d %d %d %d", &a, &a1, &a2, &a3, &a4, &a5, &a6);
    insert(&t, a);
    insert(&t, a1);
    insert(&t, a2);
    insert(&t, a3);
    insert(&t, a4);
    insert(&t, a5);
    insert(&t, a6);
    print_tree(&t);
    printf("\n");
    return 0;
}

