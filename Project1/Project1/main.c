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


void CursorView(char show) //커서를 없애는 함수
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void GotoXY(int x, int y) //콘솔 위에 커서 위치를 바꾸어 원하는 곳에 미로를 출력하기 위한 함수
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int GetKey() //키를 받아들이는 함수
{
	if (_kbhit() != 0) //키 입력이 유효할 경우
	{
		return _getch(); //입력한 키 반환
	}

	return 0; //그렇지 않을 경우 0반환
}

void print_maze(int** maze) //미로 frame(틀)을 그려주는 함수
{
	int i, j, k = 0;

	int view_i, view_j, d, chk_cnt;
	int move[4][2] = { {-2,0},{2,0},{0,-2},{0,2} };//상하좌우

	struct room {
		int r;
		int c;
	}*unknown;

	struct candidate_room {
		int r;
		int c;
		int d;
	}*candidate;

	//2차원 배열처럼 사용할 maze 생성
	maze = (int**)malloc(sizeof(int*) * row);
	for (i = 0; i < row; i++) maze[i] = (int*)malloc(sizeof(int) * col);

	//미로 방 전체 개수. 벽을 제외한 방의 개수 
	chk_cnt = (row / 2) * (col / 2);

	//미지 리스트 준비
	unknown = (struct room*)malloc(sizeof(struct room) * chk_cnt);

	//후보 미로 리스트 준비
	candidate = (struct candidate_room*)malloc(sizeof(struct candidate_room) * chk_cnt);

	//미로 행렬 전체를 벽(0)으로 채우고, 모든 방을 미지 리스트에 차례로 삽입 
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

	//임의의 방을 선택하고 미로 표시
	k = (int)rand() % chk_cnt;
	maze[unknown[k].r][unknown[k].c] = 1;

	//미지 리스트에서 제외. 끝 방의 좌표를 k 방으로 이동
	chk_cnt--; //미지 리스트에서 하나 줄임
	unknown[k].r = unknown[chk_cnt].r;
	unknown[k].c = unknown[chk_cnt].c;

	//미지 리스트에 방이 남아 있으면 반복
	while (chk_cnt > 0) {

		//임의의 방을 선택
		k = (int)rand() % chk_cnt;
		i = unknown[k].r;
		j = unknown[k].c;

		//후보 미로 리스트에 추가 
		k = 0;
		candidate[k].r = i;
		candidate[k].c = j;
		maze[i][j] = 2;

		//미로 만날 때까지 반복
		while (1) {

			d = (int)rand() % 4;
			view_i = i + move[d][0];
			view_j = j + move[d][1];

			//미로 범위 밖이면 다시 방향 정함 
			if (view_i < 1 || view_i > row - 2 || view_j < 1 || view_j > col - 2) continue;

			//미로 범위내 이면 방향 저장하고
			candidate[k].d = d;
			//다음 이동할 방을 일단 후보에 추가 
			k++;
			candidate[k].r = view_i;
			candidate[k].c = view_j;
			//다음 방이 미지이면 전진하고 후보 미로임을 표시 
			if (maze[view_i][view_j] == 0) {
				i = view_i;
				j = view_j;
				maze[i][j] = 2;
			}
			else if (maze[view_i][view_j] == 1)break; //미로를 만나면 빠져나감
			else { //maze[view_i][view_j] == 2 일 때, 후보 미로를 만났으므로 사이클을 제거함
				//이전 후보
				k--;
				do { //(view_i, view_j)를 만날 때까지 취소해 나감
					//이전으로 되돌아 가면서 후보(2)를 취소(0)함
					maze[candidate[k].r][candidate[k].c] = 0;
					k--;
				} while (candidate[k].r != view_i || candidate[k].c != view_j);
				//사이클의 원점으로 돌아와 다시 미로 찾아 나섬
				i = view_i;
				j = view_j;
			}
		}
		//임의 지점에서 미로를 만난 지점까지 미로 표시하고 미로방마다 미지리스트에서 제거함 
		for (i = 0; i < k; i++) {
			maze[candidate[i].r][candidate[i].c] = 1;
			switch (candidate[i].d) {
			case 0: maze[candidate[i].r - 1][candidate[i].c] = 1; break;
			case 1: maze[candidate[i].r + 1][candidate[i].c] = 1; break;
			case 2: maze[candidate[i].r][candidate[i].c - 1] = 1; break;
			case 3: maze[candidate[i].r][candidate[i].c + 1] = 1;
			}
			//미지 리스트에서 하나 줄임
			chk_cnt--;
			//후보 위치 탐색
			for (j = 0; j < chk_cnt; j++) if (candidate[i].r == unknown[j].r && candidate[i].c == unknown[j].c) break;
			//후보가 미로로 변경되면서 리스트에서 제외. 끝 방의 좌표를 j 방으로 이동
			unknown[j].r = unknown[chk_cnt].r;
			unknown[j].c = unknown[chk_cnt].c;
		}
	}
	maze[0][1] = 2;
	//----------

	// 옆에가 빈칸일 경우 1로 되기 
	maze[11][24] = 3;
	maze[6][24] = 3;


	maze[21][24] = 3;
	//미로를 출력함	

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (maze[i][j] == 2) {
				printf("●");
			}
			else if (maze[i][j] == 0) printf("▦");
			else printf("　");
		}
		printf("\n");
	}
}

void print_mazeGame(int** maze) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (maze[i][j] == 2) {
				printf("●");
			}
			else {
				printf("　");
			}
		}
		printf("\n");
	}
}

int is_block(int** maze, int i, int j)
{

	if (maze[i][j] == 1 || maze[i][j] == 3) //미로가 벽일 경우, 종점일 경우
		return 1;
	else
		return 0;
}

int is_finish(int** maze, int i, int j)
{

	if (maze[i][j] == 3) //종점일 경우
		return 1;
	else
		return 0;
}

void complete_exit() //완료한 후 프로그램을 종료시키는 함수
{
	printf("Complete!!!\n");
	exit(0);
}

void move_maze(int** maze, int* row, int* col) //객체(게임 주인공?)을 움직이는 함수
{
	int chr; //키를 받아들이기 위한 변수
	int i = *row; //1
	int j = *col; //0


	chr = GetKey();

	if (chr == 0 || chr == 0xe0) // 본문에서 설명하겠습니다.
	{
		chr = GetKey();

		switch (chr)
		{
		case UP:
			i--;
			if (!(is_block(maze, i, j))) //블럭이 아닐 경우 객체를 옮길 수 있음
			{
				maze[*row][j] = 0; //이전 블록에 0을 삽입 
				maze[i][j] = 2; //방향키를 옮긴 뒤 x를 삽입
				*row -= 1;
			}
			else if (is_finish(maze, i, j)) //종점일 경우
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

	int row = 0, col = 1; //시작 위치 초기화

	CursorView(0);

	GotoXY(5, 5);
	printf("미로 찾기 게임\n");
	print_maze(maze);

	while (1) //게임 start
	{
		print_mazeGame(maze);
		move_maze(maze, &row, &col);
	}

	return 0;
}