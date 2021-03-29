#include "maze_game.h"


void gotoxy(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD getCursor(void)
{
	COORD curPoint;
	CONSOLE_SCREEN_BUFFER_INFO pos;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pos);
	curPoint.X = pos.dwCursorPosition.X;
	curPoint.Y = pos.dwCursorPosition.Y;
	return curPoint;
}

void removeCursor(void)
{
	CONSOLE_CURSOR_INFO cur;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
	cur.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur);
}

void textcolor(int color_number)

{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

//enum boolean push(int x, int y) {
//	if (top >= MAX - 1) {
//		printf("stack overflow\n");
//		return false;
//	}
//	top += 1;
//	stack[top][0] = x;
//	stack[top][1] = y;
//	return true;
//}
//
//enum boolean pop(int* x, int* y) {
//	if (top == -1) {
//		printf("stack underflow\n");
//		return false;
//	}
//	*x = stack[top][0];
//	*y = stack[top][1];
//	top -= 1;
//	return true;
//}

void showBoard(int row, int col)
{
	system("cls");
	//int maze[row][col] = { 0, };
	int i, j, k = 0;
	COORD cur = getCursor();
	//int row = 25;    // �̷��� ���� ũ��
	//int col = 25;
	struct room {
		int r;
		int c;
	}*unknown;

	struct candidate_room {
		int r;
		int c;
		int d;
	}*candidate;


	int view_i, view_j, d, chk_cnt;
	int move[4][2] = { {-2,0},{2,0},{0,-2},{0,2} };//�����¿�

	//2���� �迭ó�� ����� maze ����
	maze = (int**)malloc(sizeof(int*) * row);
	for (i = 0; i < row; i++) maze[i] = (int*)malloc(sizeof(int) * col);


	//�̷� �� ��ü ����. ���� ������ ���� ���� 
	chk_cnt = (row / 2) * (col / 2);

	//���� ����Ʈ �غ�
	unknown = (struct room*)malloc(sizeof(struct room) * chk_cnt);

	//�ĺ� �̷� ����Ʈ �غ�
	candidate = (struct candidate_room*)malloc(sizeof(struct candidate_room) * chk_cnt);

	//�̷� ��� ��ü�� ��(0)���� ä���, ��� ���� ���� ����Ʈ�� ���ʷ� ���� 
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			maze[i][j] = 0;
			if (i % 2 == 1 && j % 2 == 1) {
				unknown[k].r = i;
				unknown[k].c = j;
				k++;
			}
		}
	}

	srand((unsigned int)time(NULL));

	//������ ���� �����ϰ� �̷� ǥ��
	k = (int)rand() % chk_cnt;
	maze[unknown[k].r][unknown[k].c] = 1;

	//���� ����Ʈ���� ����. �� ���� ��ǥ�� k ������ �̵�
	chk_cnt--; //���� ����Ʈ���� �ϳ� ����
	unknown[k].r = unknown[chk_cnt].r;
	unknown[k].c = unknown[chk_cnt].c;

	//���� ����Ʈ�� ���� ���� ������ �ݺ�
	while (chk_cnt > 0) {

		//������ ���� ����
		k = (int)rand() % chk_cnt;
		i = unknown[k].r;
		j = unknown[k].c;

		//�ĺ� �̷� ����Ʈ�� �߰� 
		k = 0;
		candidate[k].r = i;
		candidate[k].c = j;
		maze[i][j] = 2;

		//�̷� ���� ������ �ݺ�
		while (1) {

			d = (int)rand() % 4;
			view_i = i + move[d][0];
			view_j = j + move[d][1];

			//�̷� ���� ���̸� �ٽ� ���� ���� 
			if (view_i < 1 || view_i > row - 2 || view_j < 1 || view_j > col - 2) continue;

			//�̷� ������ �̸� ���� �����ϰ�
			candidate[k].d = d;
			//���� �̵��� ���� �ϴ� �ĺ��� �߰� 
			k++;
			candidate[k].r = view_i;
			candidate[k].c = view_j;
			//���� ���� �����̸� �����ϰ� �ĺ� �̷����� ǥ�� 
			if (maze[view_i][view_j] == 0) {
				i = view_i;
				j = view_j;
				maze[i][j] = 2;
			}
			else if (maze[view_i][view_j] == 1)break; //�̷θ� ������ ��������
			else { //maze[view_i][view_j] == 2 �� ��, �ĺ� �̷θ� �������Ƿ� ����Ŭ�� ������
				//���� �ĺ�
				k--;
				do { //(view_i, view_j)�� ���� ������ ����� ����
					//�������� �ǵ��� ���鼭 �ĺ�(2)�� ���(0)��
					maze[candidate[k].r][candidate[k].c] = 0;
					k--;
				} while (candidate[k].r != view_i || candidate[k].c != view_j);
				//����Ŭ�� �������� ���ƿ� �ٽ� �̷� ã�� ����
				i = view_i;
				j = view_j;
			}
		}
		//���� �������� �̷θ� ���� �������� �̷� ǥ���ϰ� �̷ι渶�� ��������Ʈ���� ������ 
		for (i = 0; i < k; i++) {
			maze[candidate[i].r][candidate[i].c] = 1;
			switch (candidate[i].d) {
			case 0: maze[candidate[i].r - 1][candidate[i].c] = 1; break;
			case 1: maze[candidate[i].r + 1][candidate[i].c] = 1; break;
			case 2: maze[candidate[i].r][candidate[i].c - 1] = 1; break;
			case 3: maze[candidate[i].r][candidate[i].c + 1] = 1;
			}
			//���� ����Ʈ���� �ϳ� ����
			chk_cnt--;
			//�ĺ� ��ġ Ž��
			for (j = 0; j < chk_cnt; j++) if (candidate[i].r == unknown[j].r && candidate[i].c == unknown[j].c) break;
			//�ĺ��� �̷η� ����Ǹ鼭 ����Ʈ���� ����. �� ���� ��ǥ�� j ������ �̵�
			unknown[j].r = unknown[chk_cnt].r;
			unknown[j].c = unknown[chk_cnt].c;
		}
	}
	
	maze[0][1] = 2;
	maze[13][23] = 3;


	//�̷θ� �����	

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++)
		{
			gotoxy(cur.X + (j * 2), cur.Y + i);
			if (maze[i][j] == 0) {
				textcolor(8);
				printf("��");
			}else if (maze[i][j] == 3) { 
				textcolor(12);  
				printf("��"); 
			}
			else printf("��");
		}
		printf("\n");
	}
	free(unknown);
	free(candidate);
	gotoxy(cur.X, cur.Y);
}


void showCharacter(void)
{
	COORD cur = getCursor();

	textcolor(14);
	printf("��");
	gotoxy(cur.X, cur.Y);
}
int detect(int x, int y)
{
	 
	// Ŀ�� ��ġ ��� 
	COORD cur = getCursor();  //(2,6)
	if (x == 2 || x == -2) {
		*x1 = *x1 + y;
		*y1=*y1+(x-1);
	}
	else {
		*x1 = *x1 + y;
		*y1 = *y1 + x;
	}

	// �̷� �ۿ� �ִ���?
	if (!((*x1 >= 0 && *x1 < 25) && (*y1 >= 0 && *y1 < 25)))
	{
		return 1;
	}

	
	if (maze[*x1][*y1] == 0) {   // 
		*x1 -= y;
		*y1 -= (x-1);
		return 1;
	}

	//�̼Ǽ���
	else if (maze[*x1][*y1] == 3)
		return EXIT;
	else
		//push(x1, y1);
		return 0;
}

void RemoveCharacter_Set(int x, int y)
{
	int value = detect(x, y);

	/*gotoxy(60, 25);
	printf("%d",value);*/
	if (value == 0)
	{
		COORD cur = getCursor();

		printf("  ");
		gotoxy(cur.X + x, cur.Y + y);
		
	}
	else if (value == EXIT)
	{
		system("cls");
		gotoxy(20,10);
		for (int helper = 0; helper <= 15; helper++) {
			gotoxy(10, 11); textcolor(helper); //�� �¸��ߴٰ� ����ָ� �������ǰ���?
			printf("��Ż���߽��ϴ�!��");
			Sleep(100);
			//system("pause");
		}
		exit(1);
	}
}

void character_static(void)
{
	int kb;
	gotoxy(7,6);  //�ɸ��� ������ġ
	while (1)
	{
		while (!_kbhit())
		{
			showCharacter();
			Sleep(DELAY);
		}
		kb = _getch();
		switch (kb)
		{
		case UP:
			RemoveCharacter_Set(0, -1);
			break;
		case DOWN:
			RemoveCharacter_Set(0, 1);
			break;
		case RIGHT:
			RemoveCharacter_Set(2, 0);
			break;
		case LEFT:
			RemoveCharacter_Set(-2, 0);
			break;
		}

	}
}



int main()
{
	
	system("cls");
	removeCursor(); //Ŀ�� ������ �����
	gotoxy(POINT_X, POINT_Y);

	showBoard(15, 15);
	character_static();
	/*int choose;

	gotoxy(70, 10);
	printf("1. 1�ܰ� ���(15x15)\n");
	gotoxy(70, 12);
	printf("2. 2�ܰ� ���(25x25)\n");
	gotoxy(70, 14);
	printf("3. ��ŷ ����\n");
	gotoxy(70, 16);
	printf("4. ���� �ϱ�\n");

	

	while (1) {
		gotoxy(70, 18);
		printf("���ϴ� ��带 �����ϼ��� >> ");
		scanf_s("%d", &choose);

		switch (choose) {
		case 1:
			showBoard(15, 15);
			character_static();
			break;
		case 2:
			showBoard(25, 25);
			character_static();
			break;
		case 3:
			break;
		case 4:
			exit(1);
		default:
			gotoxy(70, 20);
			printf("�ٽ� �Է����ּ���.");
			continue;
		}
	}*/
	free(maze);
	return 0;
}
