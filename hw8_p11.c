//find luck number problem
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

bool is_luckyNum(int n, int k);

int main() {
	int n;
	scanf("%d", &n);

	if (is_luckyNum(n, 2))printf("True.\n");
	else printf("False.\n");
	return 0;
}

bool is_luckyNum(int n, int k) {
	//n�� k�� ������ �������� k�� ������ �ƴ�
	if (n % k == 0) return false;
	//n�� 1�̸� �����̴ٶ�� ��Ģ
	else if (k * k > n) return true;
	//n - n/k ; ���� ���� n���� k�� ���� ���� �A ��
	//��� ȣ�⿡�� ���� ���ڷ� �Ѿ �� n���� n/k�� �� ���ο� ����  ����Ͽ�
	//���� �ܰ��� ������ �˻��ϱ� ����
	else return is_luckyNum(n - n / k, k + 1);
}