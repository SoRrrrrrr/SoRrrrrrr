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
	//n이 k로 나누어 떨어지면 k는 행운수가 아님
	if (n % k == 0) return false;
	//n이 1이면 행운수이다라는 규칙
	else if (k * k > n) return true;
	//n - n/k ; 현재 숫자 n에서 k로 나눈 몫을 뺸 값
	//재귀 호출에서 다음 숫자로 넘어갈 때 n에서 n/k를 뺀 새로운 값을  사용하여
	//다음 단계의 행운수를 검사하기 위함
	else return is_luckyNum(n - n / k, k + 1);
}