#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define  MaxSize 100//�Թ����������
int maze[10][10]={0};//�궨��һ����ά���鴢���Թ���Ϣ
typedef struct {
	int x;//������
	int y;//������
}PosType;//����һ���ṹ������
typedef struct {
	PosType seat;//ͨ�������Թ��ġ�����λ�á�
	int di;//�Ӵ�ͨ����������һ��ͨ����ġ�����
}Box;//λ�÷���Ķ���
typedef struct {
	Box data[MaxSize];
	int top;
}StType;//����һ���Թ�˳��ջ
//�������ļ���ȡ�Թ��ĺ���
void Init_Maze(char* filename);
//����ʵ�ֺ��������Եִﷵ��1;�����Է���0
int  Maze_Path(int Xb, int Yb, int Xe, int Ye);