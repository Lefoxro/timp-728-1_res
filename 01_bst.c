#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <string.h>

// Структура для хранения узла дерева.
// Необходимо хранить ссылки на потомков, предка и некоторое значение
typedef struct node 
{
        int value;
        struct node *left;
        struct node *right;
        struct node *parent;
} 
node;

// Структура для хранения дерева.
// Хранит ссылку на корень дерева и количество элементов в дереве
typedef struct tree 
{
        struct node *current;
        struct node *root;
        int numbers;
} 
tree;

// Инициализация дерева
void init(tree* t)
{
	t->root=NULL;
}

// Поиск элемента по значению. Вернуть NULL если элемент не найден
node* find(tree* t, int value)
{
	t->current = t->root; 
	while(t->current->value != value)
	{
		if(t->current->value > value) 
		{
			t->current = t->current->left; 
		}
		else
		{
			t->current = t->current->right;
		}
		if(t->current == NULL) 
		{
			return NULL;
		}
	}
	return t->current;
}

// Вставка значения в дерево:
// 0 - вставка выполнена успешно
// 1 - элемент существует
// 2 - не удалось выделить память для нового элемента
int insert(tree* t, int value)
{
	node *root2 = t->root, *root3 = NULL; 
	t->current = malloc(sizeof(node)); 
	t->current->value = value; 
	if (t->root == NULL)
	{
		t->current->parent = NULL; 
		t->current->left = NULL; 
		t->current->right = NULL; 
		t->root = t->current; 
		t->numbers = 1; 
		return 0; 
	}
	while (root2 != NULL) 
	{
		root3 = root2; 
		if (value == root2->value) 
                {
                        return 1; 
                }
		if (value < root2->value) 
		{
			root2 = root2->left; 
		}
		else 
		{
			root2 = root2->right; 
		}
	} 
	t->current->parent = root3; 
	t->current->left = NULL; 
	t->current->right = NULL;
	if (value < root3->value) 
	{
		root3->left = t->current; 
		t->numbers = t->numbers + 1; 
		return 0; 
	}
	if (value > root3->value) 
	{
		root3->right = t->current; 
		t->numbers = t->numbers +1; 
		return 0;
	}
}

// получение кол-во уровней в дереве
int get_levels(struct node * n, int deep) 
{
	  if (n == NULL){
    return deep;
  }
  int d1 = get_levels(n->left, deep + 1);
  int d2 = get_levels(n->right, deep + 1);

  return (d1 > d2) ? d1 : d2;
}

//функция для вывода уровня
void print_level(node* cur, int curl, int d, int first) 
{
	if (curl == d)
	{
		if (first > 0)
		{
			printf(" ");
		}

		if (cur != NULL) 
		{
		printf("%d", cur->value);
		}
	}
	else if (cur != NULL) 
	{
		print_level(cur->left, curl + 1, d, first);
		print_level(cur->right, curl + 1, d, first + 1);
	}
	else 
	{
		print_level(cur, curl + 1, d, first);
		print_level(cur, curl + 1, d, first + 1);
	}
}

// Вывести все значения из поддерева, корнем которого является n
// по уровням начиная с корня.
// Каждый уровень выводится на своей строке. 
// Элементы в строке разделяются пробелом. Если элемента нет, заменить на _. 
// Если дерево пусто, вывести -
void print(node* n)
{
	int m = get_levels(n, 0);
	for (int i = 1; i <= m; i++)
	{
		print_level(n, 1, i, 0);
		printf("\n");
	}
}

// Вывести все значения дерева t, аналогично функции print
void printTree(tree * t)
{
	print(t->root);
}

void print1(struct node * n)
{
	int m = get_levels(n, 0);
	int flag = 0;
	for (int i = 1; i <= m; i++)
	{
		if (flag > 0)
		{
		printf(" ");
		} 
		else 
		{
		flag++;
		}
	print_level(n, 1, i, 0);
	}
}

int main()
{
	struct tree * t = malloc(sizeof t);
	init(t);
	for (int i = 0; i < 7; i++)
	{
		int a;
		scanf("%d", &a);
		insert(t, a);
	}
	print1(t->root);
	printf("\n");
	return 0;
}
