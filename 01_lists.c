#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node {
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
	struct node *prev;  // ссылка на предыдущий элемент списка
} node;

typedef struct list {
	struct node *head;  // начало списка
	struct node *tail;  // конец списка
} list;

// инициализация пустого списка
void init(list *l) 
    {
        l->head = l->tail = NULL;
    }
// удалить все элементы из списка
void clean(list *l)
 {
        node * curr = NULL;
        while ((l->head->next) != NULL) 
	{
            curr = l->head;
            l->head = l->head->next;
            free(curr);
        }
        free(l->head);
}
// проверка на пустоту списка
bool is_empty(list *l)
{
        node * curr = l->head;
        if (curr != NULL) 
            {
                return (1); 
            }
}
// поиск элемента по значению. вернуть NULL если элемент не найден
node *find(list *l, int value)
{
        node * curr = l->head;
        while ((curr != NULL)&&(curr->value != value)) {
        curr = curr->next;
        }
        return curr;
}
// вставка значения в конец списка, вернуть 0 если успешно
int push_back(list *l, int value)
{
    node *curr = (node*) malloc(sizeof(node));
    if (curr == NULL) {
        exit(3);
    }
    curr->value = value;
    curr->next = NULL;
    curr->prev = l->tail;
    if (l->tail) {
        l->tail->next = curr;
    }
    l->tail = curr;
 
    if (l->head == NULL) {
        l->head = curr;
    }
}
// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value)
    {
    node *curr = (node*) malloc(sizeof(node));
    if (curr == NULL) {
        exit(1);
    }
    curr->value = value;
    curr->next = l->head;
    curr->prev = NULL;
    if (l->head) {
        l->head->prev = curr;
    }
    l->head = curr;
    if (l->tail == NULL) {
        l->tail = curr;
    }
}
// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(list *l, node *n, int value)
    {
	if (n && n -> next)
	{
        node * curr = malloc(sizeof(node));
        curr->value = value;
        curr->next = n->next;
        curr->prev = n;
	n -> next = curr;
	n -> next ->next -> prev = curr;		
	return 0;
	}
	else
	{
	push_back(l, value);
	}
	return -1;
    }
// вставка значения перед указанным узлом, вернуть 0 если успешно
int insert_before(list *l, node *n, int value)
    {
	if (n && n -> prev)
	{
        node * curr = malloc(sizeof(node));
        curr->value = value;
        curr->prev = n->prev;
        curr->next = n;
	n -> prev = curr;
	n -> prev ->prev -> next = curr;		
	return 0;
	}
	else
	{
	push_front(l, value);
	}
	return -1;
    }
// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_first(list *l, int value)
{
	if(l->head == NULL)
	return -1;

	node * curr = l->head;

	while (curr->next)
	{
		if (curr->value == value)
	{
	if (curr->prev == NULL)
	{
		l->head = curr->next;
		curr -> next -> prev = NULL;
		free(curr);
		return 0;
	}
	if (curr->next == NULL)
	{
		l->tail = curr->prev;
		curr->prev->next = NULL;
		free(curr);
		return 0;
	}
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	free(curr);
	return 0;
	}
	curr = curr->next;
	}
	return -1;
}
// удалить последний элемент из списка с указанным значением,
// вернуть 0 если успешно
int remove_last(list *l, int value)
{
	if(l->tail == NULL)
	return -1;
	node *curr = l->tail;
	while (curr->prev)
	{
	if (curr->value == value)
	{
	if (curr->next == NULL)
	{
		l->tail = curr->prev;
		curr->prev->next = NULL;
		free(curr);
		return 0;
	}
	if (curr->prev == NULL)
	{
		l->head = curr->next;
		curr -> next -> prev = NULL;
		free(curr);
		return 0;
	}
	curr->prev->next = curr->next;
	curr->next->prev = curr->prev;
	free(curr);
	return 0;
	}
	curr = curr->prev;
	}
	return -1;
}
// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку

void print(list *l)
{
    node *curr = l->head;
    while (curr != NULL)
    {
        printf ("%d\n", curr -> value);
        curr = curr->next;
    } 
}
// вывести все значения из списка в обратном порядке через пробел,
// после окончания вывода перейти на новую строку
void print_invers(list *l)
{
    node *curr = l->tail;
    do
    {
        printf ("%d\n", curr -> value);
        curr = curr->prev;
    } 
    while (curr != NULL);
}

void check_bool(list *l, int value)
    {
        if (find(l, value) != NULL)
            printf("1 ");
        else
            printf("0 ");
    }
//Поиск номера элемента
node *number(list *l, int idx)
    {
        node * curr = l->head;
        int itter = 0;
        while ((curr != NULL)&&(itter!= idx-1)) {
            curr = curr->next;
            itter++;
        }
        return curr;
    }
    
int main()    {
        int n, digit, elem;
        int i = 1;
        list l = {0};

        int check = scanf("%d", &n);
        assert(check == 1);
        while (i <= n)
        {
            check = scanf("%d", &digit);
            assert(check == 1);
            push_back(&l, digit);
            i++;
        }
        print(&l);
        printf("\n");

//Нахождение элементов в списке
        i = 1;
        while (i <= 3)
        {
            check = scanf("%d", &digit);
            assert(check == 1);
            check_bool(&l, digit);
            i++;
        }
        printf("\n");
        
//Добавление в конец
        check = scanf("%d", &digit);
        assert(check == 1);
        push_back(&l, digit);
        print_invers(&l);
        printf("\n");

//Добавлние в начало
        check = scanf("%d", &digit);
        assert(check == 1);
        push_front(&l, digit);
        print(&l);
        printf("\n");

//Добавление после указанного элемента
        check = scanf("%d", &digit);
        assert(check == 1);
        check = scanf("%d", &elem);
        assert(check == 1);
        node * insert_head = number(&l, digit);
        insert_after(&l, insert_head, elem);
        print_invers(&l);
        printf("\n");

//Добавление перед указанным элементом
        check = scanf("%d", &digit);
        assert(check == 1);
        check = scanf("%d", &elem);
        assert(check == 1);
        node * insert_tail = number(&l, digit);
        insert_before(&l, insert_tail, elem);
        print(&l);
        printf("\n");

//Удалить первый элемент равный введенному
        check = scanf("%d", &digit);
        assert(check == 1);
        remove_first(&l, digit);
        print_invers(&l);
        printf("\n");

//Удалить последний элемент равный введенному
        check = scanf("%d", &digit);
        assert(check == 1);
        remove_last(&l, digit);
        print(&l);
        printf("\n");

//Очистить список
        clean(&l);
        return 0;
    };