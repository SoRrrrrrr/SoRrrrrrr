//data는 오름차순으로 정렬되어 있음
//floor, ceiling function
//이진탐색 알고리즘 이용
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 1000

int floor(int data[], int start, int end, int k);
int ceiling(int data[], int start, int end, int k);

int main() {
	int data[MAX];
	int n, k, floor_result, ceiling_result;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)scanf("%d", &data[i]);
	scanf("%d", &k);
	floor_result = floor(data, 0, n - 1, k);
	ceiling_result = ceiling(data, 0, n - 1, k);
	printf("%d\n%d", floor_result, ceiling_result);
	return 0;
}

//k보다 작거나 같으면서 가장 큰 정수를 찾는 함수
int floor(int data[], int start, int end, int k) {
	int mid;
	if (start > end)return -1;
	mid = start + (end - start) / 2;
	//다음 값도 조건을 만족하면 다음 값을 return
	if (data[mid] <= k) {
		int next_data = floor(data, mid + 1, end, k);
		if (next_data != -1) //만족한다
			return next_data;
		return data[mid];
	}
	//data[mid] > k인 경우
	else return floor(data, start, mid - 1, k);
}

//k보다 크거나 같으면서 가장 작은 정수를 찾는 함수
int ceiling(int data[], int start, int end, int k) {
	int mid;
	if (start > end)return -1;
	mid = start + (end - start) / 2;
	//k보다 작으면 한 칸 뒤부터 다시 탐색
	if (data[mid] < k) return ceiling(data, mid + 1, end, k);
	//data[mid]<=k인 경우
	else {
		int next_data = ceiling(data, mid - 1, end, k);
		if (next_data != -1) return next_data;
		return data[mid];
	}
}
