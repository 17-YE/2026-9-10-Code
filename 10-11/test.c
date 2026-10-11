#include "game.h"

void menu()
{
	printf("-------------------------\n");
	printf("------   1. play    -----\n");
	printf("------   0. exit    -----\n");
	printf("-------------------------\n");
}

void game()
{
	//需要存储数据的数组
	char mine[ROWS][COLS] = {0};//布置好的雷的信息
	char show[ROWS][COLS] = {0};//排查出的雷的信息
	//初始化游戏区域
	InitBoard(mine, ROWS, COLS, '0');//'0'
	InitBoard(show, ROWS, COLS, '*');//'*'
	//打印棋盘(游戏区)
	//DisplayBoard(mine, ROW, COL);
	DisplayBoard(show, ROW, COL);
	//布置雷
	SetMine(mine, ROW, COL);
	//DisplayBoard(mine, ROW, COL);  //调试用：会显示所有雷的位置，正式游戏请保持注释
	//排查雷
	//clock()获取当前时刻作为游戏的起始时间，并传入FindMine用于计算已用时间
	FindMine(mine, show, ROW, COL, clock());
}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));

	do
	{
		menu();
		printf("请选择:");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();//扫雷游戏
			break;
		case 0:
			printf("退出游戏\n");
			break;
		default:
			printf("选择错误，重新选择\n");
			break;
		}

	} while (input);

	return 0;
}
