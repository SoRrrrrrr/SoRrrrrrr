//n�� �־�����, n���� ������ �� ���� �ϳ��� ���������� �Էµ�
//�Էµ� ������ ������ �Էµ� ������ �߿��� �۰ų� ���� ���� �����ϰ� ������ ����(�ڽ� ����) ���
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NUM 100000 //max for n

typedef int Item;

typedef struct node {
	Item data;
	struct node* next;
}Node;

typedef struct {
	Node* top;
}StackType;

int is_empty(StackType* s) {
	return s->top == NULL;
}

static void terminate(const char* errmsg) {
	printf("%s\n", errmsg);
	exit(1);
}

StackType* create_stack(void) {
	StackType* s = (StackType*)malloc(sizeof(StackType));
	if (s == NULL)
		terminate("Error in create : stack could not be created.");
	s->top = NULL;
	return s;
}

void push(StackType* s, Item data) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node == NULL)
		terminate("Error in push : memory allocation failed.\n");
	new_node->next = s->top;
	s->top = new_node;
	new_node->data = data;
}

Item pop(StackType* s) {
	if (is_empty(s))
		terminate("Error in pop : stack is empty.\n");
	Node* old_node = s->top;
	Item old_data = old_node->data;
	s->top = old_node->next;
	free(old_node);
	return old_data;
}

Item peek(StackType* s) {
	if (is_empty(s)) terminate("Error in peek : stack is empty.\n");
	return s->top->data;
}

//list �Լ��� printf->cnt++�� �ٲٸ� ��
Item cnt_data(StackType* s) {
	int cnt = 0;
	Node* pnt_s = s->top;
	while (pnt_s != NULL) {
		cnt++;
		pnt_s = pnt_s->next;
	}return cnt;
}

int main() {
	int n, input[MAX_NUM];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &input[i]);

	StackType* s = create_stack();

	for (int i = 0; i < n; i++) {
		//�۰ų� ������ pop(�ߺ� ����)
		while (!is_empty(s) && peek(s) <= input[i])
			pop(s);
		push(s, input[i]);
		printf("%d ", cnt_data(s));
	}return 0;
}