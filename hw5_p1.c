//��ȣ�� ���Ե� ���ڿ� �Է� �޾Ƽ� �� ��° ��ȣ�� ������ �������� ��ȣ�� ������ִ� ���α׷�
/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LEN 100

char OPEN[] = "([{";
char CLOSE[] = ")]}";
int open_num = 0; //���� ��ȣ ����

typedef char* Item;

typedef struct node {
	Item data;
	struct node* next;
	int num; //��ȣ�� ��ȣ�� ��Ÿ���� num �߰�
}Node;

typedef struct {
	node* top;
}StackType;

int is_empty(StackType* s) {
	return s->top == NULL;
}

StackType* create_stack(void) {
	StackType* s = (StackType*)malloc(sizeof(StackType));
	if (s == NULL) {
		printf("Error in create : stack could not be created.\n");
		return;
	}
	s->top = NULL;
	return s;
}

void push(StackType* s, Item data) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->next = s->top;
	s->top = new_node;
	new_node->data = data;
}

Item pop(StackType* s) {
	if (is_empty(s)) {
		printf("Error in pop : stack is empty.\n");
		return 0;
	}
	Node* old_node = s->top;
	Item old_data = old_node->data;
	s->top = old_node->next;
	free(old_node);
	return old_data;
}

int main() {
	char commend[MAX_LEN];
	scanf("%s", commend);
	print_paren_num(command);
	return 0;
}

//stack node�� push�� ��ȣ�� ��ȣ�� ��Ÿ���� int num�� ���
void print_paren_num(char* expr) {
	StackType* s = create_stack();

	//searching the paren
	for (int i = 0; i < strlen(expr); i++) {
		//open paren
		if (is_open(expr[i])) {
			push(expr[i]);
			open_num++;
			s->top->num = open_num;//��ȣ ��ȣ �ο�
			printf("%d ", open_num);
		}
		else if (is_close(expr[i])) {
			printf("%d ", s->top->num);
			pop(s);
		}
		else continue;
	}
}

int is_open(char ch) {
	for (int i = 0; i < strlen(OPEN); i++) {
		if (ch == OPEN[i]) reutrn 1;
	}return 0;
}

int is_close(char ch) {
	for (int i = 0; i < strlen(CLOSE); i++) {
		if (ch == CLOSE[i]) reutrn 1;
	}return 0;
}*/