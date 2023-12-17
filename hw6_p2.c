//�̷�ã�� �������� �Ա�(0,0) ~ �ⱸ(N-1,N-1)���� ���� ��ε� �߿� ���� Ƚ���� �ּҰ� �Ǵ� ��� ã��
//����� ���� �ּ� Ƚ�� ���
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INIT_CAPACITY 100
#define MAX 100

typedef struct pos {
	int x, y;
}Position;

typedef struct queue_type* Queue;
struct queue_type {
	Position* contents;
	int front, rear;
	int size;//����� ������ ����
	int capacity;//�迭 contents�� ũ��
};
void terminate(const char* errmsg) {
	printf("%s\n", errmsg);
	exit(1);
}
Queue create(int capacity) {
	Queue q = (Queue)malloc(sizeof(struct queue_type));
	if (q == NULL) terminate("Error in create : queue couldn't be created.");
	q->contents = (Position*)malloc(capacity * sizeof(Position));
	if (q->contents == NULL) {
		free(q);
		terminate("Error in create : queue couldn't be created.");
	}
	q->front = 0;
	q->rear = -1;
	q->size = 0;
	q->capacity = capacity;
	return q;
}
void destroy(Queue q)
{
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
void enqueue(Queue q, Position data) {
	if (is_full(q))
		terminate("queue is full.\n");
	q->rear = (q->rear + 1) % q->capacity;
	q->contents[q->rear] = data;
	q->size++;
}
Position dequeue(Queue q) {
	if (is_empty(q)) terminate("Error in dequeue : queue is empty.");
	Position result = q->contents[q->front];
	q->front = (q->front + 1) % q->capacity;
	q->size--;
	return result;
}
int get_size(Queue q) {
	return q->size;
}
//----------------------------------queue functions----------------------------
int maze[MAX][MAX];
int n;
int offset[4][2]{
	{-1,0},//��
	{0,1},//��
	{1,0},//��
	{0,-1}//�� 
};

//BFS �˰��� ����Ͽ� �̷θ� Ž���ϰ� ���� ���� �̵� ������ �ּ� �̵� Ƚ�� ���
int find_min_turns(int maze[MAX][MAX], int n) {
	Queue q = create(n * n);
	//enqueue start point 
	Position start = { 0,0 };
	enqueue(q, start);
	maze[0][0] = 0; //�ش� ������ �湮������ ǥ��
	
	while (!is_empty(q)) {
		Position cur = dequeue(q);
		//if arrival, terminate function and return turns num
		if (cur.x == n - 1 && cur.y == 1) {
			destroy(q);
			return maze[cur.x][cur.y] - 1;
		}
		//���� ��ġ���� 4�������� �̵��ϸ� BFS ����
		for (int dir = 0; dir < 4; dir++) {
			//�� �������� �̵��� ��, �ش� ���������� �Ÿ��� 1~n-1���� ������Ű�� �̵� �������� ���θ� Ȯ��
			for (int dist = 1; dist < n; dist++) {
				int xx = cur.x + dist * offset[dir][0];
				int yy = cur.y + dist * offset[dir][1];
				//outside of the maze or hitting walls
				if (xx < 0 || xx >= n || yy < 0 || yy >= n || maze[xx][yy] == 1)
					break;
				//if movable
				//�ش� ��ġ�� enqueue�ϰ�, �� ��ġ������ �ּ� �̵� Ƚ���� maze�� ����
				if (maze[xx][yy] == 0) {
					Position next = { xx,yy };
					enqueue(q, next);
					maze[xx][yy] = maze[cur.x][cur.y] + 1;
				}
				else break;
			}
		}
	}
	//fail=> no path to destination
	destroy(q);
	return -1;
}

int main() {
	FILE* fp = fopen("input2.txt", "r");
	fscanf(fp, "%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			fscanf(fp, "%d", &maze[i][j]);
	}
	fclose(fp);

	int min_turns = find_min_turns(maze, n);
	if (min_turns != -1) printf("%d\n", min_turns);
	else printf("No path found.\n");
	return 0;
}