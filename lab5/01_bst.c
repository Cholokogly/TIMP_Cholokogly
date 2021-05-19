#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct nodeTree {
    int value;
    bool inited;
    struct nodeTree *parent;
    struct nodeTree *right;
    struct nodeTree *left;
} nodeTree;

typedef struct tree {
    struct nodeTree *root;
    int count;
} tree;

void initTree(tree *t)
{
    t->root = NULL;
    t->count = 0;
}

void cleanNodeTree(nodeTree *n)
{
    if (n == NULL) {
        return;
    }

    if (n->left != NULL) {
        cleanNodeTree(n->left);
    }

    if (n->right != NULL) {
        cleanNodeTree(n->right);
    }

    free(n);
}

void cleanTree(tree *t)
{
    if (t == NULL) {
        return;
    }

    cleanNodeTree(t->root);

    t->root = NULL;
    t->count = 0;
}

nodeTree *findNodeInTree(tree *t, int value)
{
    if (t == NULL) {
        return NULL;
    }

    nodeTree *pNode = t->root;

    while (pNode != NULL && value != pNode->value) {
        pNode = (value < pNode->value) ? pNode->left : pNode->right;
    }

    return pNode;
}

nodeTree *findMinNodeInNode(nodeTree *n)
{
    while (n != NULL) {
        n = n->left;
    }

    return n;
}

enum nodeType
{
    LEAF = 0,
    FULL_ROOT,
    LEFT_ROOT,
    RIGHT_ROOT
};

int getNodeType(nodeTree *n)
{
    if (n->left != NULL && n->right != NULL) {
        return FULL_ROOT;
    }

    if (n->left != NULL) {
        return LEFT_ROOT;
    }

    if (n->right != NULL) {
        return RIGHT_ROOT;
    }

    return LEAF;
}

int removeNodeFromTree(tree* t, int value)
{
    nodeTree *pNode = findNodeInTree(t, value);

    if (pNode == NULL) {
        return 1;
    }

    switch (getNodeType(pNode)) {
        case FULL_ROOT: {
            nodeTree *pMinNode = pNode->right;

            while (pMinNode->left != NULL) {
                pMinNode = pMinNode->left;
            }

            if (getNodeType(pMinNode) == RIGHT_ROOT) {
                if (pMinNode->right->value < pMinNode->parent->value) {
                    pMinNode->parent->left = pMinNode->right;
                } else {
                    pMinNode->parent->right = pMinNode->right;
                }

                pMinNode->right->parent = pMinNode->parent;
            } else if (pMinNode->value < pMinNode->parent->value) {
                pMinNode->parent->left = NULL;
            } else {
                pMinNode->parent->right = NULL;
            }

            pMinNode->parent = pNode->parent;
            pMinNode->left = pNode->left;
            if (pNode->left != NULL) {
                pNode->left->parent = pMinNode;
            }
            pMinNode->right = pNode->right;
            if (pNode->right != NULL) {
                pNode->right->parent = pMinNode;
            }

            if (pMinNode->parent == NULL) {
                t->root = pMinNode;
            } else if (pMinNode->value < pMinNode->parent->value) {
                pMinNode->parent->left = pMinNode;
            } else {
                pMinNode->parent->right = pMinNode;
            }

            break;
        }
        case RIGHT_ROOT: {
            if (pNode->right->value < pNode->parent->value) {
                pNode->parent->left = pNode->right;
            } else {
                pNode->parent->right = pNode->right;
            }

            pNode->right->parent = pNode->parent;

            break;
        }
        case LEFT_ROOT: {
            if (pNode->left->value < pNode->parent->value) {
                pNode->parent->left = pNode->left;
            } else {
                pNode->parent->right = pNode->left;
            }

            pNode->left->parent = pNode->parent;

            break;
        }
        case LEAF: {
            if (pNode->parent != NULL) {
                if (pNode->value < pNode->parent->value) {
                    pNode->parent->left = NULL;
                } else {
                    pNode->parent->right = NULL;
                }
            } else {
                t->root = NULL;
            }

            break;
        }
    }

    free(pNode);

    --t->count;

    return 0;
}

nodeTree *createNode(int value, nodeTree *parent, bool inited) {
    nodeTree *pNode = (nodeTree*)malloc(sizeof(nodeTree));

    pNode->value = value;
    pNode->inited = inited;
    pNode->parent = parent;
    pNode->left = NULL;
    pNode->right = NULL;

    return pNode;
}

int insertNodeInTree(tree* t, int value)
{
    if (t == NULL) {
        return 2;
    }

    nodeTree *pNode = t->root;

    if (pNode == NULL) {
        pNode = createNode(value, NULL, true);

        t->root = pNode;

        ++t->count;

        return 1;
    }

    nodeTree *pParentNode;

    while (pNode != NULL) {
        pParentNode = pNode;

        if (value < pNode->value) {
            pNode = pNode->left;
        } else if (value > pNode->value) {
            pNode = pNode->right;
        } else {
            return 2;
        }
    }

    pNode = createNode(value, pParentNode, true);

    if (value < pParentNode->value) {
        pParentNode->left = pNode;
    } else {
        pParentNode->right = pNode;
    }

    ++t->count;

    return 1;
}

typedef struct nodeQueue {
    nodeTree *node;
    struct nodeQueue *next;
    struct nodeQueue *prev;
} nodeQueue;

typedef struct queue {
    nodeQueue *head;
    nodeQueue *tail;
} queue;

void initQueue(queue *q)
{
    q->head = NULL;
    q->tail = NULL;
}

void enqueue(queue *q, nodeTree* pNodeTree) {
    if (q == NULL || pNodeTree == NULL) {
        return;
    }

    nodeQueue *pNodeQueue = (nodeQueue*)malloc(sizeof(nodeQueue));

    pNodeQueue->node = pNodeTree;
    pNodeQueue->prev = NULL;
    pNodeQueue->next = q->head;

    if (q->head == NULL) {
        q->tail = pNodeQueue;
    } else {
        q->head->prev = pNodeQueue;
    }

    q->head = pNodeQueue;
}

nodeTree *dequeue(queue *q) {
    if (q == NULL || q->tail == NULL) {
        return NULL;
    }

    nodeQueue *pNodeQueue = q->tail;

    nodeTree *pNodeTree = pNodeQueue->node;

    q->tail = pNodeQueue->prev;

    if (q->tail != NULL) {
        q->tail->next = NULL;
    } else {
        q->head = NULL;
    }

    free(pNodeQueue);

    return pNodeTree;
}

bool needOutputNextLevel(nodeQueue *n)
{
    if (n == NULL) {
        return false;
    }

    while (n != NULL) {
        if (n->node->left != NULL || n->node->right != NULL) {
            return true;
        }

        n = n->prev;
    }

    return false;
}

void printNode(nodeTree *n)
{
    if (n == NULL) {
        printf("-\n");

        return;
    }

    queue *pQueue = (queue*)malloc(sizeof(queue));

    initQueue(pQueue);

    enqueue(pQueue, n);

    nodeTree *pNode;

    unsigned int i = 2;
    bool bNeedOutputNextLevel = false;

    while ((pNode = dequeue(pQueue)) != NULL) {
        bNeedOutputNextLevel = (bNeedOutputNextLevel || pNode->left != NULL || pNode->right != NULL || needOutputNextLevel(pQueue->tail));

        if (pNode->left != NULL) {
            enqueue(pQueue, pNode->left);
        } else if (bNeedOutputNextLevel) {
            enqueue(pQueue, createNode(0, NULL, false));
        }

        if (pNode->right != NULL) {
            enqueue(pQueue, pNode->right);
        } else if (bNeedOutputNextLevel) {
            enqueue(pQueue, createNode(0, NULL, false));
        }

        if (pNode->inited) {
            printf("%d ", pNode->value);
        } else {
            printf("_ ");
        }

        if ((i & (i-1)) == 0) {
            printf("\n");

            bNeedOutputNextLevel = false;
        }

        ++i;
    }
}

void printTree(tree *t, bool addSpace)
{
    if (t == NULL) {
        printf("-\n");
    }

    printNode(t->root);

    if (addSpace) {
        printf("\n");
    }
}

void findAndPrintValueInTree(tree *t, int value)
{
    nodeTree *pNode = findNodeInTree(t, value);

    if (pNode != NULL) {
        if (pNode->parent != NULL) {
            printf("%d ", pNode->parent->value);
        } else {
            printf("_ ");
        }

        if (pNode->left != NULL) {
            printf("%d ", pNode->left->value);
        } else {
            printf("_ ");
        }

        if (pNode->right != NULL) {
            printf("%d ", pNode->right->value);
        } else {
            printf("_ ");
        }
    } else {
        printf("-");
    }

    printf("\n\n");
}

int rotateRight(tree* t) {

    nodeTree *pNode = t->root;

    if (pNode != NULL && pNode->left != NULL) {
        t->root = pNode->left;

        nodeTree *tmpNode = pNode->left->right;

        pNode->left->right = pNode;

        pNode->parent = pNode->left;

        pNode->left->parent = NULL;

        pNode->left = tmpNode;

        if (tmpNode != NULL) {
            tmpNode->parent = pNode;
        }

        return 0;
    }

    return 1;
}

int rotateLeft(tree* t)
{
    nodeTree *pNode = t->root;

    if (pNode != NULL && pNode->right != NULL) {
        t->root = pNode->right;

        nodeTree *tmpNode = pNode->right->left;

        pNode->right->left = pNode;

        pNode->parent = pNode->right;

        pNode->right->parent = NULL;

        pNode->right = tmpNode;

        if (tmpNode != NULL) {
            tmpNode->parent = pNode;
        }

        return 0;
    }

    return 1;
}

int main()
{
    tree* pTree = (tree*)malloc(sizeof(tree));

    initTree(pTree);

    int a;

    unsigned char args;

    for (unsigned char i = 0; i < 4; ++i) {
        args = scanf("%d", &a);

        if (args != 1) {
            return 1;
        }

        insertNodeInTree(pTree, a);
    }

    printTree(pTree, true);

    for (unsigned char i = 0; i < 3; ++i) {
        args = scanf("%d", &a);

        if (args != 1) {
            return 2;
        }

        insertNodeInTree(pTree, a);
    }

    printTree(pTree, true);

    for (unsigned char i = 0; i < 2; ++i) {
        args = scanf("%d", &a);

        if (args != 1) {
            return 3;
        }

        findAndPrintValueInTree(pTree, a);
    }

    args = scanf("%d", &a);

    if (args != 1) {
        return 4;
    }

    removeNodeFromTree(pTree, a);

    printTree(pTree, true);

    a = 0;

    while (a == 0) {
        a = rotateLeft(pTree);
    }

    printTree(pTree, true);

    a = 0;

    while (a == 0) {
        a = rotateRight(pTree);
    }

    printTree(pTree, true);

    printf("%d\n\n", pTree->count);

    cleanTree(pTree);

    printTree(pTree, false);

    free(pTree);

    return 0;
}
