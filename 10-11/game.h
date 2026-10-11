#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 9
#define COL 9
#define ROWS (ROW+2)
#define COLS (COL+2)

#define EASY_COUNT 10

//函数的声明

//初始化游戏区域的函数
void InitBoard(char board[ROWS][COLS], int r, int c, char set);

//打印棋盘的函数
void DisplayBoard(char board[ROWS][COLS], int r, int c);

//布置雷
void SetMine(char mine[ROWS][COLS], int r, int c);

//排查雷
//start: 游戏的起始时间，用于每次排雷后计算已用时间
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int r, int c, clock_t start);
