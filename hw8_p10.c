//hamming distance ���� ; ���̰� ���� �� ���������� ���� �ٸ� ��Ʈ�� ����
//hamming distance : k, bit length : n 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void hamming(char* str, int n, int k, int idx) {
	//hamming distance == 0
	if (k == 0) {
		printf("%s", str);
		return;
	}
	//������ ���̸�ŭ �� Ž��(?) �Ϸ�
	if (idx == n) return;
	//���� ���ڿ����� k-1�� ���ڿ� ����
	//str[idx]=='0'�̸� '1'�� , '1'�̸� '0'���� ����
	str[idx] = (str[idx] = '0') ? '1' : '0';
	hamming(str, n, k - 1, idx + 1);
	//���� ��Ʈ�� ���� => ���� ��Ʈ�� �̵��Ͽ� �ٸ� ��ġ�� ��Ʈ�� �����ϸ鼭 ���ϴ� ���ڿ� ����
	str[idx] = (str[idx] = '0') ? '1' : '0';
	hamming(str, n, k, idx + 1);
}

void main() {
	int n, k;
	char binaryNum[17];
	scanf("%d %d", &n, &k);
	scanf("%d", binaryNum);

	hamming(bunaryNum, n, k, 0);
	return 0;
}