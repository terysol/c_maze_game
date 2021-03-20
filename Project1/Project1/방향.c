 #include<stdio.h>
#include<windows.h>
#include<time.h>

#define MAX 10   //MAX를 10으로 정의
#define LEFT 75 //확장키
#define RIGHT 77 //kernel에게 아스키 코드로 인식못하게 먼저 다른 숫자(224)를 보낸 다음 해당 숫자보내면 방향키로 인식
#define UP 72
#define DOWN 80

typedef struct hero
{

	int x, y;

}HERO;

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
} //API 함수중 하나//커서의 위치를 이동시켜준다.

HERO roro = { 4,4 };
int map[MAX][MAX] =
{
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,0,0,1},
	{1,0,1,0,1,0,1,0,0,1},
	{1,0,1,1,0,0,1,0,0,1},
	{1,0,0,0,0,1,0,1,0,0},
	{1,1,0,0,0,0,0,1,0,1},
	{1,0,0,1,0,0,1,1,0,1},
	{1,0,1,0,0,0,0,0,1,1},
	{1,0,0,0,1,0,1,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};
void move() {
	if (kbhit())   //kbhit() =>키보드의 입력을 감지하는 함수 
	{
		gotoxy(roro.x, roro.y);//이전의 좌표로가서
		printf(" ");//이전의 위치를 지워라

		switch (getch()) // 벽돌 만나면 더 이상 이동하지 않고 그 외에는 움직이는 코드
		{
		case LEFT:
			if (map[roro.y][roro.x / 2 - 1] > 0)//x는 1/2칸만큼씩만 움직이므로 roro.x/2.
			{
				break;
			}
			roro.x -= 2;
			break;
		case RIGHT:
			if (map[roro.y][roro.x / 2 + 1] > 0)
			{
				break;
			}
			roro.x += 2;
			break;
		case UP:
			if (map[roro.y - 1][roro.x / 2] > 0)
			{
				break;
			}
			roro.y -= 2;
			break;
		case DOWN:
			if (map[roro.y + 1][roro.x / 2] > 0)
			{
				break;
			}
			roro.y += 2;
			break;
		}
		gotoxy(roro.x, roro.y);
		printf("●");
	}
}
int main()
{
	int i, j;
	
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			if (map[i][j] == 1)
			{
				printf("◇");
			}
			else if (map[i][j] == 0)
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	gotoxy(roro.x, roro.y); // x,y로 커서 이동
	printf("●"); //그 자리에 '+' 출력
	while (1)
	{
		move();
	}
	return 0;
}