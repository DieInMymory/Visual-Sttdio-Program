#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#define Snake_Max 500

//🐍蛇
struct Snake
{
	int size;
	int dir;
	int speed;
	POINT coor[Snake_Max];
}snake;

enum DIR
{
	UP, DOWN, LEFT, RIGHT
};

struct Food
{
	int x;
	int y;
	int r;//食物大小
	bool flag;//是否被吃
	DWORD color;//食物颜色
}food;

void InitSnake()
{
	mciSendString("open ./x64/res/qqqg.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat",0,0,0);
	initgraph(640, 480);
	snake.size = 2;
	snake.dir=RIGHT;
	snake.speed = 10;
	for (int i = 0; i <  snake.size; i++)
	{
		snake.coor[i].x = 40-i*10;
		snake.coor[i].y = 20;
		
	}
	srand(GetTickCount());//随机数种子   获取系统开机时间 ms
	food.x = rand()%640;
	food.y = rand()%480;
	food.r = rand() % 10+8;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256,);
	food.flag = true;
}

void DrawSnake()
{
	//双缓冲绘图
	BeginBatchDraw();

	setbkcolor(RGB(113, 96, 232));
	cleardevice();

	setfillcolor(RED);
	for (size_t i = 0; i <snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	if (food.flag)
	{
		setfillcolor(food.color);
		solidcircle(food.x, food.y, food.r);
	}


	EndBatchDraw();
		
}

void KeyControl()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72:
			if (snake.dir!=DOWN)
			{
				snake.dir = UP;
			}		
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dir !=UP)
			{
				snake.dir = DOWN;
			}		
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			break;
		case ' ':
			
				while (_getch() != ' ');
				break;
		default:
			break;
		}

	}
}
//移动🐍蛇
void MoveSnake()
{
	for (int i = snake.size - 1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir)
	{
	case UP:
		if (snake.coor[0].y<0)
		{
			snake.coor[0].y = 480;
		}
		else
		{
			snake.coor[0].y -= snake.speed;
		}
		break;
	case DOWN:
		if (snake.coor[0].y >480)
		{
			snake.coor[0].y = 0;
		}
		else
		{
			snake.coor[0].y += snake.speed;
		}
		break;
	case LEFT:
		if (snake.coor[0].x < 0)
		{
			snake.coor[0].x = 640;
		}
		else
		{
			snake.coor[0].x -= snake.speed;
		}
		break;
	case RIGHT:
		if (snake.coor[0].x >640)
		{
			snake.coor[0].x = 0;
		}
		else
		{
			snake.coor[0].x += snake.speed;
		}
		break;
	default:
		break;
	}
	
}

void EatFood()
{
	if (food.flag==true&&
		snake.coor[0].x <= food.x+food.r&& snake.coor[0].x >= food.x - food.r
		&& snake.coor[0].y <= food.y + food.r && snake.coor[0].y >= food.y - food.r)
	{
			food.flag = false;
			snake.size++;	
	}
	if (food.flag == false)
	{
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.r = rand() % 10 + 8;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256, );
		food.flag = true;
	}
}

int main(void)
{	
	InitSnake();

	while (1)
	{
		KeyControl();
		DrawSnake();
		MoveSnake();
		EatFood();
	
		Sleep(100);
	}
	return 0;
}