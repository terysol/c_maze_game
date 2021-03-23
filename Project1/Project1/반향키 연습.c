#include <stdio.h>
#include <windows.h>

#define UP 72
#define DOWN 80 //키보드 방향키의 아스키코드값을 정의해둔것입니다.
#define LEFT 75     //이런식으로 정의해두면 편하게 사용할 수 있습니다.
#define RIGHT 77

void gotoxy(int x, int y) //gotoxy함수를 호출해올 기본함수.
{
    COORD pos = { x, y };  // y는 2배한 값으로 콘솔에 찍힘.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {

    int X = 44, Y = 22; //좌표값.
    int test;

    system("mode con cols=92 lines=40");


    while (1) {

        test = getch(); //문자를 먼저 입력받습니다.

        switch (test) { //입력받은 문자에 따라서 스위치문을 구성합니다.

        case UP: gotoxy(X, Y);
            printf("  "); //기존에 출력된 문자는 지우고
            Y -= 1;        //좌표를 이동시킨 뒤에
            gotoxy(X, Y);
            printf("●"); //새로운 위치에 문자를 출력해줍니다
            break;   //이렇게 해서 마치 문자가 움직이는듯한
                         //효과를 만들 수 있습니다.

        case DOWN: gotoxy(X, Y);
            printf("  ");
            Y += 1;
            gotoxy(X, Y);
            printf("●");
            break;

        case LEFT: gotoxy(X, Y);
            printf("  ");
            X -= 1;
            gotoxy(X, Y);
            printf("●");
            break;

        case RIGHT: gotoxy(X, Y);
            printf("  ");
            X += 1;
            gotoxy(X, Y);
            printf("●");
            break;

        }//switch닫음

        gotoxy(80, 38);
        printf("%2d %2d", X, Y); //변수 X,Y는 좌표값이며                                          continue;                           // 유동적으로 변하는 값입니다.
                           //이를 출력시키는것으로 "좌표측량"이 가능합니다!

    } //while 닫음

} //main 함수 닫음