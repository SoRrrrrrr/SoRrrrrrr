//회문(palindrome)인지 판별해주는 프로그램 구현
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LEN 100

bool is_palindrome(char* str, int left, int right);

int main() {
	char word[MAX_LEN];
	int len;
	scanf("%d", &word);
	len = strlen(word);
	bool result = is_palindrome(word, 0, len - 1);
	if (result == true) printf("True.\n");
	else printf("False\n");
	return 0;
}

bool is_palindrome(char* str, int left, int right) {
	if (left >= right)return true;
	else if (str[left] != str[right])return false;
	else is_palindrome(str, left + 1, right - 1);
}