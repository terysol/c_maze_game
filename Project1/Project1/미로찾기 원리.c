#include <stdio.h>
//��漳��
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

const int PATHWAY = 0; // ������ �� �ִ� ��
const int WALL = 1; // ��
const int BLOCKED = 2; // ���ƿ��鼭 ���� ��
const int PATH = 3; //�������鼭 ǥ���� ��

//�Լ� ����
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
    //Q. 0,0 �������� 7,7���� �� �� �ִ� ���� �����ұ�?
    printf("�̷θ� ���� �� �ֽ��ϱ�?\n");
    if (findMapPath(1,1)) printf("��!");
    else printf("�ƴϿ�!");
    return 0;
}