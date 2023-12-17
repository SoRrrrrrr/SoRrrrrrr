//N= 1~15�� n-queens �Լ� ������ ���� ������ ���ϴ� ���α׷�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int n, solutionCnt = 0;
int* cols; //ü������ �� �࿡ ���� queen�� ���� �����ϴ� �迭

//������ check
bool promising(int level);
void queens(int level);

int main() {
	for (n = 1; n < 15; n++) {
		cols = (int*)malloc(sizeof(int) * (n + 1));
		queens(1);//ù ���� ����� ����
		printf("%d ", solutionCnt);
		free(cols);
		solutionCnt = 0;//���� n�� �� ����� ���� �ʱ�ȭ ����� ��
	}return 0;
}

//level ; ���� ����� ����(��, ���� �ǹ���)
//cols[]�� ����� ���� ������ ���� �浹�� ������ ����Ǿ� ����
//=> �������� ���� ��(cols[level])�� ������ ���� ����(cols[i])�� �浹�ϴ����� �˻��ϸ� ��
bool promising(int level) {
	for (int i = 1; i < level; i++) {
		//���� ������ or �밢�����̸� 
		if (cols[i] == cols[level] || abs(level - i) == abs(cols[level]) - cols[i)
			return false;
	}return true;
}

//������ �� Ž����
void queens(int level) {
	//������ ����� ���� �Ϸ��ߴٸ�
	if (level > n) {
		solutionCnt++;
		return;
	}
	//�ش� level�� ��� ���� ���캻��
	for (int i = 1; i <= n; i++) {
		cols[level] = i;
		//������ ���̸� ���� �൵ ����ؼ� �������
		if (promising(level))
			queens(level + 1);
	}
}