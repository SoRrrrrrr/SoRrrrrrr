//N= 1~15인 n-queens 함수 문제의 해의 개수를 구하는 프로그램
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int n, solutionCnt = 0;
int* cols; //체스판의 각 행에 대한 queen의 열을 저장하는 배열

//유망성 check
bool promising(int level);
void queens(int level);

int main() {
	for (n = 1; n < 15; n++) {
		cols = (int*)malloc(sizeof(int) * (n + 1));
		queens(1);//첫 번쨰 행부터 시작
		printf("%d ", solutionCnt);
		free(cols);
		solutionCnt = 0;//다음 n의 해 계산을 위해 초기화 해줘야 함
	}return 0;
}

//level ; 현재 노드의 레벨(즉, 행을 의미함)
//cols[]에 저장된 값들 간에는 서로 충돌이 없음이 보장되어 있음
//=> 마지막에 놓인 말(cols[level])이 이전에 놓인 말들(cols[i])과 충돌하는지만 검사하면 됨
bool promising(int level) {
	for (int i = 1; i < level; i++) {
		//동일 직선상 or 대각선상이면 
		if (cols[i] == cols[level] || abs(level - i) == abs(cols[level]) - cols[i)
			return false;
	}return true;
}

//가능한 해 탐색함
void queens(int level) {
	//마지막 행까지 선택 완료했다면
	if (level > n) {
		solutionCnt++;
		return;
	}
	//해당 level의 모든 열을 살펴본다
	for (int i = 1; i <= n; i++) {
		cols[level] = i;
		//유망한 열이면 다음 행도 계속해서 살펴봐라
		if (promising(level))
			queens(level + 1);
	}
}