//data�� ������������ ���ĵǾ� ����
//floor, ceiling function
//����Ž�� �˰��� �̿�
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

//k���� �۰ų� �����鼭 ���� ū ������ ã�� �Լ�
int floor(int data[], int start, int end, int k) {
	int mid;
	if (start > end)return -1;
	mid = start + (end - start) / 2;
	//���� ���� ������ �����ϸ� ���� ���� return
	if (data[mid] <= k) {
		int next_data = floor(data, mid + 1, end, k);
		if (next_data != -1) //�����Ѵ�
			return next_data;
		return data[mid];
	}
	//data[mid] > k�� ���
	else return floor(data, start, mid - 1, k);
}

//k���� ũ�ų� �����鼭 ���� ���� ������ ã�� �Լ�
int ceiling(int data[], int start, int end, int k) {
	int mid;
	if (start > end)return -1;
	mid = start + (end - start) / 2;
	//k���� ������ �� ĭ �ں��� �ٽ� Ž��
	if (data[mid] < k) return ceiling(data, mid + 1, end, k);
	//data[mid]<=k�� ���
	else {
		int next_data = ceiling(data, mid - 1, end, k);
		if (next_data != -1) return next_data;
		return data[mid];
	}
}
