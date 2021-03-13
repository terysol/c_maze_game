#include <stdio.h>
#include <windows.h>

#define UP 72
#define DOWN 80 //키보드 방향키의 아스키코드값을 정의해둔것입니다.
#define LEFT 75     //이런식으로 정의해두면 편하게 사용할 수 있습니다.
#define RIGHT 77 

void textcolor(int color_number)

{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

gotoxy(int x, int y) //gotoxy함수를 호출해올 기본함수.
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int keeper(int(*map)[36], int X, int Y) { //2차원 배열과 좌표를 받습니다.

	int checker;

	if (*(*(map + Y) + X) == 0) { //야 간단히 검사만 하면 되겠네요? 그렇죠?
		checker = 1;
	} //좌표부분의 맵값이 0이면 1을 반환하고
	else if (*(*(map + Y) + X) == 2) {
		checker = 1;
	}
	else { checker = 0; } //0이 아니면 지나다니면 안된다는듯으로 0을 반환시킬께요. 

	return checker;
}
int main() {

	int X = 4, Y = 3; //좌표값.
	int test, checker, helper, helper2;
	int map[20][36] = {
		{0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9},
		{1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9},
		{1,9,0,9,0,9,1,9,0,9,0,9,0,9,1,9,0,9,0,9,0,9,0,9,0,9,0,9,1,9,0,9,0,9,1,9},
		{1,9,0,9,0,9,1,9,0,9,1,9,0,9,0,9,0,9,0,9,1,9,1,9,1,9,1,9,1,9,0,9,2,9,1,9},//하트 32,3
		{1,9,0,9,1,9,1,9,1,9,1,9,0,9,1,9,1,9,1,9,1,9,0,9,0,9,0,9,1,9,0,9,0,9,1,9},
		{1,9,0,9,0,9,0,9,0,9,1,9,0,9,0,9,1,9,0,9,0,9,0,9,1,9,0,9,0,9,0,9,0,9,1,9},
		{1,9,0,9,1,9,1,9,0,9,1,9,0,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,0,9,1,9},
		{1,9,0,9,0,9,1,9,0,9,1,9,0,9,0,9,0,9,0,9,0,9,0,9,1,9,0,9,0,9,0,9,0,9,1,9},
		{1,9,1,9,0,9,1,9,0,9,1,9,1,9,0,9,1,9,1,9,1,9,0,9,1,9,0,9,1,9,0,9,0,9,1,9},
		{1,9,0,9,0,9,1,9,0,9,0,9,0,9,0,9,1,9,0,9,0,9,0,9,1,9,0,9,1,9,1,9,1,9,1,9},
		{1,9,0,9,1,9,1,9,1,9,0,9,0,9,1,9,0,9,0,9,1,9,0,9,1,9,0,9,0,9,0,9,0,9,1,9},
		{1,9,1,9,1,9,0,9,1,9,1,9,0,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,0,9,1,9,1,9,1,9},
		{1,9,0,9,0,9,0,9,0,9,0,9,0,9,1,9,0,9,1,9,0,9,0,9,0,9,1,9,0,9,0,9,0,9,1,9},
		{1,9,0,9,1,9,0,9,1,9,1,9,1,9,0,9,0,9,0,9,0,9,1,9,0,9,1,9,1,9,1,9,0,9,1,9},
		{1,9,0,9,1,9,1,9,1,9,0,9,0,9,0,9,1,9,1,9,0,9,1,9,0,9,0,9,0,9,0,9,0,9,1,9},
		{1,9,0,9,0,9,1,9,0,9,0,9,1,9,0,9,0,9,1,9,1,9,1,9,0,9,1,9,0,9,1,9,1,9,1,9},
		{1,9,1,9,0,9,1,9,1,9,0,9,1,9,1,9,0,9,0,9,0,9,1,9,0,9,1,9,0,9,1,9,0,9,1,9},
		{1,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,0,9,1,9,0,9,0,9,0,9,1,9,0,9,0,9,0,9,1,9},
		{1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9} };
	//2차원 배열을 적당히 초기화 시킨뒤

	system("mode con cols=37 lines=24");

	gotoxy(4, 1); textcolor(15); printf("★★  미 로 찾 기 샘 플  ★★");
	gotoxy(0, 2); //원하는 좌표로 가서
	for (helper = 0; helper < 20; helper++) { //이중 for문으로 맵을 출력해봅니다.
		for (helper2 = 0; helper2 < 36; helper2++) {
			if (map[helper][helper2] == 1) {
				textcolor(8);
				printf("■");
			}
			else if (map[helper][helper2] == 2) {
				textcolor(12);
				printf("♥");
			}
			else if (map[helper][helper2] == 0) {
				printf("  ");
			} //0인 경우 빈칸을 출력합니다.
//빈칸은 반드시 출력해줘야 합니다 
//그래야 원하는 위치에 원하는 문자를 출력시킬수 있습니다.
		}
		printf("\n"); //한줄 출력한 후에는 반드시 띄워주어야 엉키지 않습니다.
	}
	textcolor(14);
	gotoxy(X, Y + 2);
	printf("●");

	while (1) {

		test = getch(); //문자를 먼저 입력받습니다.
		textcolor(14);
		switch (test) { //입력받은 문자에 따라서 스위치문을 구성합니다.

		case UP: gotoxy(X, Y + 2);;
			printf(" ");//일단 지우고 시작합니다.
			Y -= 1;//좌표를 이동시켜본뒤에

			checker = keeper(map, X, Y);
			//map배열 주소와 좌표를 넘겨줘 봅시다
			if (checker == 1) {
				gotoxy(X, Y + 2);
				printf("●");//지나가도 된다면 그자리에 출력해주고
				break;
			}
			else if (checker == 0)
			{
				Y += 1;//막힌길이면 좌표를 다시 되돌린후에
				gotoxy(X, Y + 2);
				printf("●");//다시 출력해줍니다.
				break;
			}
		case DOWN: gotoxy(X, Y + 2);
			printf(" ");
			Y += 1;
			checker = keeper(map, X, Y);
			if (checker == 1) {
				gotoxy(X, Y + 2);
				printf("●");
				break;
			}
			else if (checker == 0)
			{
				Y -= 1;
				gotoxy(X, Y + 2);
				printf("●");
				break;
			}

		case LEFT: gotoxy(X, Y + 2);
			printf(" ");
			X -= 2;

			checker = keeper(map, X, Y);
			if (checker == 1) {

				gotoxy(X, Y + 2);
				printf("●");

				break;
			}
			else if (checker == 0)
			{
				X += 2;
				gotoxy(X, Y + 2);
				printf("●");
				break;
			}

		case RIGHT:   gotoxy(X, Y + 2);
			printf(" ");
			X += 2;

			checker = keeper(map, X, Y);
			if (checker == 1) {

				gotoxy(X, Y + 2);
				printf("●");

				break;
			}
			else if (checker == 0)
			{
				X -= 2;
				gotoxy(X, Y + 2);
				printf("●");
				break;
			}

		} //switch닫음

//gotoxy(0,0);
//printf("%2d %2d",X,Y);

		if (X == 32 & Y == 3 || X == 33 & Y == 3) { break; }
		else { continue; } //
		   //하트도 2바이트 문자인 관계로 X좌표를 2가지일경우로 설정했습니다.
	} //while 닫음

	system("cls"); //대충 화면을 깨끗이 지워주고

	for (helper = 0; helper <= 15; helper++) {
		gotoxy(10, 11); textcolor(helper); //막 승리했다고 띄워주면 마무리되겠죠?
		printf("★승리했습니다!★");
		Sleep(100);
	}

	system("pause>nul");
	fflush(stdin);

	system("cls");
	gotoxy(0, 11); textcolor(15);

} //main 함수 닫음