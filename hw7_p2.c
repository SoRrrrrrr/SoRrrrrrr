//strcmp()함수를 recursion.ver로 구현
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

//끝에 도달하는 순서 기준으로 비교
int compare(char* str1, char* str2) {
	//둘 다 끝에 도달 => 같다
	if (*str1 == '\0' && *str2 == '\0') return 0;
	//길이가 서로 다름
	//str1이 먼저 도달 => str1이 더 빠름
	else if (*str1 == '\0' && *str2 != '\0') return -1;
	//str2이 먼저 도달 => str2이 더 빠름
	else if (*str1 != '\0' && *str2 == '\0') return 1;
	//문자가 서로 같지 않은 경우
	if (*str1 != *str2) {
		if (*str1 < *str2) return -1;
		else if (*str1 > *str2) return 1;
	}
	return compare(str1 + 1, str2 + 1);
}