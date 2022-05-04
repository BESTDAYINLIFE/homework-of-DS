#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define  MaxSize 100//迷宫的最大容量
int maze[10][10]={0};//宏定义一个二维数组储存迷宫信息
typedef struct {
	int x;//横坐标
	int y;//纵坐标
}PosType;//定义一个结构体坐标
typedef struct {
	PosType seat;//通道块在迷宫的“坐标位置”
	int di;//从此通道块走向下一个通道块的“方向”
}Box;//位置方块的定义
typedef struct {
	Box data[MaxSize];
	int top;
}StType;//定义一个迷宫顺序栈
//声明从文件读取迷宫的函数
void Init_Maze(char* filename);
//声明实现函数，可以抵达返回1;不可以返回0
int  Maze_Path(int Xb, int Yb, int Xe, int Ye);