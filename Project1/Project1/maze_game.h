#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "modules.h"

// void maze_game(void);

#define POINT_X 5  //보드 시작좌표 x
#define POINT_Y 6  //보드 시작좌표 y

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define DELAY 100
#define EXIT 50

#define ROW 25
#define COL 25
#define MAX ROW*COL


int maze[25][25] = { 0, };
int top = -1;
int num1 = 0;
int num2 = 1;
int* x1 = &num1;
int* y1 = &num2;
int stack[][2] = { 0, };
enum boolean{false, true};

