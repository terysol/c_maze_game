#include <stdio.h>
#include <windows.h>

#define UP 72
#define DOWN 80 //Ű���� ����Ű�� �ƽ�Ű�ڵ尪�� �����صа��Դϴ�.
#define LEFT 75     //�̷������� �����صθ� ���ϰ� ����� �� �ֽ��ϴ�.
#define RIGHT 77

void gotoxy(int x, int y) //gotoxy�Լ��� ȣ���ؿ� �⺻�Լ�.
{
    COORD pos = { x, y };  // y�� 2���� ������ �ֿܼ� ����.
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main() {

    int X = 44, Y = 22; //��ǥ��.
    int test;

    system("mode con cols=92 lines=40");


    while (1) {

        test = getch(); //���ڸ� ���� �Է¹޽��ϴ�.

        switch (test) { //�Է¹��� ���ڿ� ���� ����ġ���� �����մϴ�.

        case UP: gotoxy(X, Y);
            printf("  "); //������ ��µ� ���ڴ� �����
            Y -= 1;        //��ǥ�� �̵���Ų �ڿ�
            gotoxy(X, Y);
            printf("��"); //���ο� ��ġ�� ���ڸ� ������ݴϴ�
            break;   //�̷��� �ؼ� ��ġ ���ڰ� �����̴µ���
                         //ȿ���� ���� �� �ֽ��ϴ�.

        case DOWN: gotoxy(X, Y);
            printf("  ");
            Y += 1;
            gotoxy(X, Y);
            printf("��");
            break;

        case LEFT: gotoxy(X, Y);
            printf("  ");
            X -= 1;
            gotoxy(X, Y);
            printf("��");
            break;

        case RIGHT: gotoxy(X, Y);
            printf("  ");
            X += 1;
            gotoxy(X, Y);
            printf("��");
            break;

        }//switch����

        gotoxy(80, 38);
        printf("%2d %2d", X, Y); //���� X,Y�� ��ǥ���̸�                                          continue;                           // ���������� ���ϴ� ���Դϴ�.
                           //�̸� ��½�Ű�°����� "��ǥ����"�� �����մϴ�!

    } //while ����

} //main �Լ� ����