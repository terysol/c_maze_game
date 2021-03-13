#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

#define XPOS 30
#define YPOS 5

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

void CursorView(char show);
void GotoXY(int x, int y);
int GetKey();
int** maze;
int row = 25, col = 25;


void CursorView(char show) //Ŀ���� ���ִ� �Լ�
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void GotoXY(int x, int y) //�ܼ� ���� Ŀ�� ��ġ�� �ٲپ� ���ϴ� ���� �̷θ� ����ϱ� ���� �Լ�
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int GetKey() //Ű�� �޾Ƶ��̴� �Լ�
{
	if (_kbhit() != 0) //Ű �Է��� ��ȿ�� ���
	{
		return _getch(); //�Է��� Ű ��ȯ
	}

	return 0; //�׷��� ���� ��� 0��ȯ
}

void print_maze(int** maze) //�̷� frame(Ʋ)�� �׷��ִ� �Լ�
{
	int i, j, k = 0;

	int view_i, view_j, d, chk_cnt;
	int move[4][2] = { {-2,0},{2,0},{0,-2},{0,2} };//�����¿�

	struct room {
		int r;
		int c;
	}*unknown;

	struct candidate_room {
		int r;
		int c;
		int d;
	}*candidate;

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
	//----------

	// ������ ��ĭ�� ��� 1�� �Ǳ� 
	maze[11][24] = 3;
	maze[6][24] = 3;


	maze[21][24] = 3;
	//�̷θ� �����	

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (maze[i][j] == 2) {
				printf("��");
			}
			else if (maze[i][j] == 0) printf("��");
			else printf("��");
		}
		printf("\n");
	}
}

void print_mazeGame(int** maze) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (maze[i][j] == 2) {
				printf("��");
			}
			else {
				printf("��");
			}
		}
		printf("\n");
	}
}

int is_block(int** maze, int i, int j)
{

	if (maze[i][j] == 1 || maze[i][j] == 3) //�̷ΰ� ���� ���, ������ ���
		return 1;
	else
		return 0;
}

int is_finish(int** maze, int i, int j)
{

	if (maze[i][j] == 3) //������ ���
		return 1;
	else
		return 0;
}

void complete_exit() //�Ϸ��� �� ���α׷��� �����Ű�� �Լ�
{
	printf("Complete!!!\n");
	exit(0);
}

void move_maze(int** maze, int* row, int* col) //��ü(���� ���ΰ�?)�� �����̴� �Լ�
{
	int chr; //Ű�� �޾Ƶ��̱� ���� ����
	int i = *row; //1
	int j = *col; //0


	chr = GetKey();

	if (chr == 0 || chr == 0xe0) // �������� �����ϰڽ��ϴ�.
	{
		chr = GetKey();

		switch (chr)
		{
		case UP:
			i--;
			if (!(is_block(maze, i, j))) //���� �ƴ� ��� ��ü�� �ű� �� ����
			{
				maze[*row][j] = 0; //���� ��Ͽ� 0�� ���� 
				maze[i][j] = 2; //����Ű�� �ű� �� x�� ����
				*row -= 1;
			}
			else if (is_finish(maze, i, j)) //������ ���
			{
				maze[*row][j] = 0;
				maze[i][j] = 2;
				print_mazeGame(maze);
				complete_exit();
			}
			break;

		case DOWN:
			i++;
			if (!(is_block(maze, i, j)))
			{
				maze[*row][j] = 0;
				maze[i][j] = 2;
				*row += 1;
			}
			else if (is_finish(maze, i, j))
			{
				maze[*row][j] = 0;
				maze[i][j] = 2;
				print_mazeGame(maze);
				complete_exit();
			}
			break;

		case LEFT:
			j--;
			if (!(is_block(maze, i, j)))
			{
				maze[i][*col] = 0;
				maze[i][j] = 2;
				*col -= 1;
			}
			else if (is_finish(maze, i, j))
			{
				maze[i][*col] = 0;
				maze[i][j] = 2;
				print_mazeGame(maze);
				complete_exit();
			}
			break;

		case RIGHT:
			j++;
			if (!(is_block(maze, i, j)))
			{
				maze[i][*col] = 0;
				maze[i][j] = 2;
				*col += 1;
			}
			else if (is_finish(maze, i, j))
			{
				maze[i][*col] = 0;
				maze[i][j] = 2;
				print_mazeGame(maze);
				complete_exit();
			}
			break;
		}
	}

}

int main(void) {

	int row = 0, col = 1; //���� ��ġ �ʱ�ȭ

	CursorView(0);

	GotoXY(5, 5);
	printf("�̷� ã�� ����\n");
	print_maze(maze);

	while (1) //���� start
	{
		print_mazeGame(maze);
		move_maze(maze, &row, &col);
	}

	return 0;
}