//hamming distance 문제 ; 길이가 같은 두 이진수열간 서로 다른 비트의 개수
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
	//이진수 길이만큼 다 탐색(?) 완료
	if (idx == n) return;
	//원래 문자열에서 k-1인 문자열 생성
	//str[idx]=='0'이면 '1'로 , '1'이면 '0'으로 생성
	str[idx] = (str[idx] = '0') ? '1' : '0';
	hamming(str, n, k - 1, idx + 1);
	//원래 비트로 복원 => 다음 비트로 이동하여 다른 위치의 비트를 변경하면서 원하는 문자열 생성
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