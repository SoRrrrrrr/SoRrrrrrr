//양의 정수 k를 입력받아서 맨 처음 어떤 칸에 풀을 심으면 (인접 white칸으로 번져나가는데 1년 걸림)
//k년 후 가장 많은 수의 칸에 풀이 자라게 되는지를 계산하여 해당 자리& 그 칸 수를 출력
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INIT_CAPACITY 100 //초기 q 배열 크기
#define MAX 100
#define WHITE 0 //흰색 칸
#define GREY 1 //회색 칸

typedef int Item;
typedef struct queue_type* Queue;

struct queue_type {
	Item* contents;//배열
	//size : 저장된 데이터 개수, capacity : 배열 contents의 크기
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
	int cnt = 0; //최대 풀 개수
	//x, y 좌표 변화량(우, 좌, 하, 상)
	int dx[] = { 1,-1,0,0 };
	int dy[] = { 0,0,1,-1 };
	//capacity = n*n
	Queue q = create(n * n);
	//enqueue the start indx(queue 배열이 1차원이므로 인덱스를 start_X*n(행)+start_y로 계산한다)
	enqueue(q, start_x * n + start_y);
	//----------------BFS-----------------------
	while (!is_empty(q) && years > 0) {
		int cur_size = get_size(q);
		for (int i = 0; i < cur_size; i++) {
			//change current index to 좌표
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

	//가장 최대가 되는 start point 
	int max_cnt = 0;
	int max_x = 0;
	int max_y = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			//if movable point 
			if (maze[i][j] == 0) {
				//cp maze to grid
				//bfs 과정에서 growable인 경우, 배열 maze값이 변경될 수 있으므로
				//다른 point에서의 bfs연산에 영향을 끼치지 않기 위해 cp하여 사용해야 함
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