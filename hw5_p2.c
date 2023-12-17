//명령어를 입력한 후 각 명령어에 맞는 연산 후 결과 출력
//stack에 대한 create, push, pop, list, exit 함수 구현
/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACK 100

typedef struct node {
	char* data;
	struct node* next;
}Node;

typedef struct {
	char* name;//stack name
	Node* top;
}StackType;

//save stacks
int idx = 0;//array "stacks" index
StackType* stacks[MAX_STACK];

static void terminate(const char* errmsg);
StackType* create_stack(char* name);
int is_empty(StackType* s);
StackType* search(char* name);
void push(char* stack_name, char* data);
char* pop(StackType* s);
void list(StackType* s);

int main() {
	char command[100], arg1[100], arg2[100];

	while (1) {
		printf("$ ");
		scanf("%s", command);
		if (strcmp(command, "create") == 0) {
			scanf("%s", arg1);
			stack[idx] = create_stack(arg1);
			idx++;
		}

		else if (strcmp(command, "push") == 0) {
			scanf("%s", arg1); //stack name
			scanf("%s", arg2); //input data
			if (arg1 == NULL || arg2 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			push(arg1, arg2);
		}
		else if (strcmp(command, "pop") == 0) {
			scanf("%s", arg1); //stack name
			printf("%s", pop(search(arg1));
		}
		else if (strcmp(command, "list") == 0) {
			scanf("%s", arg1); //stack name
			list(search(arg1));
		}
		else if (strcmp(command, "exit") == 0) break;
		printf("\n");
	} return 0;
}

static void terminate(const char* errmsg) {
	printf("%s", errmsg);
	exit(1);
}

StackType* create_stack(char* name) {
	StackType* s = (StackType*)malloc(sizeof(StackType));
	if (s == NULL) terminate("Error in Create : Stack could not be created.\n");
	s->top = NULL;
	s->name = _strdup(name);
	return s;
}

int is_empty(StackType* s) {
	return s->top = NULL;
}

//해당 이름의 stack을 찾는 함수
StackType* search(char* name) {
	for (int i = 0; i < idx; i++) {
		if (stacks[i] != NULL && strcmp(stacks[i]->name, name) == 0)
			return stack[i];
	}return NULL;
}

//search함수 이용해서 바꿔보기
void push(char* stack_name, char* data) {
	for (int i = 0; i < idx; i++) {
		if (strcmp(stacks[i]->name, stack_name) == 0) {
			Node* cur_stack = stacks[i]->top;
			Node* new_node = (Node*)malloc(sizeof(Node));
			new_node->data = _strdup(data);
			new_node->next = stacks[i]->top;
			stacks[i]->top = new_node;
		}
	}
}

char* pop(StackType* s) {
	if (is_empty(s))
		terminate("Error in pop : Stack is empty.\n");
	Node* old_node = s->top;
	char* old_data = old_node->data;
	s->top = old_node->next;
	free(old_node);
	return old_data;
}

void list(StackType* s) {
	if (s == NULL) terminate("stack not found.\n");
	Node* curr = s->top;
	while (curr != NULL) {
		printf("%s\n", curr->data);
		curr = curr->next;
	}
}*/