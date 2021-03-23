#include <stdio.h>
//배경설정
int N = 8;
int map[8][8] = {
    {0, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 1, 0, 1, 1, 0, 1},
    {0, 0, 0, 1, 0, 0, 0, 1},
    {0, 1, 0, 0, 1, 1, 0, 0},
    {0, 1, 1, 1, 0, 0, 1, 1},
    {0, 1, 0, 0, 0, 1, 0, 1},
    {0, 0, 0, 1, 0, 0, 0, 1},
    {0, 1, 1, 1, 0, 1, 0, 0},
};

const int PATHWAY = 0; // 지나갈 수 있는 길
const int WALL = 1; // 벽
const int BLOCKED = 2; // 돌아오면서 막은 길
const int PATH = 3; //지나가면서 표시한 길

//함수 지정
int findMapPath(int x, int y) {
    if (x < 0 || y < 0 || x >= N || y >= N) {
        return 0;
    }
    else if (map[x][y] != PATHWAY) return 0;
    else if (x == N - 1 && y == N - 1) {
        map[x][y] = PATH;
        return 1;
    }
    else {
        map[x][y] = PATH;
        if (findMapPath(x - 1, y) || findMapPath(x, y + 1)
            || findMapPath(x + 1, y) || findMapPath(x, y - 1)) {
            return 1;
        }
        map[x][y] = BLOCKED;
        return 0;
    }
}
//main
int main() {
    //Q. 0,0 지점부터 7,7까지 갈 수 있는 길은 존재할까?
    printf("미로를 지날 수 있습니까?\n");
    if (findMapPath(1,1)) printf("네!");
    else printf("아니오!");
    return 0;
}