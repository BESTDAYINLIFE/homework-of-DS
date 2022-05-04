#include "header2.h"
void Init_Maze(char* filename) {
	FILE* fp1 = NULL;
	fp1 = fopen(filename, "r");
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			fscanf(fp1, "%d", &(maze[i][j]));
		}
	}
	fclose(fp1);
}
int  Maze_Path(int Xb, int Yb, int Xe, int Ye) {
	//定义中间变量存储行走的情况
	int i, j, di;
	//定义一个栈
	StType ac;
	ac.top = -1;//初始化
	ac.top++;//起点进栈
	ac.data[ac.top].seat.x = Xb;//记录起点横坐标
	ac.data[ac.top].seat.y = Yb;//记录起点纵坐标
	ac.data[ac.top].di = -1;
	maze[Xb][Yb] = -1;
	while (ac.top > -1) {//栈不空进栈
		i = ac.data[ac.top].seat.y;
		j = ac.data[ac.top].seat.x;
		di = ac.data[ac.top].di;
		//定义一个布尔类型变量find作为判断条件：为1就是可以走；为0就是不可以走
		bool I_Can_Go = false;
		while (di < 8 && !I_Can_Go) {
			di++;
			//建立了以向右为x轴正方向，向下为y轴正方向的平面直角坐标系
			switch (di) {
				//八个方向八种情况
				//优先级依次是：下、右、右下、右上、上、左、上左
			case 0://向下：纵坐标加一
				i = ac.data[ac.top].seat.y + 1;
				j = ac.data[ac.top].seat.x;
				break;
			case 1://向右：横坐标加一
				i = ac.data[ac.top].seat.y;
				j = ac.data[ac.top].seat.x + 1;
				break;
			case 2://向右下：横坐标加一 纵坐标加一
				i = ac.data[ac.top].seat.y + 1;
				j = ac.data[ac.top].seat.x + 1;
				break;
			case 3://向右上：横坐标加一 纵坐标减一
				i = ac.data[ac.top].seat.y - 1;
				j = ac.data[ac.top].seat.x + 1;
				break;
			case 4://向左下：横坐标减一 纵坐标加一
				i = ac.data[ac.top].seat.y + 1;
				j = ac.data[ac.top].seat.x - 1;
				break;
			case 5://向上：纵坐标减一
				i = ac.data[ac.top].seat.y - 1;
				j = ac.data[ac.top].seat.x;
				break;
			case 6://向左：横坐标减一
				i = ac.data[ac.top].seat.y;
				j = ac.data[ac.top].seat.x - 1;
				break;
			case 7://向左上：横坐标减一 纵坐标减一
				i = ac.data[ac.top].seat.y - 1;
				j = ac.data[ac.top].seat.x - 1;
				break;
			}
			if (maze[i][j] == 0)I_Can_Go = true;
		}
		//下个方向可以走的话就移动位置，把当前的位置存进栈中
		if (I_Can_Go) {
			ac.data[ac.top].di = di;
			ac.top++;
			ac.data[ac.top].seat.y = i;
			ac.data[ac.top].seat.x = j;
			ac.data[ac.top].di = -1;
			maze[i][j] = -1;
		}
		//如果八个方向没找到可以走的位置就退回
		else {
			maze[ac.data[ac.top].seat.x][ac.data[ac.top].seat.y] = 0;
			ac.top--;
		}
		if (i == Ye && j == Xe) {//到终点了就把路径写入文件
			printf("迷宫路径正在写入文件中.....");
			cout << endl << "请稍候......." << endl << endl;
			FILE* fp2 = NULL;
			fp2 = fopen("Answer.txt", "w");
			if (!fp2) { exit(-1); cout << "文件打开失败" << endl; }
			for (int k = 0; k <= ac.top; k++) {

				fprintf(fp2, "\t(%d,%d)", ac.data[k].seat.x, ac.data[k].seat.y);
				if ((k + 1) % 4 == 0)//四个坐标换行，美观输出
					fprintf(fp2, "\n");
			}
			return true;
		}
	}
	return false;
}
int main()
{   int x, y, k, t;
	char s1[] = "InitialMaze.txt";
	Init_Maze(s1);
	
	//打印迷宫样式便于我们检查
	printf("迷宫的样式如下(#表示墙体 空隙表示可走区域)：\n");
	for (t = 0; t < 10; t++) {
		for (k = 0; k < 10; k++) {
			if (maze[t][k] == 0) {
				printf(" ");
			}
			if (maze[t][k] == 1) {
				printf("#");
			}
		}
		if (k == 10) {
			printf("\n");
		}
	}
	 cout << "请在大脑里建立了以向右为x轴正方向，向下为y轴正方向的平面直角坐标系" << endl;
	 cout << "然后请输入迷宫的起点坐标：";
	 scanf_s("%d %d", &x, &y);

	 while (maze[x][y] == 1) {
		 cout << "错误不可以输入墙体的坐标！请重新输入：" << endl;
		 scanf_s("%d %d", &x, &y);
	 }
	 while (x>=10||y>=10||x<0||y<0) {
		 cout << "错误不可以输入迷宫以外的坐标请重新输入：" << endl;
		 scanf_s("%d %d", &x, &y);
	 }
	 //迷宫有路径返回值为1
	 if (Maze_Path(x, y, 8, 8)) {
		 cout << endl << endl << endl;
		 cout << "迷宫的路径坐标已经写进文件“Answer.txt”里面";
		 cout << endl;
		 cout << endl;
		 cout << endl;
		 cout << endl;
	 }
	//无路径则返回值为0
	 else cout << "该迷宫无解" << endl;
	return 0;
}


