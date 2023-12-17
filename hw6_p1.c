//���� ���� k�� �Է¹޾Ƽ� �� ó�� � ĭ�� Ǯ�� ������ (���� whiteĭ���� ���������µ� 1�� �ɸ�)
//k�� �� ���� ���� ���� ĭ�� Ǯ�� �ڶ�� �Ǵ����� ����Ͽ� �ش� �ڸ�& �� ĭ ���� ���
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INIT_CAPACITY 100 //�ʱ� q �迭 ũ��
#define MAX 100
#define WHITE 0 //��� ĭ
#define GREY 1 //ȸ�� ĭ

typedef int Item;
typedef struct queue_type* Queue;

struct queue_type {
	Item* contents;//�迭
	//size : ����� ������ ����, capacity : �迭 contents�� ũ��
	int front, rear, size, capacity;
};

//-------------------------------------- queue's functions ----------------------------------------------
void terminate(const char* errmsg) {
	printf("%s\n", errmsg);
	exit(1);
}

Queue create(Item capacity) {
	Queue q = (Queue)malloc(sizeof(struct queue_type));
	if (q == NULL) terminate("Error in create : Queue couldn't be created.\n");
	q->contents = (Item*)malloc(sizeof(Item) * capacity);
	if (q->contents == NULL) {
		free(q);
		terminate("Error in create : queue's contents couldn't be created.\n");
	}
	q->front = 0;
	q->rear = -1;
	q->size = 0;
	q->capacity = capacity;
	return q;
}

void destroy(Queue q) {
	free(q->contents);
	free(q);
}

void make_empty(Queue q) {
	q->front = 0;
	q->rear = -1;
	q->size = 0;
}

bool is_empty(Queue q) {
	return q->size == 0;
}

bool is_full(Queue q) {
	return q->size == q->capacity;
}

void enqueue(Queue q, Item data) {
	if (is_full(q)) terminate("Queue is full.");
	q->rear = (q->rear + 1) % q->capacity;
	q->contents[q->rear] = data;
	q->size++;
}

Item dequeue(Queue q) {
	if (is_empty(q)) terminate("Error in dequeue : queue is empty.");
	Item result = q->contents[q->front];
	q->front = (q->front + 1) % q->capacity;
	q->size--;
	return result;
}

Item peek(Queue q) {
	if (is_empty(q)) terminate("Error in peek : queue is empty.");
	return q->contents[q->front];
}

int get_size(Queue q) {
	return q->size;
}
//-------------------------------------- problem's functions ----------------------------------------------
int n; //size of maze
int visited[MAX][MAX];

int max_growth(int maze[MAX][MAX], int n, int start_x, int start_y, int years) {
	int cnt = 0; //�ִ� Ǯ ����
	//x, y ��ǥ ��ȭ��(��, ��, ��, ��)
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };
	//capacity = n*n
	Queue q = create(n * n);
	//enqueue the start indx(queue �迭�� 1�����̹Ƿ� �ε����� start_X*n(��)+start_y�� ����Ѵ�)
	enqueue(q, start_x * n + start_y);
	//----------------BFS-----------------------
	while (!is_empty(q) && years > 0) {
		int cur_size = get_size(q);
		for (int i = 0; i < cur_size; i++) {
			//change current index to ��ǥ
			int cur_idx = dequeue(q);
			int x = cur_idx / n;//row
			int y = cur_idx % n;//col
			//check growable in 4 directions
			for (int j = 0; j < 4; j++) {
				int pos_x = x + dx[j];
				int pos_y = y + dy[j];
				//if movable 
				if (pos_x >= 0 && pos_x < n && pos_y >= 0 && pos_y < n && maze[pos_x][pos_y] == 0) {
					enqueue(q, pos_x * n + pos_y);
					maze[pos_x][pos_y] = 1;
					cnt++;
				}
			}
		}years--;
	}destroy(q);
	return cnt;
}

int main() {
	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL) terminate("file open failed.");
	int years;
	int maze[MAX][MAX];
	//read maze
	fscanf(fp, "%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			fscanf(fp, "%d", &maze[i][j]);
	}fscanf(fp, "%d", &years);
	fclose(fp);

	//���� �ִ밡 �Ǵ� start point 
	int max_cnt = 0;
	int max_x = 0;
	int max_y = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//if movable point 
			if (maze[i][j] == 0) {
				//cp maze to grid
				//bfs �������� growable�� ���, �迭 maze���� ����� �� �����Ƿ�
				//�ٸ� point������ bfs���꿡 ������ ��ġ�� �ʱ� ���� cp�Ͽ� ����ؾ� ��
				int grid[MAX][MAX];
				for (int a = 0; a < n; a++) {
					for (int b = 0; b < n; b++)
						grid[a][b] = maze[a][b];
				}
				int cur_cnt = max_growth(grid, n, i, j, years);
				if (cur_cnt > max_cnt) {
					max_cnt = cur_cnt;
					max_x = i;
					max_y = j;
				}
			}
		}
	}
	printf("%d %d\n", max_x, max_y);
	printf("%d\n", max_cnt);
	return 0;
}