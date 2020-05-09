#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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


//Функция рекурсивного удаления
node* cleant(node* t) 
{
	if(t!=NULL)
	{
		cleant(t->left); 
		cleant(t->right); 
		if(t->left!=NULL)
			t->left = NULL;
		if(t->right!=NULL)
			t->right = NULL;
		free(t); 
	}
	return NULL;
}

// Удалить все элементы из дерева
void clean(tree* t)
{
        node* root = t->root;
        cleant(root);
        t->root = NULL;
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

// Удалить минимальный элемент из поддерева, корнем которого является n
// Вернуть значение удаленного элемента

int remove_min(node* n)
{
	int b;
	node *cur = n; 
	while (cur->left != NULL) 
	{
		cur = cur->left;  
	}
	b = cur->value; 
	if(cur->right != NULL)
	{
		if(b < cur->parent->value)
		{
			cur->parent->left = cur->right;
			free(cur);
			return b;
		}
		else
		{
			cur->parent->right = cur->right;
			free(cur);
			return b;
		}
	}
	else
	{
		if (b < cur->parent->value)
		{
			cur->parent->left = NULL;
			free(cur);
			return b;
		}
		else
		{
			cur->parent->right = NULL;
			free(cur);
			return b;
		}
	}
}

// Удалить элемент из дерева:
// 0 - удаление прошло успешно
// 1 - нет элемента с указанным значением
int remove_node(tree* t, int value)
{
	int b;
	node *cur = find(t, value); 
	if (cur == NULL) 
		return 1;
	if (cur->left==NULL && cur->right==NULL)
	{
		if(cur != t->root) 
		{
			if (cur->value < cur->parent->value) 
			{
				cur->parent->left = NULL; 
				free(cur); 
				t->numbers = t->numbers-1; 
				return 0; 
			}
			else
			{
				cur->parent->right = NULL; 
				free(cur); 
				t->numbers = t->numbers-1; 
				return 0; //конец
			}
		}
		else 
		{
			free(cur); 
			t->root = NULL; 
			t->numbers = 0;
			return 0;
		}
	}
	if (cur->left==NULL && cur->right!=NULL) 
	{
		if(cur != t->root) 
		{
			if (cur->value < cur->parent->value) 
			{
				cur->parent->left = cur->right; 
				cur->right->parent = cur->parent; 
				free(cur);
				t->numbers = t->numbers-1; 
				return 0; 
			}
			else 
			{
				cur->parent->right = cur->right; 
				cur->right->parent = cur->parent; 
				free(cur); 
				t->numbers = t->numbers-1; 
				return 0; 
			}
		}
		else 
		{
			cur->right->parent = NULL; 
			t->root = cur->right; 
			free(cur); 
			t->numbers = t->numbers-1; 
			return 0; 
		}
	}
	if (cur->left!=NULL && cur->right==NULL) 
	{
		if(cur !=t->root) 
		{
			if (cur->value < cur->parent->value) 
			{
				cur->parent->left = cur->left;
				cur->left->parent = cur->parent;
				free(cur);
				t->numbers = t->numbers-1;
				return 0;
			}
			else 
			{
				cur->parent->right = cur->left;
				cur->left->parent = cur->parent;
				free(cur);
				t->numbers = t->numbers-1;
				return 0;
			}
		}
		else 
		{
			cur->left->parent = NULL; 
			t->root = cur->left; 
			free(cur); 
			t->numbers = t->numbers-1; 
			return 0; 
		}
	}
	if(cur->right!=NULL && cur->left!=NULL) 
	{
		b = remove_min(cur->right); 
		cur->value = b; 
		t->numbers = t->numbers-1; 
		return 0; 
	}
}

// Выполнить правое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно 
int rotate_right(node* n)
{
	node* y = n;
	node* x = y->left;
        node* z = x->right;
        x->parent = y->parent;
        if(y->parent != NULL)
        {
            if(y->parent->value > y->value)
            {
                  y->parent->left = x;
            }
            else
            {
                y->parent->right = x;
            }
        }
        if(z!=NULL)
        {
            z->parent = y;
        }
        y->left = z;
        y->parent = x;
        x->right = y;
        return 0;
}

// Выполнить левое вращение поддерева, корнем которого является n:
// 0 - успешно выполненная операция
// 1 - вращение невозможно
int rotate_left(node* n)
{
	node* x = n;
	node* y = x->right;
	node* b = y->left;
        y->parent = x->parent;
	if(x->parent != NULL)
	{
		if(x->parent->value > x->value)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}
	if(b!=NULL)
	{
	b->parent = x;
	}
	x->right = b;
	x->parent = y;
	y->left = x;
	return 0;
}

int rotate_root_left(tree* t)
{
        rotate_left(t->root);
	if (t->root->parent != NULL)
		t->root = t->root->parent;
	return 0;
}

int rotate_root_right(tree* t)
{
        rotate_right(t->root);
	if (t->root->parent != NULL)
	        t->root = t->root->parent;
        return 0;
}

//Функция нахождения предка и потомка заданного элемента
void checkrel(tree* t, int value)
{
	node *tmp = find(t, value);
        if(tmp==NULL)
        {
                printf("-");
                printf("\n");
        }
        else
        {
                if (tmp->parent != NULL)
                {
                printf("%d", tmp->parent->value);
                printf(" ");
                }
                else
                {
                        printf("_ ");
                }
                if(tmp->left)
                {
                        printf("%d", tmp->left->value);
                }
                else
                {
                        printf("_");
                }
                printf(" ");
                if(tmp->right)
                {
                printf("%d", tmp->right->value);
                }
                else
                {
                        printf("_");
                }
                printf("\n");
        }
        printf("\n");
}

// получение кол-во уровней в дереве
int get_levels(node* cur) 
{
	if (cur == NULL)
	{
		return 0;
	}
	int lmax = 1 + get_levels(cur->left);
	int rmax = 1 + get_levels(cur->right);
	if (lmax > rmax)
	{
		return lmax;
	}
	else
	{
		return rmax;
	}
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

		if (cur == NULL) {
		printf("_");
		}
		else
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
	int num = get_levels(n);
	for (int i = 1; i <= num; i++)
	{
		print_level(n, 1, i, 0);
		printf("\n");
	}
}

// Вывести все значения дерева t, аналогично функции print
void print_tree(tree* t)
{
	node* n = t->root;
	if (n == NULL) 
	{
	printf("-");
	printf("\n");
	}
	int num = get_levels(n);  
	for (int i = 1; i <= num; i++)
	{
		print_level(n, 1, i, 0);
		printf("\n");
	}
}

//Функция, возвращающая указатель на корень
node* rootret(tree* t) 
{
	return t->root;
} 

//Вывод количества элементов в списке
void print_num(tree* t) 
{
	printf("%d", t->numbers);
}

int main()
{
	int a, i, m1, m2;
	struct tree t;
	init(&t);
	//Считывание 4 элементов
	for (i=0; i<4; i++)
	{
		scanf("%d", &a);
		insert(&t, a);
	}
	//Вывод дерево
	print_tree(&t);
	printf("\n");
	//Считывание 3 элементов
	for (i=0; i<3; i++)
	{
		scanf("%d", &a);
		insert(&t, a);
	}
	print_tree(&t);
	printf("\n");
	scanf("%d", &m1);
	checkrel(&t, m1);
	scanf("%d", &m1);
        checkrel(&t, m1);
	scanf("%d", &m1);
	//удаление элемента
	remove_node(&t, m1);
	print_tree(&t);
	printf("\n");
	//Левый поворот, пока это возможно
	node* troot = rootret(&t);
	if (troot != NULL)
	{
		while (troot->right != NULL)
		{
			rotate_root_left(&t);
        		troot = rootret(&t);
		}
	}
	printf("\n");
        print_tree(&t);
	// Правый поворот, пока это возможно
	troot = rootret(&t);
	if(troot != NULL)
	{
	        while (troot->left != NULL)
	        {
		        rotate_root_right(&t);
	                troot = rootret(&t);
	        }
        }
	printf("\n");
        print_tree(&t);
	//Количество элементов
	printf("\n");
	print_num(&t);
	printf("\n\n");
	//Очищение дерева
	clean(&t);
	troot = rootret(&t);
	print_tree(&t);
	return 0;
};

