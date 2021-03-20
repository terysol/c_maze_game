 #include<stdio.h>
#include<windows.h>
#include<time.h>

#define MAX 10   //MAX�� 10���� ����
#define LEFT 75 //Ȯ��Ű
#define RIGHT 77 //kernel���� �ƽ�Ű �ڵ�� �νĸ��ϰ� ���� �ٸ� ����(224)�� ���� ���� �ش� ���ں����� ����Ű�� �ν�
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
} //API �Լ��� �ϳ�//Ŀ���� ��ġ�� �̵������ش�.

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
	if (kbhit())   //kbhit() =>Ű������ �Է��� �����ϴ� �Լ� 
	{
		gotoxy(roro.x, roro.y);//������ ��ǥ�ΰ���
		printf(" ");//������ ��ġ�� ������

		switch (getch()) // ���� ������ �� �̻� �̵����� �ʰ� �� �ܿ��� �����̴� �ڵ�
		{
		case LEFT:
			if (map[roro.y][roro.x / 2 - 1] > 0)//x�� 1/2ĭ��ŭ���� �����̹Ƿ� roro.x/2.
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
		printf("��");
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
				printf("��");
			}
			else if (map[i][j] == 0)
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	gotoxy(roro.x, roro.y); // x,y�� Ŀ�� �̵�
	printf("��"); //�� �ڸ��� '+' ���
	while (1)
	{
		move();
	}
	return 0;
}