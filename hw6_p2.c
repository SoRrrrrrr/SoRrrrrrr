//미로찾기 문제에서 입구(0,0) ~ 출구(N-1,N-1)까지 가는 경로들 중에 꺽인 횟수가 최소가 되는 경로 찾기
//경로의 꺽인 최소 횟수 출력
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
	int size;//저장된 데이터 개수
	int capacity;//배열 contents의 크기
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
	{-1,0},//북
	{0,1},//동
	{1,0},//남
	{0,-1}//서 
};

//BFS 알고리즘를 사용하여 미로를 탐색하고 벽을 피해 이동 가능한 최소 이동 횟수 계산
int find_min_turns(int maze[MAX][MAX], int n) {
	Queue q = create(n * n);
	//enqueue start point 
	Position start = { 0,0 };
	enqueue(q, start);
	maze[0][0] = 0; //해당 지점을 방문했음을 표시
	
	while (!is_empty(q)) {
		Position cur = dequeue(q);
		//if arrival, terminate function and return turns num
		if (cur.x == n - 1 && cur.y == 1) {
			destroy(q);
			return maze[cur.x][cur.y] - 1;
		}
		//현재 위치에서 4방향으로 이동하며 BFS 수행
		for (int dir = 0; dir < 4; dir++) {
			//각 방향으로 이동할 때, 해당 방향으로의 거리를 1~n-1까지 증가시키며 이동 가능한지 여부를 확인
			for (int dist = 1; dist < n; dist++) {
				int xx = cur.x + dist * offset[dir][0];
				int yy = cur.y + dist * offset[dir][1];
				//outside of the maze or hitting walls
				if (xx < 0 || xx >= n || yy < 0 || yy >= n || maze[xx][yy] == 1)
					break;
				//if movable
				//해당 위치를 enqueue하고, 그 위치까지의 최소 이동 횟수를 maze에 저장
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