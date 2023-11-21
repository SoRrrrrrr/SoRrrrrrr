//터미널에 아래 명령어 쳐서 실행하기
// gcc f_merger.c -o f_merger
// ./f_merger test1.txt test2.txt .. output.txt
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_WORD 100000//단어 최대 수

int main(int argc, char* argv[]){
	char** words = (char**)malloc(sizeof(char*)*MAX_WORD);//모든 파일의 단어를 한번에 저장할 배열을 가리키는 포인터
	int idx = 0;//words의 인덱스
	FILE* fp_in;//입력할 파일
	
	//argv[0]에는 프로그램 실행경로가 들어가므로 index = 1부터 봐야 함 
	//그리고 마지막 값은 출력 파일이므로 argc-2까지 읽어야 함
	for(int i = 1; i < argc - 1; i++){
		fp_in = fopen(argv[i], "r");
		if(fp_in == NULL){
			perror("file open failed.");
			return 1;
		}
		//배열에 단어를 저장할 공간이 남아있지 않은 경우(다 찬 경우)
		//배열을 2배해서 재할당해줌
		if(idx == MAX_WORD)
			words = (char**)realloc(words, MAX_WORD*2*sizeof(char*));
			
		char word[100];
		//파일에서 단어 읽어서 배열에 저장
		while(fscanf(fp_in,"%s",word)!=EOF)
			words[idx++]=strdup(word);
	}fclose(fp_in);
		
	//알파벳 순서로 정렬
	char tmp[100];
	for(int i = 0; i<idx - 1; i++){
		for(int j = i + 1; j < idx; j++){
			if(strcasecmp(words[i],words[j]) > 0){//대소문자 구분없이 비교해야하기에 strcasecmp 함수 사용
				strcpy(tmp, words[i]);
				strcpy(words[i], words[j]);
				strcpy(words[j], tmp);
			}
		}
	}
	
	//출력 파일에 저장
	FILE* fp_out = fopen(argv[argc - 1], "w");//마지막 입력한 파일=출력 파일
	if(fp_out == NULL){
			perror("file open failed.");
			return 1;
		}
	for(int i=0;i<idx;i++){
		fprintf(fp_out,"%s ", words[i]);
	}fclose(fp_out);
	return 0;
}
