#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
void gotoxy(int x, int y);
COORD getCursor(void);

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



int** maze;
int main() {
	//int maze[25][25] = { 0, };
	int i, j, k = 0;
	int row = 25;    // �̷��� ���� ũ��
	int col = 25;
	struct room {
		int r;
		int c;
	}*unknown;

	COORD cur = getCursor();
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
			printf("%d", maze[i][j]);
		}
		printf("\n");
	}
	free(unknown);
	free(candidate);
	gotoxy(cur.X, cur.Y);
	return 0;
}