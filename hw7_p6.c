//�̷�ã�� �������� ��� ����� ������ ã�� ���α׷�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#define MAX 100 
#define PATHWAY 0
#define WALL 1 
#define BLOCKED 2 //visited, �ⱸ������ ��λ� ���� ������ ������ cell
#define PATH 3 //visited, �ⱸ�� ���� ��ΰ� �� ���ɼ��� �ִ� cell

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

//�ش� ��ǥ���� ��� ���������� ��θ� recursion���� Ž�� �� sum 
int cnt_paths(int x, int y) {
	//can't move
	if (x < 0 || x >= n || y < 0 || y >= n || maze[x][y] != PATHWAY)return 0;
	//arrive at destination
	else if (x == n - 1 && y == n - 1) return 1;
	else {
		//�湮 ǥ��(������ �ִ� cell)
		maze[x][y] = PATH;
		//��� ���⿡���� ��� ã�Ƽ� ��ġ��
		int sum_cnt = cnt_path(x - 1, y) + cnt_path(x, y + 1) + cnt_path(x + 1, y) + cnt_path(x, y - 1);
		//Ž�� �Ϸ� ������ ���� �˻��� ���� �ٽ� �ǵ�������
		maze[x][y] = PATHWAY;
		return cnt;
	}
}