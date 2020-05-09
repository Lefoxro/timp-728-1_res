#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct node {
	int value;          // значение, которое хранит узел 
	struct node *next;  // ссылка на следующий элемент списка
} node;
typedef struct list {
	struct node *head;  // начало списка
} list;
// инициализация пустого списка
void init(list *l) 
    {
        l->head = NULL;
    }
// удалить все элементы из списка
void clean(list *l)
 {
        node * cl = NULL;
        while ((l->head->next) != NULL) {
            cl = l->head;
            l->head = l->head->next;
            free(cl);
        }
        free(l->head);
}
// проверка на пустоту списка (Возвращение 1, если список не пустой)
bool is_empty(list *l)
{
        node * curr = l->head;
        if (curr != NULL) 
            {
                return (1); 
            }
}
// поиск элемента по значению. вернуть NULL если эжемент не найден
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
if (l->head != NULL)
        {
            node * curr = l->head;
            while (curr->next != NULL) 
            {
                curr = curr->next;
            }
            curr->next = malloc(sizeof(node));
            curr->next->value = value;
            curr->next->next = NULL;
            return 0;
        }
        else
        {
            node * curr = malloc(sizeof(node));
            curr->value = value;
            curr->next = l->head;
            l->head = curr;
            return 0;
        }
}
// вставка значения в начало списка, вернуть 0 если успешно
int push_front(list *l, int value)
    {
        node * curr = malloc(sizeof(node));
        if (!curr) {
            return -1;
        }
        curr->value = value;
        curr->next = l->head;
        l->head = curr;
        return 0;
    }

// вставка значения после указанного узла, вернуть 0 если успешно
int insert_after(node *n, int value)
    {
        node * curr = malloc(sizeof(node));
        curr->value = value;
        curr->next = n->next;
        n->next = curr;
		return 0;
    }

// удалить первый элемент из списка с указанным значением, 
// вернуть 0 если успешно
int remove_node(list *l, int value)
{
    if(l->head == NULL)
        return -1;
    node * curr = l->head;
    node * prev = NULL;
    while (curr->next) 
    {
        if (curr->value == value)
        {
            if (prev == NULL)
            {
                l->head = curr->next;
                free(curr);
                return 0;
            }
            prev->next = curr->next;
            free(curr);
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }
    return -1;
}

// вывести все значения из списка в прямом порядке через пробел,
// после окончания вывода перейти на новую строку
void print(list *l)
{
    node * curr = l->head;
    while (curr != NULL)
    {
        printf ("%d\n", curr -> value);
        curr = curr->next;
    } 
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
int main() 
{
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
        print(&l);
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
        insert_after(insert_head, elem);
        print(&l);
        printf("\n");

        //Удалить первый элемент равный введенному
        check = scanf("%d", &digit);
        assert(check == 1);
        remove_node(&l, digit);
        print(&l);
        printf("\n");

        //Очистить список
        clean(&l);
        return 0;
};