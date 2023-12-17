//2-sum (오름차순으로 정렬된 n개의 서로 다른정수, 정수 k
//N개의 정수들 중에서 합이 K가 되는 정수 쌍의 개수
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000

int two_sum(int data[], int k, int start, int end);

int main() {
	int data[MAX];
	int N, K;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) 
		scanf("%d", &data[i]);
	scanf("%d", &K);
	int start = 0, end = N - 1;
	int sum_cnt = two_sum(data, K, start, end);
	printf("%d", sum_cnt);
	return 0;
}

int two_sum(int data[], int k, int start, int end) {
	int cnt = 0;
	int sum = data[start] + data[end];
	if (start >= end)return cnt;
	if (sum == K) {
		cnt++;
		return cnt + two_sum(data, K, start + 1, end - 1);
	}
	else if (sum < K) return two_sum(data, K, start + 1, end);
	//sum > K
	else return two_sum(data, K, start, end - 1);
}