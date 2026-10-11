#define _CRT_SECURE_NO_WARNINGS

#include "game.h"

//函数的定义

void InitBoard(char board[ROWS][COLS], int r, int c, char set)
{
	int i = 0;
	for (i = 0; i < r; i++)
	{
		int j = 0;
		for (j = 0; j < c; j++)
		{
			board[i][j] = set;
		}
	}
}

void DisplayBoard(char board[ROWS][COLS], int r, int c)
{
	int i = 0;
	int j = 0;
	//列号打印
	for (j = 0; j <= c; j++)
	{
		printf("%d ", j);
	}
	printf("\n");
	for (i = 1; i <= r; i++)
	{
		printf("%d ", i);
		
		for (j = 1; j <= c; j++)
		{
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void SetMine(char mine[ROWS][COLS], int r, int c)
{
	int count = EASY_COUNT;
	while (count) //>=EASY_COUNT
	{
		int x = rand() % r + 1;
		int y = rand() % c + 1;
		if (mine[x][y] != '1')
		{
			mine[x][y] = '1';
			count--;
		}
	}
}

//这个函数仅仅是为了指支持FindMine函数的实现而存在的
//这个函数就可以被static修饰，变成一个内部函数
//static size_t GetMineCount(char mine[ROWS][COLS], int x, int y)
//{
//	return mine[x - 1][y] + mine[x - 1][y - 1] + mine[x][y - 1] + mine[x + 1][y - 1] +
//		mine[x + 1][y] + mine[x + 1][y + 1] + mine[x][y + 1] + mine[x - 1][y + 1] - 8 * '0';
//}

static size_t GetMineCount(char mine[ROWS][COLS], int x, int y)
{
	int i = 0;
	int j = 0;
	size_t count = 0;
	for (i = -1; i <= 1; i++)
	{
		for (j = -1; j <= 1; j++)
		{
			count += (mine[x + i][y + j] - '0');
		}
	}
	return count;
}

//排查雷
//start: 游戏开始的时间，用于计算排雷已经消耗的时间
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int r, int c, clock_t start)
{
	int x = 0;
	int y = 0;
	int win = 0;
	while (win < r * c -EASY_COUNT)
	{
		printf("请输入要排查的坐标:");
		scanf("%d%d", &x, &y);
		//判断输入坐标的合法性
		if (x >= 1 && x <= r && y >= 1 && y <= c)
		{
			//判断该位置是否被排查过
			if (show[x][y] == '*')
			{
				//该位置是不是雷
				//win == 0表示还没排过雷，即第一次排雷；第一次排雷即使踩雷也不炸死，把雷移走
				if (mine[x][y] == '0' || win == 0) //不是雷 或 第一次排雷
				{
					//第一次排雷就踩到雷，把雷移走，重新随机放到其他空位
					if (mine[x][y] == '1')
					{
						mine[x][y] = '0';
						int nx = 0;
						int ny = 0;
						do
						{
							nx = rand() % r + 1;
							ny = rand() % c + 1;
						} while (mine[nx][ny] == '1');//找到一个没有雷的位置
						mine[nx][ny] = '1';
					}
					size_t count = GetMineCount(mine, x, y);//统计mine数组中x,y周围雷的个数
					show[x][y] = (char)(count + '0');
					DisplayBoard(show, ROW, COL);
					win++;
					//(clock() - start)是游戏开始到现在消耗的CPU时钟周期
					//除以CLOCKS_PER_SEC换算成秒，%.0f表示不显示小数
					printf("当前已用时%.0f秒\n", (double)(clock() - start) / CLOCKS_PER_SEC);
				}
				else
				{
					printf("很遗憾，你被炸死了\n");
					DisplayBoard(mine, ROW, COL);
					printf("本局共消耗%.0f秒\n", (double)(clock() - start) / CLOCKS_PER_SEC);
					break;
				}
			}
			else
			{
				printf("该坐标已经被排查过了，请重新输入坐标\n");
			}
		}
		else
		{
			printf("输入的坐标非法，请重新输入\n");
		}
	}
	if (win == r * c - EASY_COUNT)
	{
		printf("恭喜你，排雷成功\n");
		DisplayBoard(mine, ROW, COL);
		printf("本局共消耗%.0f秒\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	}
}

 


