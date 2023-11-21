//모든 파일의 단어를 한꺼번에 배열에 저장한 후 프로세스가 반씩 나누어서 정렬
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/file.h>
#define MAX_WORD 100000 // 단어 최대 수

void sorting(char** words,int start,int last);

int main(int argc, char *argv[]) {
	// 모든 파일의 단어를 한번에 저장할 배열을 가리키는 포인터
    char **words = (char **)malloc(sizeof(char *) * MAX_WORD); 
    int idx = 0;// words의 인덱스
    FILE* fp_in;

    //read files
	for (int i = 1; i < argc - 1; i++) {
        fp_in = fopen(argv[i], "r");
        if (fp_in == NULL) {
            perror("file open failed.");
            return 1;
        }
        // 배열에 단어를 저장할 공간이 남아있지 않은 경우(다 찬 경우) 배열 크기 늘려서 재할당
        if (idx == MAX_WORD)
            words = (char **)realloc(words, MAX_WORD * 2 * sizeof(char *));
		// 파일에서 단어 읽어서 배열에 저장
		char word[100];
        while (fscanf(fp_in, "%s", word) != EOF)
            words[idx++] = strdup(word);
		fclose(fp_in);
    }

    // fork()를 이용하여 두 개의 프로세스 생성
    pid_t pid = fork();
	if (pid < 0) {
        perror("forking failed.\n");
        return 1;
    }
	// child process
	else if (pid == 0) {
        // set file lock
        FILE *fp_out = fopen(argv[argc - 1], "a");
		flock(fileno(fp_out), LOCK_EX);
        if (fp_out == NULL) {
            perror("file open failed.");
            return 1;
        }
        // 자식 프로세스는 배열의 뒷부분을 정렬
		sorting(words,idx/2,idx);
        // write results
		for (int i = idx/2; i <= idx - 1; i++){
			fprintf(fp_out, "%s ", words[i]);
			fprintf(fp_out,"\n");
		} 
		flock(fileno(fp_out), LOCK_UN);	
		fclose(fp_out);
    } 
	// parent process
	else {
        FILE *fp_out = fopen(argv[argc - 1], "w"); 
		flock(fileno(fp_out), LOCK_EX);
        if (fp_out == NULL) {
            perror("file open failed.");
            return 1;
        }
        // 부모 프로세스는 배열의 앞부분을 정렬
        sorting(words,0,idx/2);
         for (int i = 0; i <= idx/2 - 1; i++) {
			fprintf(fp_out, "%s ", words[i]);
			fprintf(fp_out,"\n"); 
		 }
        // unlock the file
		flock(fileno(fp_out), LOCK_UN);
        fclose(fp_out);
    }
	free(words);
    return 0;
}

void sorting(char** words,int start,int last){
	for (int i = start; i < last - 1; i++) {
		for (int j = i + 1; j < last; j++) {
			if (strcasecmp(words[i], words[j]) > 0) {
				char tmp[100];
                strcpy(tmp, words[i]);
                strcpy(words[i], words[j]);
                strcpy(words[j], tmp);
            }
        }
    }	
}
