//미로찾기 문제에서 모든 경로의 개수를 찾는 프로그램
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define MAX 100 
#define PATHWAY 0
#define WALL 1 
#define BLOCKED 2 //visited, 출구까지의 경로상에 있지 않음이 밝혀진 cell
#define PATH 3 //visited, 출구로 가는 경로가 될 가능성이 있는 cell

int n;
int maze[MAX][MAX];

int cnt_paths(int x, int y);

int main() {
	//file read
	FILE* fp = fopen("input6.txt", "r");
	fscanf(fp, "%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			fscanf(fp, "%d", &maze[i][j]);
	}
	fclose(fp);

	int cnt = cnt_paths(0, 0);
	printf("%d", cnt);
	return 0;
}

//해당 좌표에서 모든 방향으로의 경로를 recursion으로 탐색 후 sum 
int cnt_paths(int x, int y) {
	//can't move
	if (x < 0 || x >= n || y < 0 || y >= n || maze[x][y] != PATHWAY)return 0;
	//arrive at destination
	else if (x == n - 1 && y == n - 1) return 1;
	else {
		//방문 표시(유망성 있는 cell)
		maze[x][y] = PATH;
		//모든 방향에서의 경로 찾아서 합치기
		int sum_cnt = cnt_path(x - 1, y) + cnt_path(x, y + 1) + cnt_path(x + 1, y) + cnt_path(x, y - 1);
		//탐색 완료 했으면 다음 검색을 위해 다시 되돌려놓기
		maze[x][y] = PATHWAY;
		return cnt;
	}
}