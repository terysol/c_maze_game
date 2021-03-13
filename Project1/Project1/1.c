#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define SIZE 26
#define BACK 4

struct MStack
{
    int x;
    int y;
};

void initMap(int(*Maze)[SIZE]);
void displayMap(int(*Maze)[SIZE]);
void mazeStart(int(*Maze)[SIZE], struct MStack* mStack, int* top);
int currentPosition(int(*Maze)[SIZE], int* x, int* y);
void push(struct MStack* mStack, int* top, int x, int y);
struct MStack pop(struct MStack* mStack, int* top);
void mazeReStart(int(*Maze)[SIZE], struct MStack* mStack, int* top);

void gotoxy(int x, int y);
void textcolor(int color_number);

void main()
{
    int Maze[SIZE][SIZE];
    struct MStack mStack[SIZE * SIZE];
    int top = -1;

    initMap(Maze);
    displayMap(Maze);

    textcolor(14);
    gotoxy(0, SIZE + 1);
    puts(" ▤▤ 경로 학습 시작 ▤▤");
    system("pause");
    system("cls");

    mazeStart(Maze, mStack, &top);

    textcolor(10);
    gotoxy(0, SIZE + 1);
    puts(" ▤▤ 경로 학습 완료 ▤▤");
    system("pause");
    system("cls");

    initMap(Maze);
    displayMap(Maze);
    mazeReStart(Maze, mStack, &top);

    textcolor(11);
    gotoxy(0, SIZE + 1);
    puts(" ▤▤ 경로 학습 성공 ▤▤");
    system("pause");
}


void initMap(int(*Maze)[SIZE])
{
    int i, j;

    int MAP[SIZE][SIZE] =
    {
     {1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {1,0,1,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,1},
     {1,0,1,0,1,0,1,0,0,0,0,1,0,1,0,1,0,1,0,1},
     {1,0,1,0,1,0,1,1,1,1,1,1,0,1,1,1,0,1,1,1},
     {1,0,1,0,1,1,1,1,0,0,0,1,0,0,0,0,0,0,0,1},
     {1,0,1,0,0,1,0,0,0,1,1,1,1,0,1,1,1,1,0,1},
     {1,0,1,0,1,1,1,1,0,1,0,0,1,0,1,0,0,1,0,1},
     {1,0,1,0,0,0,0,1,0,1,1,0,1,0,1,0,1,1,0,1},
     {1,0,1,0,1,1,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
     {1,0,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1},
     {1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,1},
     {1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,0,0},
     {1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,1,1,1,0,1},
     {1,0,1,0,1,0,1,1,1,1,0,1,1,0,1,0,0,1,0,1},
     {1,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,1,1,1},
     {1,0,1,0,1,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1},
     {1,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,1},
     {1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,1},
     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            Maze[i][j] = MAP[i][j];
        }
    }
}

void displayMap(int(*Maze)[SIZE])
{
    int i, j;
    gotoxy(0, 0);
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            switch (Maze[i][j])
            {
            case 0:
                textcolor(8);
                printf("□");
                break;
            case 1:
                textcolor(11);
                printf("■");
                break;
            case 2:
                printf("  ");
                break;
            case 3:
            case BACK:   // pop
                textcolor(12);
                printf("★");
                break;
            default:
                break;
            }
        }
        puts("");
    }
}

void mazeStart(int(*Maze)[SIZE], struct MStack* mStack, int* top)
{
    int x, y;
    struct MStack tmpStack;
    tmpStack.x = -1;
    tmpStack.y = -1;

    while (1)
    {
        if (!currentPosition(Maze, &x, &y))
        {
            if (x == 11 && y == 19)                      // 도착
            {
                break;
            }
            if (x > 0 && Maze[x - 1][y] == 0)       // 상
            {
                if (Maze[x][y] == BACK) push(mStack, top, x, y);
                Maze[x][y] = 2;
                Maze[--x][y] = 3;
                push(mStack, top, x, y);
            }
            else if (x < SIZE - 1 && Maze[x + 1][y] == 0) // 하
            {
                if (Maze[x][y] == BACK) push(mStack, top, x, y);
                Maze[x][y] = 2;
                Maze[++x][y] = 3;
                push(mStack, top, x, y);
            }
            else if (y > 0 && Maze[x][y - 1] == 0)      // 좌
            {
                if (Maze[x][y] == BACK) push(mStack, top, x, y);
                Maze[x][y] = 2;
                Maze[x][--y] = 3;
                push(mStack, top, x, y);
            }
            else if (y < SIZE - 1 && Maze[x][y + 1] == 0) //우
            {
                if (Maze[x][y] == BACK) push(mStack, top, x, y);
                Maze[x][y] = 2;
                Maze[x][++y] = 3;
                push(mStack, top, x, y);
            }
            else
            {
                Maze[x][y] = 2;
                tmpStack = pop(mStack, top);
                x = tmpStack.x;
                y = tmpStack.y;
                Maze[x][y] = BACK;
            }
            displayMap(Maze);
        }
        Sleep(200);
    }
}

int currentPosition(int(*Maze)[SIZE], int* x, int* y)
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (Maze[i][j] == 3 || Maze[i][j] == BACK)
            {
                *x = i;
                *y = j;
                return 0;
            }
        }
    }
    return 1;
}

void push(struct MStack* mStack, int* top, int x, int y)
{
    if (*top < SIZE * SIZE - 1)
    {
        mStack[++ * top].x = x;
        mStack[*top].y = y;
    }
    else puts("Stack Overflow");
}

struct MStack pop(struct MStack* mStack, int* top)
{
    if (*top < 0)
    {
        puts("Stack Underflow");
        mStack[SIZE * SIZE].x = -1;
        mStack[SIZE * SIZE].y = -1;
        return mStack[SIZE * SIZE];
    }
    else return mStack[(*top)--];
}
void mazeReStart(int(*Maze)[SIZE], struct MStack* mStack, int* top)
{
    int i;
    Maze[0][1] = 2;
    for (i = 1; i <= *top; i++)
    {
        Maze[mStack[i - 1].x][mStack[i - 1].y] = 2;
        Maze[mStack[i].x][mStack[i].y] = 3;
        Sleep(200);
        displayMap(Maze);
    }
}
void gotoxy(int x, int y)
{
    COORD cd;
    cd.X = x;
    cd.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}

void textcolor(int color_number)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
