#include <stdio.h>
#include <windows.h>
#include <time.h>

int main() {

    clock_t start = clock();

    for (;;) {
        clock_t end = clock();
        double time = double(end - start) / CLOCKS_PER_SEC; //�ʴ��� ��ȯ
        printf("����ð� : %0.3lf\n", time); //�Ҽ��� ��° �ڸ�����

        system("cls");
    }
}