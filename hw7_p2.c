//strcmp()�Լ��� recursion.ver�� ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(char* str1, char* str2);

int main() {
	char str1[100], str2[100];
	scanf("%s %s", str1, str2);
	int result = compare(str1, str2);
	printf("%d\n", result);
	return 0;
}

//���� �����ϴ� ���� �������� ��
int compare(char* str1, char* str2) {
	//�� �� ���� ���� => ����
	if (*str1 == '\0' && *str2 == '\0') return 0;
	//���̰� ���� �ٸ�
	//str1�� ���� ���� => str1�� �� ����
	else if (*str1 == '\0' && *str2 != '\0') return -1;
	//str2�� ���� ���� => str2�� �� ����
	else if (*str1 != '\0' && *str2 == '\0') return 1;
	//���ڰ� ���� ���� ���� ���
	if (*str1 != *str2) {
		if (*str1 < *str2) return -1;
		else if (*str1 > *str2) return 1;
	}
	return compare(str1 + 1, str2 + 1);
}