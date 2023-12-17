//DFS 사용함
/*#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100
#define BACKGROUND 0//it means white 
#define IMAGE 1//it means black 
#define VISITED 2//already visited 
#define BACKTRACKED 3//turn back after visit

typedef struct node {
    int dir;
    struct node* next;
}Node;

typedef struct {
    Node* top;
}Stack;

//struct of position 
//x가 수직이고, y가 수평임( 즉 반대로 생각해야한다 ~ )
typedef struct pos {
    int x, y; //좌표
}Position;

//이동시 좌표 변화량
int offset[8][2] = {
    {-1,0};//북(dir=0)
    {0,1};//동(dir=1)
    {1,0};//남(dir=2)
    {0,-1};//서(dir=3)
    {-1,1};//북동(dir=4)
    {1,1};//남동(dir=5)
    {1,-1};//남서(dir=6)
    {-1,-1};//북서(dir=7)
};

int grid[MAX][MAX] = { 0 };
int n = 0, row = 0, col = 0;//n : gird size

//--------------stack functions-----------------
static void terminate(const char* errmsg) {
    printf("%s\n", errmsg);
    exit(1);
}
int is_empty(Stack* s) {
    return (s->top == NULL);
}
void make_empty(Stack* s) {
    s->top = NULL;
}
Stack create_stack(void) {
    Stack* s = (Stack*)malloc(sizeof(Stack));
    s->top = NULL;
    return *s;
}
void push(Stack* s, int dir) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->dir = dir;
    tmp->next = s->top;
    s->top = tmp;
}
int pop(Stack* s) {
    Node* temp = s->top;
    int data = temp->dir;
    s->top = s->top->next;
    free(temp);
    return data;
}

//position functions
Position move_to(Position pos, int dir) {
    Position next;
    next_x = pos.x + offset[dir][0];
    next_y = pos.y + offset[dir][1];
    return next;
}

//해당 방향으로 이동했을 때, 해당 픽셀이 이미지 픽셀인지 판단 후 bool값 반환
bool movable(Position pos, int dir) {
    //-1,0 이동(북)
    if (dir == 0 && (pos.x - 1 >= 0) && grid[pos.x - 1][pos.y] == 1)
        return true;
    //0,1 이동(동)
    else if (dir == 1 && (pos.y + 1 <= n) && maze[pos.x][pos.y + 1] == 1)
        return true;
    //1,0 이동(남)
    else if (dir == 2 && (pos.x + 1 <= n) && maze[pos.x + 1][pos.y] == 1)
        return true;
    //0,-1 이동(서)
    else if (dir == 3 && (pos.y - 1 >= 0) && maze[pos.x][pos.y - 1] == 1)
        return true;
    //-1, 1 이동(북동)
    else if (dir == 5 && (pos.x - 1 >= 0 && pos.y + 1 <= n) && maze[pos.x - 1][pos.y + 1] == 1)
        return true;
    //1, 1 이동(남동)
    else if (dir == 6 && (pos.x + 1 <= n && pos.y + 1 <= n) && maze[pos.x + 1][pos.y + 1] == 1)
        return true;
    //1, -1 이동(남서)
    else if (dir == 7 && (pos.x + 1 <= n && pos.y - 1 >= 0) && maze[pos.x + 1][pos.y - 1] == 1)
        return true;
    //-1, -1 이동(북서)
    else if (dir == 4 && (pos.x - 1 >= 0 && pos.y - 1 >= 0) && maze[pos.x - 1][pos.y - 1] == 1)
        return true;
    else
        return false;
}

//하나의 이미지를 나타내는 데이터 파일을 읽어서 그 이미지에 포함된 모든 컴포넌트의 크기 출력
int main() {
    FILE* fp = fopen("input.txt", "r");
    //USE DFS algorithm 
    //The process repeats for each maze in the input file
    for (int x = 0; x < num; x++) {
        //read file
        fscanf(fp, "%d", n);
        for (row = 0; row < n; row++) {
            for (col = 0; col < n; col; col++)
                fscanf(fp, "%d", &grid[row][col]);
        }
        //DFS
        for (row = 0; row < n; row++) {
            for (col = 0; col < n; col; col++) {
                //if it's IMAGE(1)
                if (grid[row][col] == 1) {
                    int cnt = 1;//컴포넌트 개수
                    //각 position에서 movable한 dir를 저장하는 역할
                    Stack s = create_stack();
                    Position cur;//current position
                    cur.x = row; cur.y = col;
                    int init_dir = 0;

                    while (1) {
                        //Mark the curr position as visited
                        grid[cur.x][cur.y] = VISITED;

                        int dir = 0;
                        bool forwarded = false;//flag to check if success to forward move 

                        //find a movable direction through 8 directions
                        for (dir = init_dir; dir < 8; dir++) {
                            //if possible to move in the current position
                            if (movable(cur, dir)) {
                                push(&s, dir);
                                cnt++;//component size++
                                cur = move_to(cur, dir);
                                forwarded = true;
                                init_dir = 0;
                                break;
                            }
                        }
                        //impossoble in forward move => backtracking
                        if (!forwarded) {
                            //if the stack is empty, one connected component is colpleted
                            if (is_empty(&s)) {
                                printf("%d ", cnt);
                                break;
                            }
                            grid[cur.x][cur.y] = BACKTRACKED;

                            int popped_dir = pop(&s);
                            //opposite direction of the last move, ensuring that the algorithm backtracks correctly.
                            int reverse_dir = (popped_dir + 2) % 8;

                            //Move to the position in the reverse direction
                            cur = move_to(cur, reverse_dir);
                            init_dir = popped_dir;
                        }
                    }
                }
            }
        }printf("\n");
    }fclose(fp);
    return 0;
}*/