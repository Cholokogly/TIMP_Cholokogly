#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;
    struct node *next;
    struct node *prev;
} node;

typedef struct list {
    struct node *head;
    struct node *tail;
} list;

// инициализация пустого списка
void init(list *l)
{
    l->tail = NULL;
    l->head = NULL;
}

bool is_empty(list *l)
{
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

    init(l);
}

node* find(list *l, int value, bool revert)
{
    if (l == NULL) {
        return NULL;
    }

    if (is_empty(l)) {
        return NULL;
    }

    node *pNode = revert ? l->tail : l->head;

    while (pNode) {
        if (pNode->value == value) {
            return pNode;
        }

        pNode = revert ? pNode->prev : pNode->next;
    }

    return NULL;
}

int push_front(list *l, int value)
{
    //Лист не проинициализирован
    if (l == NULL) {
        return 1;
    }

    //Создаем ноду
    node *pNode = (node*)malloc(sizeof(node));

    //Задаем новой ноде значение
    pNode->value = value;
    //Задаем новой ноде следующий элемент - нода в начале листа
    pNode->next = l->head;
    //Предыдущего значения нет
    pNode->prev = NULL;

    //Если head задан
    if (l->head != NULL) {
        //Задаем предыдущий элемент ноде в начале листа - новую ноду
        l->head->prev = pNode;
    } else {
        //Ставим новую нову конечной нодой листа
        l->tail = pNode;
    }

    //Ставим новую нову начальной нодой листа
    l->head = pNode;

    return 0;
}

// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value)
{
    //Лист не проинициализирован
    if (l == NULL) {
        return 1;
    }

    //Создаем ноду
    node *pNode = (node*)malloc(sizeof(node));

    //Задаем новой ноде значение
    pNode->value = value;
    //Задаем новой ноде предыдущий элемент - нода в конце листа
    pNode->prev = l->tail;
    //Следующего значения нет
    pNode->next = NULL;

    //Если tail задан
    if (l->tail != NULL)
    {
        //Задаем следующий элемент ноде в конце листа - новую ноду
        l->tail->next = pNode;
    } else {
        //Ставим новую нову начальной нодой листа
        l->head = pNode;
    }

    //Ставим новую нову конечной нодой листа
    l->tail = pNode;

    return 0;
}

int insert_after(list *l, node *n, int value)
{
    //Лист не проинициализирован
    if (l == NULL) {
        return 1;
    }

    //Создаем ноду
    node *pNode = (node*)malloc(sizeof(node));

    //Задаем новой ноде значение
    pNode->value = value;
    //Задаем новой ноде следующий элемент - следующая нашей ноды
    pNode->next = n->next;
    //Задаем предыдущей элемент новой ноды - наша нода
    pNode->prev = n;

    //Если следующая нода существует
    if (n->next != NULL) {
        //Задаем предыдущей элемент следующей ноде нашей ноды - новую ноду
        n->next->prev = pNode;
    } else {
        l->tail = pNode;
    }

    //Задаем нашей ноде следующий элемент
    n->next = pNode;

    return 0;
}

int insert_before(list *l, node *n, int value)
{
    //Лист не проинициализирован
    if (l == NULL) {
        return 1;
    }

    //Создаем ноду
    node *pNode = (node*)malloc(sizeof(node));

    //Задаем новой ноде значение
    pNode->value = value;
    //Задаем новой ноде следующий элемент - наша ноды
    pNode->next = n;
    //Задаем предыдущей элемент новой ноды - предыдущая нода нашей ноды
    pNode->prev = n->prev;

    //Если предыдущая нода существует
    if (n->prev != NULL) {
        //Задаем следующий элемент предыдущей ноде нашей ноды - новая нода
        n->prev->next = pNode;
    } else {
        l->head = pNode;
    }

    //Задаем предыдущей элемент нашей ноды - новую ноду
    n->prev = pNode;

    return 0;
}

int remove_first(list *l, int value, bool revert)
{
    //Лист не проинициализирован
    if (l == NULL) {
        return 1;
    }

    //Лист пустой
    if (is_empty(l)) {
        return 2;
    }

    //Ищем ноду с указанным значением
    node *pNode = find(l, value, revert);

    //Нода не проинициализирована
    if (pNode == NULL) {
        return 3;
    }

    //Нода первая в листе
    if (pNode->prev == NULL) {
        //Смещаем head листа к следующей ноде
        l->head = pNode->next;
    } else if (pNode->next == NULL) { //Нода последняя в листе
        //Смещаем tail листа к предыдущей ноде
        l->tail = pNode->prev;
        //Убираем у предыдущей ноды связь с найденной
        pNode->prev->next = NULL;
    } else { //Нода в середине листа
        //Задаем следующую ноду у предыдущий ноды - следующая нашей ноды
        pNode->prev->next = pNode->next;

        //Если следующая нода существует
        if (pNode->next != NULL) {
            //Задаем предыдущую ноду у следующей ноды - предыдущая нода нашей ноды
            pNode->next->prev = pNode->prev;
        }
    }

    //Очищаем память, выделенную для ноды
    free(pNode);

    return 0;
}

void print(list *l)
{
    //Лист не проинициализирован
    if (l == NULL) {
        return;
    }

    //Лист пустой
    if (is_empty(l)) {
        return;
    }

    //Начинаем с начала
    node *pNode = l->head;

    while (pNode != NULL)
    {
        //Выводим значения через пробел
        printf("%d ", pNode->value);

        //До конца
        pNode = pNode->next;
    }

    //Переходим на новую строку
    printf("\n");
}

void print_invers(list *l)
{
    //Лист не проинициализирован
    if (l == NULL) {
        return;
    }

    //Лист пустой
    if (is_empty(l)) {
        return;
    }

    //Начинаем с конца
    node *pNode = l->tail;

    while (pNode != NULL)
    {
        //Выводим значения через пробел
        printf("%d ", pNode->value);

        //До начала
        pNode = pNode->prev;
    }

    //Переходим на новую строку
    printf("\n");
}

node* get(list* l, unsigned int index)
{
    //Лист не проинициализирован
    if (l == NULL) {
        return NULL;
    }

    //Лист пустой
    if (is_empty(l)) {
        return NULL;
    }

    //Начинаем с начала
    node* pNode = l->head;

    unsigned int i = 1;

    while (pNode != NULL)
    {
        //До нужного индекса
        if (i == index) {
            return pNode;
        }

        pNode = pNode->next;
        ++i;
    }

    //Если индекс вышел за рамки размера листа

    return NULL;
}


int main()
{
    unsigned int n;

    int args = scanf("%u", &n);

    if (args != 1) {
        return 1;
    }

    if (n == 0) {
        return 2;
    }

    list *linkedList = (list*)malloc(sizeof(list));

    init(linkedList);

    int a;

    for (unsigned int i = 0; i < n; ++i) {
        args = scanf("%d", &a);

        if (args != 1) {
            return 3;
        }

        push_back(linkedList, a);
    }

    print(linkedList);

    int k[3];

    for (unsigned int i = 0; i < 3; ++i)
    {
        args = scanf("%d", &k[i]);

        if (args != 1) {
            return 4;
        }
    }

    for (unsigned int i = 0; i < 3; ++i) {
        printf("%d ", find(linkedList, k[i], false) != NULL);
    }

    printf("\n");

    int m;

    args = scanf("%d", &m);

    if (args != 1) {
        return 5;
    }

    push_back(linkedList, m);

    print_invers(linkedList);

    int t;

    args = scanf("%d", &t);

    if (args != 1) {
        return 6;
    }

    push_front(linkedList, t);

    print(linkedList);

    unsigned int j;

    args = scanf("%u", &j);

    if (args != 1) {
        return 7;
    }

    if (j == 0) {
        return 8;
    }

    int x;

    args = scanf("%d", &x);

    if (args != 1) {
        return 9;
    }

    node* pNode = get(linkedList, j);

    if (pNode == NULL) {
        return 10;
    }

    insert_after(linkedList, pNode, x);

    print_invers(linkedList);

    unsigned int u;

    args = scanf("%u", &u);

    if (args != 1) {
        return 11;
    }

    if (u == 0) {
        return 12;
    }

    int y;

    args = scanf("%d", &y);

    if (args != 1) {
        return 13;
    }

    pNode = get(linkedList, u);

    if (pNode == NULL) {
        return 14;
    }

    insert_before(linkedList, pNode, y);

    print(linkedList);

    int z;

    args = scanf("%d", &z);

    if (args != 1) {
        return 15;
    }

    remove_first(linkedList, z, false);

    print_invers(linkedList);

    int r;

    args = scanf("%d", &r);

    if (args != 1) {
        return 16;
    }

    remove_first(linkedList, r, true);

    print(linkedList);

    clean(linkedList);

    free(linkedList);

    return 0;
}
